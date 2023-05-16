#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define RST_PIN 9
#define SS_PIN 10

#define InterruptPin 2

int buttonState = 0;
int lastButtonState = 0;


int count = 1;
String Tags[5];//5 cards can be stored
String cardUID = "";


MFRC522 my522(SS_PIN,RST_PIN);
LiquidCrystal myLCD(8,7,6,5,4,3);

void setup() {
  Tags[0] = "59A8F854";//UID of one of my cards

  pinMode(InterruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(InterruptPin),ISR_Register,CHANGE);
  
  SPI.begin();
  my522.PCD_Init();

  myLCD.begin(16, 2);
  myLCD.clear();

  myLCD.print("Ready To Scan");
  
}

void loop() {
  while(getUID()){
    myLCD.clear();
    
    bool isCorrect = false;
    isCorrect = checkIDs();
    if(isCorrect){
      myLCD.print("Welcome");
      myLCD.setCursor(0,1);
      myLCD.print("Access Granted");
    }else{
      myLCD.print("Incorrect Card");
      myLCD.setCursor(0,1);
      myLCD.print("Please Register");
    }

    delay(4000);

    myLCD.clear();
    myLCD.print("Ready To Scan");
    
  }

}
//gets the cards ID
bool getUID(){
  if(!my522.PICC_IsNewCardPresent()){
    return false;
  }
  if(!my522.PICC_ReadCardSerial()){
    return false;
  }

  cardUID = "";
  for(int i =0;i<4;i++){
    cardUID.concat(String(my522.uid.uidByte[i],HEX));
  }
  cardUID.toUpperCase();
  my522.PICC_HaltA();
  return true;
}

void ISR_Register(){
  if(buttonStateHandelling()){
    myLCD.clear();
    myLCD.print("Register card");
    
    while(!setID()){}
    
    myLCD.clear();
    
    myLCD.print("Card read Success");
  }
  
}
bool buttonStateHandelling(){
      if(digitalRead(InterruptPin)==0&& lastButtonState == 1){
        lastButtonState = 0;
        return true;
      }else if(digitalRead(InterruptPin)==1&& lastButtonState == 0){
        lastButtonState = 1;
        return false;
      }
}

//sets carUID variable
bool setID(){

  if(!my522.PICC_IsNewCardPresent()){
    return false;
  }
  if(!my522.PICC_ReadCardSerial()){
    return false;
  }

  cardUID = "";
  for(int i =0;i<4;i++){
    cardUID.concat(String(my522.uid.uidByte[i],HEX));
  }
  cardUID.toUpperCase();
  Tags[count] = cardUID;

  count++;
  my522.PICC_HaltA();
  return true;
}

//checks if the card ID is in the array of stored IDs
bool checkIDs(){
  for(int i = 0; i<5;i++){
    if(Tags[i] == cardUID){
      return true;
    }
    
  }return false;
}
