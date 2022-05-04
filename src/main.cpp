
#include <Arduino.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>


#include <TempSensors.h>

#define DHTPIN 12   
#define DHTTYPE  DHT11            

DHT dht = DHT_sensor_init(DHTPIN, DHTTYPE);

//variables to capture:
float t = 0.0;
float h = 0.0;

void setup(){
      //DHT-Sensor
      dht = DHT_sensor_setup(dht);
      //Moisture-Sensor   
}

void loop() {

    float t =  DHT_temperature_reader(dht);
    float h =  DHT_humidity_reader(dht);
    
}