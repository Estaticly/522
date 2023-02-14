//Abraham Mendoza 

//pins
const int buttonPin = 2;  //button on pin 2
const int ledPin = 4;    // led light on pin 4
//time
int period=500;//intial period of time
int currentPeriod;//the curren period of time
int startPeriod;//the start of the period of time
//button state
int buttonCou = 0;  //counts the number of times the button is pressed
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button

void setup() {
  pinMode(buttonPin, INPUT);//button set as a input
  
  pinMode(ledPin, OUTPUT); //led set as a output

  startPeriod = millis();//set the start period 
}


void loop() {
  // read button input pin:
  buttonState = digitalRead(buttonPin);
  if(buttonState != lastButtonState){
    if(buttonState ==HIGH){
      buttonCou++;
    }
    delay(50);//delay so button wont bounce
  }
  lastButtonState = buttonState;
  currentPeriod = millis();

  //sets up the frequency the light turns on and off
  
  if(buttonCou ==1){
    period = 250;//2hz
  }else if(buttonCou ==2) {
    period = 125;//4hz
  }else if(buttonCou ==3){
    period = 63;//8hz
  }else if(buttonCou ==4){
    buttonCou = 0;//reset
    period = 500;//1hz
  }
    
  //activates led at time interval chosen
  if(currentPeriod-startPeriod >= period){
    digitalWrite(ledPin, !digitalRead(ledPin));
    startPeriod = currentPeriod;
  }
  
}