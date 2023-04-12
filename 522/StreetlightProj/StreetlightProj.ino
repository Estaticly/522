#include <Arduino_FreeRTOS.h>
//Abraham Mendoza

//maybe just 2 tasks a swtich task witht the delay to only switch lights every x seconds
//then a lights task with no delays only for changing lights 

void taskChangeLed(void *pvParameters);//Control the lights
void taskSwitch( void *pvParameters);//timer for the lights to switch

bool left=true;
bool sLeds;

int sTimer = 5000;
int yellowTimer =1000;

void setup(){
  Serial.begin(9600);
  
  xTaskCreate(taskChangeLed,"task1",128,NULL,1,NULL);

  xTaskCreate(taskSwitch,"task2",128,NULL,2,NULL);

  vTaskStartScheduler();
}

void loop(){

}

void taskSwitch(void *pvParameters){
  
  while(1){
  vTaskDelay(sTimer/portTICK_PERIOD_MS);
  Serial.println("sLeds changed");
  sLeds = true;
  }
  
}


void taskChangeLed(void *pvParameters){
  //               "LEFT"|"RIGHT"
  //-------------------------
  //   Red lights pin 7 and 6
  //Yellow lights pin 5 and 4
  // Green lights pin 3 and 2
  pinMode(7,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(2,OUTPUT);

  while(1){
    //check which side is on green
    //then check when a switch happens and start to change lights
    if(sLeds==true&&left){
      left = false;
      
      digitalWrite(3,LOW);
      digitalWrite(5,HIGH);
      vTaskDelay(yellowTimer/portTICK_PERIOD_MS);
      digitalWrite(5,LOW);
      digitalWrite(7,HIGH);
      sLeds =false;
    }else if(sLeds && !left){
      left = true;
      
      digitalWrite(2,LOW);
      digitalWrite(4,HIGH);
      vTaskDelay(yellowTimer/portTICK_PERIOD_MS);
      digitalWrite(4,LOW);
      digitalWrite(6,HIGH);
      sLeds =false;
    }
    else if(left){
      digitalWrite(7,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(6,HIGH);
    }else{
      digitalWrite(6,LOW);
      digitalWrite(2,HIGH);
      digitalWrite(7,HIGH);
    }
  }
}
