#include <DHT.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>

 float DHT_temperature_reader(DHT dht){  
      float newD = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      //float newT = dht.readTemperature(true);
      // if temperature read failed, don't change t value
        if (isnan(newD)) {
          Serial.println("Failed to read from DHT sensor!");
        }
        else {
         // Serial.println(newD);
        }
        return newD;
 }

 float DHT_humidity_reader(DHT dht){  
      float newD = dht.readHumidity();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      //float newT = dht.readTemperature(true);
      // if temperature read failed, don't change t value
        if (isnan(newD)) {
          Serial.println("Failed to read from DHT sensor!");
        }
        else {
          // Serial.println(newD);
        }
        return newD;
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

void WiFi_setup(const char* ssid,const char* password){

      WiFi.begin(ssid, password);
      Serial.println("Connecting to WiFi");
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println(".");
      }
    Serial.println(WiFi.localIP());
}





