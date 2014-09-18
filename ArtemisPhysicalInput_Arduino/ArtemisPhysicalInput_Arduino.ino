#include <serial.h>

long lastDebounceTime = 0;
long debounceDelay = 50;

struct Button{
//  int buttonNumber;
  int Value;
  int pinNumber;
  int lastValue;
  String buttonNumber;
}button_type; // something about defining object of type Button

struct Button toggle0;

  
  struct Button toggle1;
 
  
void setup() {
  Serial.begin(9600);

  /* We are not using external pullup resistors so we use an onboard
   * pullup resistor to avoid any floating values
   * We could also accomplish this with the following lines of code
   * pinMode(toggle0Pin, INPUT);
   * digitalWrite(toggle0Pin, HIGH);
   */
    
  toggle0.pinNumber = 2;
  toggle0.buttonNumber="0";
  toggle0.lastValue= LOW;
  toggle0.Value = 1;
  
   toggle1.pinNumber = 4;
  toggle1.buttonNumber="1";
  toggle1.lastValue = LOW;
  toggle1.Value=1;
  
  
  pinMode(toggle0.pinNumber, INPUT_PULLUP);
//  pinMode(toggle1Pin, INPUT_PULLUP);
  
 
  
}

void loop() {

  pushTest(toggle0);
  pushTest(toggle1);

}

void pushTest(struct Button button){ //a detector for each button, hopefully fast enough


int reading = digitalRead(button.pinNumber);

if (reading != button.lastValue){
  lastDebounceTime= millis();
// Serial.print("uno "); //debug
}
  
  if ((millis()-lastDebounceTime) > debounceDelay){
    Serial.print(millis());
    Serial.print(":");
    Serial.print(lastDebounceTime);
   Serial.print("dos "); // debug
    
    if(reading != button.Value){
    button.Value = reading;
    Serial.print("tre "); // debug
    if(button.Value == LOW){
      String outputString = "fire"+ button.buttonNumber;
      Serial.println(outputString);
      Serial.print("qua "); // debug
    }
    }
  }
  
  button.lastValue = reading;
//Serial.println("cin "); // debug
}



