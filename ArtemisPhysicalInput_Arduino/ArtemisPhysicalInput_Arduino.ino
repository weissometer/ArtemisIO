#include <serial.h>

#define buttonPin 2
#define toggle2Pin 4

int toggle1;
int lasttoggle1 = LOW;
int lasttoggle2 = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  Serial.begin(9600);

  /* We are not using external pullup resistors so we use an onboard
   * pullup resistor to avoid any floating values
   * We could also accomplish this with the following lines of code
   * pinMode(buttonPin, INPUT);
   * digitalWrite(buttonPin, HIGH);
   */
  pinMode(buttonPin, INPUT_PULLUP);
  
}

void loop() {
  /* The following code avoids button bouncing.
   * See: www.arduino.cc/en/Tutorial/Debounce for more details
   */
  int reading1 = digitalRead(buttonPin);
  
  int reading2 = digitalRead(toggle2Pin);
  
  if (reading1 != lasttoggle1) {
    lastDebounceTime = millis(); 
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading1 != toggle1) {
      toggle1 = reading1;

      // Only transmit the "toggle" command if the toggle1 is LOW
      if (toggle1 == LOW) {
        Serial.println("fire1");
      }
      
      }
    }
    if(reading2 != toggle2){
      toggle2 = reading1;
      if (toggle2 == LOW){
        Serial.println("fire2");
      }
    }
  }
  lasttoggle1 = reading1;
  lasttoggle2 = reading2;
}
