#include <Arduino.h>

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

class Moisture_sensor : public stdAnalogSensor {
};

#include <DHT.h>
class Dht_sensor : public Sensor {

  public:    
    int t; 
    int h;
    int DHTPIN;
    unsigned char DHTTYPE;
    
    void setup(int pin, unsigned char type){
      DHTPIN = pin;
      DHTTYPE = type;     
    }

    void read(){
        DHT dht( DHTPIN,  DHTTYPE);

        t = dht.readTemperature();
        if (isnan(t)) {Serial.println("Failed to read from DHT sensor!");}
        else {Serial.println(t);}

        h = dht.readHumidity();
        if (isnan(h)) {Serial.println("Failed to read from DHT sensor!");}
        else {Serial.println(h);} 
    }

};
