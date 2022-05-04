#include <Arduino.h>


 void Waterpump_setup(int PIN){
      pinMode(PIN,INPUT);
 }

void Waterpump_onoff(int PIN, bool onoff){
    if ( onoff == true){
      digitalWrite(PIN, LOW);
      Serial.println("Set to Low");
    }
    else if ( onoff == false){
      digitalWrite(PIN, HIGH);
      Serial.println("Set to High");
    }
     
}