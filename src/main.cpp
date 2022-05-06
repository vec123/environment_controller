
#include <Arduino.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <TempSensors_class.h>

#define DHTPIN 12   
#define DHTTYPE  DHT11            

Dht_sensor dht1;




void setup(){
  
    //DHT-Sensor 
    dht1.setup(DHTPIN, DHTTYPE);
}

void loop() {
   //Blink builtin LED
  
    dht1.read();
    Serial.println(dht1.t);
    Serial.println(dht1.h);
}