#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class Web_handler{
  public:
   // AsyncWebServer server;
    AsyncWebServer init_server();
    void load_sites(AsyncWebServer);
    void get(String, float);
};

//AsyncWebServer Web_handler::init_server(){
//    return AsyncWebServer server(80);
//};

void Web_handler::load_sites(AsyncWebServer server){
      
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Setup_Intro.html", String(), false);
      });
      // Route to load style.css file
      server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
      });
      server.begin();
};

void Web_handler::get(String field, float value){
      // Route to load style.css file
      //server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {                  
        //      if (request->hasParam("ac-onoff")) {
          //            ac_onoff = request->getParam("ac-onoff")->value();
            //        }
              // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
              //if (request->hasParam("ac-temp")) {
                //      ac_commandtemp =  request->getParam("ac-temp")->value().toFloat() ;
                  //  }
              // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
              //if (request->hasParam("water-onoff")) {
                //      waterpump_onoff = request->getParam("water-onoff")->value();
                  //  }           
      //});
     // server.begin()
};