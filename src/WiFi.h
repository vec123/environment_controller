#include <Arduino.h>
//#include <ESPAsyncTCP.h>
#include <ESP8266WiFi.h>

void WiFi_setup(const char* ssid, const char* password){

      WiFi.begin(ssid, password);
      Serial.println("Connecting to WiFi");
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println(".");
      }
    Serial.println(WiFi.localIP());
}
