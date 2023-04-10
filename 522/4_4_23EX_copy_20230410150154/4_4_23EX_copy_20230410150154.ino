#include <Arduino_FreeRTOS.h>

void TaskBlink1( void *pvParameters );

void TaskBlink2( void *pvParameters );

void Taskprint( void *pvParameters );
int checkNum = 0;
void setup() {

  // initialize serial communication at 9600 bits per second:

  Serial.begin(9600);

  xTaskCreate(

    TaskBlink1

    ,  "task1"   

    ,  128  

    ,  NULL

    ,  1  

    ,  NULL );

  xTaskCreate(

    TaskBlink2

    ,  "task2"

    ,  128  

    ,  NULL

    ,  2 

    ,  NULL );

    xTaskCreate(

    Taskprint

    ,  "task3"

    ,  128  

    ,  NULL

    ,  3  

    ,  NULL );

vTaskStartScheduler();

}

void loop()

{

}

void TaskBlink1(void *pvParameters)  {

  pinMode(8, OUTPUT);
  while (1){
    if(checkNum ==1||checkNum == 2){
      digitalWrite(8,HIGH);
    }
    else{
      digitalWrite(8,LOW);
    }
    vTaskDelay(200/portTICK_PERIOD_MS);
  }

/*
  while(1)

  {

    Serial.println("Task1");

    digitalWrite(8, HIGH);   

    vTaskDelay( 200 / portTICK_PERIOD_MS ); 

    digitalWrite(8, LOW);    

    vTaskDelay( 200 / portTICK_PERIOD_MS ); 

  }*/

}

void TaskBlink2(void *pvParameters)  

{

  pinMode(7, OUTPUT);
while (1){
    if(checkNum ==2||checkNum == 3){
      digitalWrite(7,HIGH);
    }
    else{
      digitalWrite(7,LOW);
    }
    vTaskDelay(200/portTICK_PERIOD_MS);
  }


/*
  while(1)

  {

    Serial.println("Task2");

    digitalWrite(7, HIGH);   

    vTaskDelay( 300 / portTICK_PERIOD_MS ); 

    digitalWrite(7, LOW);   

    vTaskDelay( 300 / portTICK_PERIOD_MS ); 

  }*/

}

void Taskprint(void *pvParameters)  {

  int counter = 0;

  while(1)

  {
    if(checkNum!=3){
     checkNum++;
    }else{
      checkNum = 0;
    }
  counter++;

  Serial.println(counter); 

  vTaskDelay(1000 / portTICK_PERIOD_MS);    }

}