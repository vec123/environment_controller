
#include <Arduino.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <functions.h>

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Toshiba.h>
#include <FS.h>

#define LED 2
#define DHTPIN 12          
#define InfarredLED 4
#define WaterPumpPIN 5


#define DHTTYPE    DHT11     

int MoisturePIN = A0;
int moisture_value = 0;

// Replace with your network credentials

const char* ssid = "Vodafonemagneticjesus";
const char* password = "Inthelandofnails:)";

float t = 0.0;
float h = 0.0;
String waterpump_onoff = "off";
String ac_onoff = "off";
float ac_commandtemp = 25;

unsigned long previousMillis = 0;
const long interval = 100; 


//const char* ssid = "Redmi 10";
//const char* password = "bu5tfzaaxav9r5b";

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);
IRToshibaAC ac(InfarredLED); 

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


/* 
- would like to use in main and eventually move to header but does not work
void server_setup(AsyncWebServer server){
      Serial.print("1");
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/website.html", String(), false, processor);
      });
      Serial.print("2");
      // Route to load style.css file
      server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
      });
     // Route for root / web page
      server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String(t).c_str());
      });
      server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", String(h).c_str());
      });
      server.begin();
  }
*/


#include "HTTPSRedirect.h"
const char* Spreadsheat_name =  "EnvData_1";
const char *GScriptId = "AKfycby3x6638FKLE9_wmZMlt9z0zkco-kZxgOcPH8j1TPaeTElOQ2Txv3BuBH0UUe2LkI3w";
// Google Sheets setup (do not edit)
String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"EnvData_1\", \"values\": ";
String payload = "";
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

void setup(){

      Serial.begin(115200);

      /*-Setups in order:
          -WiFi
          -SPIFFS
          -HTML-server
          -AC
          -DHT-sensor
          -Infarred LED
          -builtin LED
    */

      //WiFi
      WiFi_setup(ssid, password);
      Serial.print(WiFi.localIP());

     //SPIFFS
      Serial.print("0");
      if(!SPIFFS.begin()){
           Serial.println("An Error has occurred while mounting SPIFFS");
          return;
      }

      //HTML-server
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/website.html", String(), false, processor);
      });
      // Route to load style.css file
      server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
      });
     // Route for root / web page
      server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String(t).c_str());
      });
      server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", String(h).c_str());
      });

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

    server.begin();


      //AC
      ac.on();
      ac.setFan(1);
      ac.setMode(kToshibaAcCool);
      ac.setTemp(26);

      //DHT-Sensor
      dht.begin();
      //Moisture-Sensor
      pinMode(MoisturePIN,INPUT);

      //infarredLED
      pinMode(InfarredLED, OUTPUT);

      //buildin LED
      pinMode(LED, OUTPUT);
      
      //buildin LED
      pinMode(WaterPumpPIN, OUTPUT);

      delay(3000);
      //HTTPS-redirect
        client = new HTTPSRedirect(httpsPort);
        client->setInsecure();
        client->setPrintResponseBody(true);
        client->setContentTypeHeader("application/json");
  

        Serial.print("Connecting to ");
        Serial.println(host);

        // Try to connect for a maximum of 5 times
        bool flag = false;
        for (int i=0; i<5; i++){ 
          int retval = client->connect(host, httpsPort);
          if (retval == 1){
            flag = true;
            Serial.println("Connected");
            break;
          }
          else
            Serial.println("Connection failed. Retrying...");
        }
        if (!flag){
          Serial.print("Could not connect to server: ");
          Serial.println(host);
          return;
        }
        delete client;    // delete HTTPSRedirect object
        client = nullptr; // delete HTTPSRedirect object





}

void loop() {
   //Blink builtin LED
   digitalWrite(LED, HIGH);
   delay(1000);
   digitalWrite(LED, LOW);
   delay(1000);

  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    // Read temperature as Celsius (the default)
    t =  DHT_temperature_reader(dht);
    h =  DHT_humidity_reader(dht);
    moisture_value = Moisture_reader(MoisturePIN);
    
    if ( waterpump_onoff.equals("on")){
      digitalWrite(WaterPumpPIN, LOW);
      Serial.println("Set to Low");
    }
    else if ( waterpump_onoff.equals("off")){
      digitalWrite(WaterPumpPIN, HIGH);
      Serial.println("Set to High");
    }
     

    if (ac_onoff == "on"){
      //Send AC-Temperature
      ac.setTemp(int(ac_commandtemp));
      ac.send();
      //#if SEND_TOSHIBA_AC
      //Serial.println("Sending IR command to A/C ...");
      //ac.setTemp(26);
      //ac.send();
      // #endif 
    }
    else if (ac_onoff == "off"){
      //turn AC off
      //TODO
    }

    Serial.println("temp value [in C]:");
    Serial.println(t);
    Serial.println("hum value [in %]:");
    Serial.println(h);
    Serial.println("moisture value [in RH]:");
    Serial.println(moisture_value);
    Serial.println("ac_onnoff [on,off]:");
    Serial.println(ac_onoff);
    Serial.println("ac_commandtemp [in C]:");
    Serial.println(ac_commandtemp);
    Serial.println("water_onoff [on,off]:");
    Serial.println(waterpump_onoff);

  }
   


  // Publish data to Google Sheets

  static bool flag = false;
  if (!flag){
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr){
    if (!client->connected()){
      client->connect(host, httpsPort);
    }
  }
  else{
    Serial.println("Error creating client object!");
  }


  // Create json object string to send to Google Sheets
  payload = payload_base + "\"" + t + "," + h + "," + ac_onoff + "," + ac_commandtemp + "," + moisture_value + "," + waterpump_onoff + " \" }";
  
  Serial.println("Publishing data...");
  //Serial.println(payload);
  if(client->POST(url, host, payload)){ 
     // do stuff here if publish was successful
  }
  else{
    // do stuff here if publish was not successful
    Serial.println("Error while connecting");
  }


  delay(5000);

}