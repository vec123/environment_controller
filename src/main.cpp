
#include <Arduino.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <TempSensors_class.h>

#define DHTPIN 12   
#define DHTTYPE  DHT11            

Dht_sensor dht1;

//variables to capture:
String processor(const String& var){
          //Serial.println(var);
          if(var == "TEMPERATURE"){
            return String(dht1.t);
          }
          else if(var == "HUMIDITY"){
              return String(dht1.h);
          }
          return String();
    }



void setup(){

    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    //DHT-Sensor 
    dht1.setup_sensor(DHTPIN, DHTTYPE);


    //capture-values:
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/website.html", String(), false, processor);
      });
      // Route to load style.css file
      server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
      });
     // Route for root / web page
      server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String(dht1.t).c_str());
      });
      server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", String(dht1.h).c_str());
      });

    //recieve-values:
      server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {                  
              if (request->hasParam("ac-onoff")) {
                      ac_onoff = request->getParam("ac-onoff")->value();
                    }
              // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
              if (request->hasParam("ac-temp")) {
                      ac_commandtemp =  request->getParam("ac-temp")->value().toFloat() ;
                    }
              // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
              if (request->hasParam("water-onoff")) {
                      waterpump_onoff = request->getParam("water-onoff")->value();
                    }           
      });
      server.begin()
}

void loop() {

    dht1.DHT_temperature_reader();
    dht1.DHT_humidity_reader();
    Serial.println(dht1.t);
    Serial.println(dht1.h);
}