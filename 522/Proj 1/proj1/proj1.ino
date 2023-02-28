//Abraham Mendoza
int PotentioPin = 0;//potentiometer pin A0

int ledPin = 3;//LED pin ~3

int inputVal = 0;//Stores the val from pin A0 from 0-1023

int outputVal = 0;//Stores the output of A0 from 0-255

void setup(){
  pinMode(PotentioPin,INPUT);

  pinMode(ledPin,OUTPUT);

  Serial.begin(9600);//set the serial communication baudrate as 9600
}

void loop(){
  inputVal = analogRead(PotentioPin);//Read val from the potentiometer

  Serial.println(inputVal); //print the input val

  outputVal = map(inputVal, 0, 1023, 0, 255); //Converts val 0-1023  to val 0-255

  Serial.println(outputVal); //print the output val

  analogWrite(ledPin, outputVal); //Turns led on with the coresponding output val from 0-255
}