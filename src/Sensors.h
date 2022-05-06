#include <Arduino.h>
#include <DHT.h>

class Sensor{
    public:
        String myName;
        void label(String);
        void setup();
        void read();
};

void Sensor::label(String name){myName = name;}
void Sensor::setup(){}
void Sensor::read(){}

class stdAnalogSensor : public Sensor{
    public:
        float myValue;
        int myPin;
        void setup(int pin){
            myPin = pin; 
            pinMode(myPin,INPUT); 
        }
        void read(){
          myValue = analogRead(myPin);
          if (isnan(myValue)) {Serial.println("Failed to read from Sensor!");}
          else {Serial.println(myValue);}
        }
};

class stdDigitalSensor : public Sensor{
    public:
        float myValue;
        int myPin;
        void setup(int pin){
            myPin = pin; 
            pinMode(myPin,INPUT); 
        }
        void read(){
          myValue = digitalRead(myPin);
          if (isnan(myValue)) {Serial.println("Failed to read from Sensor!");}
          else {Serial.println(myValue);}
        }
};
