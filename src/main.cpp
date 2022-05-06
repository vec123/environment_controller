
#include <Arduino.h>
#include <TempSensors.h>
#include <Moisturesensors.h>

#define DHTPIN 12   
#define DHTTYPE DHT11            
#define MoisturePIN A0

Dht_sensor dht1;
Moisture_sensor earth1;


void setup(){
  
    //DHT-Sensor 
    dht1.setup(DHTPIN, DHTTYPE);
    earth1.label("first temp sensor");

    earth1.setup(MoisturePIN);
    earth1.label("first moisture sensor");
}

void loop() {
   //Blink builtin LED
  
    dht1.read();
    earth1.read();
    Serial.println(dht1.t);
    Serial.println(dht1.h);
    Serial.println(earth1.myValue);
}