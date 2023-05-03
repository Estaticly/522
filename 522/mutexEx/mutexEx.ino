#include <Arduino_FreeRTOS.h>
#include <semphr.h>
//define two tasks
void Task_print1(void *param);
void Task_print2(void *param);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
SemaphoreHandle_t myMutex;


volatile int a;
//volatile boolean myMutex = false;

void setup() {
  Serial.begin(9600);

  myMutex = xSemaphoreCreateMutex();
  if(myMutex==NULL){
    Serial.println("Mutex can not be created");
  }

  xTaskCreate(Task_print1,"Task1",100,NULL,1,&TaskHandle_1);
  xTaskCreate(Task_print2,"Task2",100,NULL,1,&TaskHandle_2);

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void Task_print1(void *param){
  (void) param;
  while(1){
    xSemaphoreTake(myMutex,portMAX_DELAY);
    a++;
    for(int i=0;i<3;i++){
      Serial.print("Task1 a=");
      Serial.print(i);
      Serial.print("||volatile a=");
      Serial.println(a);
      digitalWrite(i+2,HIGH);
      vTaskDelay(100/portTICK_PERIOD_MS);
    }
    xSemaphoreGive(myMutex);
    vTaskDelay(1);
  }
}

void Task_print2(void *param){
  (void) param;
  
  while(1){
    
    xSemaphoreTake(myMutex,portMAX_DELAY);
    a++;
    for(int i=0;i<3;i++){
      Serial.print("Task2 b=");
      Serial.print(i);
      Serial.print("||volatile a=");
      Serial.println(a);
      digitalWrite(i+2,LOW);
      vTaskDelay(100/portTICK_PERIOD_MS);
    }
    xSemaphoreGive(myMutex);
    vTaskDelay(1);
  }
}
