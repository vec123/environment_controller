#include <Arduino.h>

 void Setup_moisture_reader(int PIN){
      pinMode(PIN,INPUT);
 }

 int Moisture_reader(int MoisturePIN){  
          int newD = analogRead(MoisturePIN);
          if (isnan(newD)) {
               Serial.println("Failed to read from Moisture sensor!");
          }
          else {
          // Serial.println(newD);
          }
        return newD;
 }