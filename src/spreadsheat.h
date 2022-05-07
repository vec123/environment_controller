#include "HTTPSRedirect.h"
#include <Arduino.h>

class Spreadsheat_Publisher {
  public:
      char* Spreadsheat_name;
      char* GScriptId;
      // Google Sheets setup (do not edit)
      String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"EnvData_1\", \"values\": ";
      const char* host = "script.google.com";
      const int httpsPort = 443;
      const char* fingerprint = "";
      String url = String("/macros/s/") + GScriptId + "/exec";
      HTTPSRedirect* client = nullptr;
     
      Spreadsheat_Publisher( char* name,  char* ID){
        Spreadsheat_name = name;
        GScriptId = ID;
      }

   void setup(){
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

   void publish(String payload){
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
      Serial.println("Publishing data...");
      //Serial.println(payload);
      if(client->POST(url, host, payload)){ 
        Serial.println("Publish sucess");
      }
      else{
        Serial.println("Error while connecting");
      }
   }
};
