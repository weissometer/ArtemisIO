#include <serial.h>

#define toggle0Pin 2
#define toggle1Pin 4

int toggle0;
int toggle1;
int lasttoggle0 = LOW;
int lasttoggle1 = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

char* myButtonPins[]={toggle0Pin,toggle1Pin};
char* myButtons[] =  {toggle0,  toggle1};
char* myLastState[] = {lasttoggle0, lasttoggle1};

int numberofButtons= 2;
void setup() {
  Serial.begin(9600);

  /* We are not using external pullup resistors so we use an onboard
   * pullup resistor to avoid any floating values
   * We could also accomplish this with the following lines of code
   * pinMode(toggle0Pin, INPUT);
   * digitalWrite(toggle0Pin, HIGH);
   */
  pinMode(toggle0Pin, INPUT_PULLUP);
  pinMode(toggle1Pin, INPUT_PULLUP);
  
}

void loop() {

  for( i=0; i<numberofButtons; i++){
    pushTest(i);
  }
}

void pushTest(int buttonNumber){ //a detector for each button, hopefully fast enough
int localButton = myButtons[buttonNumber];

int lastToggle = LOW;
int reading = digitalRead(myButtonPins[buttonNumber]);

if (reading != lastToggle){
  lastDebounceTime= millis();
}
  
  if (millis()-lastDebounceTime > debounceDelay){
    if(reading != localButton){
    localButton = reading;
    
    if(localButton == LOW){
      String outputString = "fire"+ buttonNumber;
      Serial.println(outputString);
    }
    }
  }
  
  myLastState[buttonNumber] = reading;

}
