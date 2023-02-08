


const int buttonPin = 2;  //button attached on pin #2
const int ledPin = 4;    // led light attached to pin #4

bool isOn =0;

int period=0;
int currentPeriod;
int startPeriod;

int buttonCou = 0;  //counts the number of times the button is pressed
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:

  startPeriod = millis();
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  if(buttonState != lastButtonState){
    if(buttonState ==HIGH){
      buttonCou++;
    
      //digitalWrite(ledPin, HIGH);
    }
    delay(50);
  }//I have something going i think the delays are messing me up as it doesnt change modes unles i hold it down or time it with the lights 
  lastButtonState = buttonState;
  currentPeriod = millis();
  //sets up the frequency the light turns on and off
  

  if(buttonCou ==1){
    period = 1000;
    isOn=1;
  }else if(buttonCou ==2) {
    period = 500;
  }else if(buttonCou ==3){
    period = 250;
  }else if(buttonCou ==4){
    period = 125;
  }else if(buttonCou >= 5){
    digitalWrite(ledPin, LOW);
    buttonCou = 0;
    isOn =0;
  }

  if(currentPeriod-startPeriod >= period && isOn == 1){
    digitalWrite(ledPin, !digitalRead(ledPin));
    startPeriod = currentPeriod;
  }
  //digitalWrite(ledPin, LOW);
}
