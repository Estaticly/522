#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xCountingSemaphore;

void setup()
{
  Serial.begin(9600); 
  pinMode(LED_BUILTIN, OUTPUT);
  
  xTaskCreate(Task1, "Ledon", 128, NULL,0 ,NULL );
  xTaskCreate(Task2, "Ledoff", 128, NULL,0, NULL );

  xCountingSemaphore = xSemaphoreCreateCounting(1,1);
  
  xSemaphoreGive(xCountingSemaphore);
}

void loop() {}

void Task1(void *pvParameters)
{
  (void) pvParameters;
  while(1)
  {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    Serial.println("Inside Task1 and Serial monitor Resource Taken");
    digitalWrite(LED_BUILTIN, HIGH);
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}

void Task2(void *pvParameters)
  {
    (void) pvParameters;
    while(1)
    {
      xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
      Serial.println("Inside Task2 and Serial monitor Resource Taken");
      digitalWrite(LED_BUILTIN, LOW);
      xSemaphoreGive(xCountingSemaphore);
      vTaskDelay(1);
    }
}