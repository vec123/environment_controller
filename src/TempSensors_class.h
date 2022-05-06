#include <DHT.h>
#include <Arduino.h>
#include <Sensors.h>

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
        if (isnan(t)) {
          Serial.println("Failed to read from DHT sensor!");
        }
        else {
          Serial.println(t);
        }
         h = dht.readHumidity();
         if (isnan(h)) {
             Serial.println("Failed to read from DHT sensor!");
         }
         else {
              Serial.println(h);
         } 
    }

};


    

