
#include <Arduino.h>
#include <Sensors.h>
#include <Actuators.h>
#include <publish_data.h>
#include <ESPAsyncTCP.h>
#include <WiFi.h>

#define DHTPIN 12
#define DHTTYPE DHT11
#define MoisturePIN A0
#define WaterPumpPIN 5
#define InfarredLED 4
#define LED 2

Dht_sensor dht1;
Moisture_sensor earth1;
Waterpump pump1;
ACActuator ac1;
Spreadsheat_Publisher publisher("EnvData_1", "AKfycbyBYzUiXjYnOUgKIMmJ5ovr9txebh43ntbn2m96nGGbLCTNULVZMsZmkWS9kKQGWwqe");

int moisture_threshold = 30;
int desired_room_temp = 25;
int upper_temp_threshold = desired_room_temp + 1;
int lower_temp_threshold = desired_room_temp - 1;

const char* ssid = "Vodafone-B0F4";
const char* password = "tmUM66hFETHN3uTd";

void setup(){
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    
    WiFi_setup(ssid, password);
    Serial.print(WiFi.localIP());

    dht1.setup(DHTPIN, DHTTYPE);
    dht1.label("first temp sensor");

    earth1.setup(MoisturePIN);
    earth1.label("first moisture sensor");

    pump1.setup(WaterPumpPIN,1000);
    pump1.label("first water pump");

    ac1.setup(InfarredLED);
    ac1.label("first AC");

    publisher.setup();
    String payload = String("\"") + "Date" + "," + "Time" + "," + "Temperature" + "," + "Humidity" +  "," + "Earth_Moisture" + " \" }"; 
    publisher.publish(payload, "set_title");
}

void loop() {
    Serial.println("loop");
   //Blink builtin LED
   digitalWrite(LED, HIGH);
   delay(1000);
   digitalWrite(LED, LOW);
   delay(1000);

    dht1.read();
    earth1.read();
    if(earth1.myValue <= moisture_threshold)
        { pump1.on(); }
    if(dht1.t >= upper_temp_threshold ||  dht1.t <= lower_temp_threshold)
        { ac1.set_temp(desired_room_temp); }
    Serial.println(dht1.t);
    Serial.println(dht1.h);
    Serial.println(earth1.myValue);

    // String payload = String("\"") + dht1.t + "," + dht1.h +  " \" }"; 
    String payload = String("\"") + dht1.t + "," + dht1.h +  "," + earth1.myValue + " \" }"; 
    publisher.publish(payload,  "insert_row");
}