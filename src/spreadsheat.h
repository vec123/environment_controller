#include "HTTPSRedirect.h"

 HTTPSRedirect* spreadshead_setup(){ 
    const char* Spreadsheat_name =  "EnvData_1";
    const char *GScriptId = "AKfycby3x6638FKLE9_wmZMlt9z0zkco-kZxgOcPH8j1TPaeTElOQ2Txv3BuBH0UUe2LkI3w";
    // Google Sheets setup (do not edit)
    String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"EnvData_1\", \"values\": ";

    const char* host = "script.google.com";
    const int httpsPort = 443;
    const char* fingerprint = "";
    String url = String("/macros/s/") + GScriptId + "/exec";
    HTTPSRedirect* client = nullptr;
    return client;
}

 HTTPSRedirect* connect(){
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

void publish_to_spreadshead( HTTPSRedirect*  client, String payload){
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
      
      Serial.println("Publishing data...");
      //Serial.println(payload);
      if(client->POST(url, host, payload)){ 
        // do stuff here if publish was successful
      }
      else{
        // do stuff here if publish was not successful
        Serial.println("Error while connecting");
      }
}