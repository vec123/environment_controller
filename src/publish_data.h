#include "HTTPSRedirect.h"
#include <Arduino.h>

class Spreadsheat_Publisher {
  public:
      const char* Spreadsheat_name;
      const char* GScriptId;
      String payload_base;  
      String command;
      const char* host = "script.google.com";
      const int httpsPort = 443;
      const char* fingerprint = "";
      String url;
      HTTPSRedirect* client = nullptr;
    
      void setup();
      void publish(String, String);

      Spreadsheat_Publisher(const char* name, const char* ID){
        Spreadsheat_name = name;
        GScriptId = ID ;
        url = String("/macros/s/") + GScriptId + "/exec";
      }
};

void Spreadsheat_Publisher::setup(){
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


void Spreadsheat_Publisher::publish(String payload, String command){
   
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
     // payload  =  "{\"command\": \"not_set\", \"sheet_name\": \"EnvData_1\", \"values\": ";
      String data_pack = "{\"command\": \"" + command + "\"" + ", " + "\"sheet_name\": \"" + Spreadsheat_name + "\"" + ", " + "\"values\": " + payload; 

      Serial.println("Publishing data...");
      Serial.println(data_pack); 
      if(client->POST(url, host, data_pack)){ 
        Serial.println("Publish sucess");
      }
      else{
        Serial.println("Error while connecting");
      }
   }