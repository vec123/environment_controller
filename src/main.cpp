
#include <Arduino.h>
#include <Sensors.h>
#include <Actuators.h>
#include <Spreadsheat.h>

#define DHTPIN 12   
#define DHTTYPE DHT11            
#define MoisturePIN A0
#define WaterPumpPIN 5
#define InfarredLED 4

Dht_sensor dht1;
Moisture_sensor earth1;
Waterpump pump1; 
ACActuator ac1;
Spreadsheat_Publisher publisher("EnvData_1", "AKfycby3x6638FKLE9_wmZMlt9z0zkco-kZxgOcPH8j1TPaeTElOQ2Txv3BuBH0UUe2LkI3w");

int moisture_threshold = 30;
int desired_room_temp = 25;
int upper_temp_threshold = desired_room_temp + 1;
int lower_temp_threshold = desired_room_temp - 1;

void setup(){  
    dht1.setup(DHTPIN, DHTTYPE);
    dht1.label("first temp sensor");

    earth1.setup(MoisturePIN);
    earth1.label("first moisture sensor");

    pump1.setup(WaterPumpPIN,1000);
    pump1.label("first water pump");

    ac1.setup(InfarredLED);
    ac1.label("first AC");
}

void loop() {
    dht1.read();
    earth1.read();
    if(earth1.myValue <= moisture_threshold)
        { pump1.on(); }
    if(dht1.t >= upper_temp_threshold ||  dht1.t <= lower_temp_threshold)
        { ac1.set_temp(desired_room_temp); }
    Serial.println(dht1.t);
    Serial.println(dht1.h);
    Serial.println(earth1.myValue);

    String payload = publisher.payload_base + "\"" + dht1.t + "," + dht1.h + " \" }"; 
    publisher.publish(payload);
}