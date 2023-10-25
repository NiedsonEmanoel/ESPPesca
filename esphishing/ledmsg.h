#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

const int ledPin =  2;// the number of the LED pin

// Variables will change:
          // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillisw = 0;
// constants won't change:


void ledmsgvoid(){
  unsigned long currentMillis = millis();
  unsigned long currentMillisw = millis();

  if (str(ssid) == str(ssidAttack)){
    if (currentMillis - previousMillis >= 400) {

      // save the last time you blinked the LED
      previousMillis = currentMillis;
      // if the LED is off turn it on and vice-versa:
      if (ledState == 1) {
        digitalWrite(ledPin, 0);
        digitalWrite(13, 0);
        ledState = 0;
      } else {
        digitalWrite(ledPin, 1);
        digitalWrite(13, 1);
        ledState = 1;
      }

      // set the LED with the ledState of the variable:
    }
  }else{
    if (stationConnected){
      digitalWrite(ledPin, 0);
      digitalWrite(13, 0);
      if (currentMillisw - previousMillisw >= 5000) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(ssid);
        previousMillisw = currentMillisw;
      }
    }else{
      digitalWrite(ledPin, 1);
      digitalWrite(13, 1);
      lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)      
      lcd.print("AGUARDANDO  HOST"); 
    }
  }

}
