#include <Arduino.h>
#include <ESPAsyncWebServer.h>

String processor(const String& var){
          //Serial.println(var);
          if(var == "TEMPERATURE"){
            return String(t);
          }
          else if(var == "HUMIDITY"){
              return String(h);
          }
          return String();
    }

AsyncWebServer init_server(){
    return AsyncWebServer server(80);
}


void capture(String field, float value, String processor){
     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/website.html", String(), false, processor);
      });
      // Route to load style.css file
      server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
      });
     // Route for root / web page
      server.on(field, HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String(value).c_str());
      });

}