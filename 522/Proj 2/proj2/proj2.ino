//Abraham Mendoza
#include <Arduino_FreeRTOS.h>
#include <Stepper.h>
//inputs
int buttonIn1 = 2;//button on pin 2
int buttonIn2 = 3;//button on pin 3

int currVelocity[] = {1,2,5,8,15};//each time button 1 is pressed this will increase 2>5>8>11>15 

int pointer =0;

int buttonState1 = 0;
int lastButtonState1 = 0;

int buttonState2 = 0;
int lastButtonState2 = 0;

//steps in my motor
const int stepsPerRevolution = 2038;

//init the pins for my motor
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
bool buttonOn = false;




unsigned long lastMilli = millis();
unsigned long debounceTime = 50;
void setup() {
  Serial.begin(9600);
    pinMode(buttonIn1,INPUT_PULLUP);
    pinMode(buttonIn2,INPUT);

    attachInterrupt(digitalPinToInterrupt(buttonIn1),ISR_button1,CHANGE);
    attachInterrupt(digitalPinToInterrupt(buttonIn2),ISR_button2,CHANGE);
}

void loop() {
  if(buttonOn == true){
    myStepper.setSpeed(currVelocity[pointer]);
	  myStepper.step(1);
  }
}

bool buttonStateHandelling(int pin){
//if(millis() -lastMilli >= debounceTime){
  switch(pin){
    case 1:
      if(digitalRead(buttonIn1)==0&& lastButtonState1 == 1){
        lastButtonState1 = 0;
        return true;
      }
      else if(digitalRead(buttonIn1)==1 && lastButtonState1 ==0){
        lastButtonState1 =1;
        return false;
      }
    break;
      case 2:
        if(digitalRead(buttonIn2)==0&& lastButtonState2 == 1){
          lastButtonState2 = 0;
          return true;
        }
        else if(digitalRead(buttonIn2)==1 && lastButtonState2 ==0){
          lastButtonState2 =1;
          return false;
        } 
      break;     
  }
//}return false;
}

void ISR_button1(){
  if(buttonStateHandelling(1)){
    if(!buttonOn ){
      buttonOn = !buttonOn;
    }else if(pointer !=4){
      pointer++;
   }
    Serial.println(currVelocity[pointer]);
    delay(75);
  }
}
//stop the motor on 1st click, 2ncd click will reset to default speed
void ISR_button2(){
  if(buttonStateHandelling(2)){
    if(buttonOn){
      buttonOn = !buttonOn;
    }else{
     pointer =0;
    }
    Serial.println(currVelocity[pointer]);
    delay(75);
  }
}