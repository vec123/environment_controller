#include <DHT.h>
#include <Arduino.h>

class Dht_sensor {
 
  public:    
    int t; 
    int h;
    int DHTPIN;
    unsigned char DHTTYPE;
    void setup_sensor(int, unsigned char);
    void DHT_temperature_reader();
    void DHT_humidity_reader();
};

    void Dht_sensor::setup_sensor(int pin, unsigned char type){
      DHTPIN = pin;
      DHTTYPE = type;     
    }

    void Dht_sensor::DHT_temperature_reader(){  
        DHT dht( DHTPIN,  DHTTYPE);
        t = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      //float newT = dht.readTemperature(true);
      // if temperature read failed, don't change t value
        if (isnan(t)) {
          Serial.println("Failed to read from DHT sensor!");
        }
        else {
          Serial.println(t);
        }
        //return t;
     }

     void Dht_sensor::DHT_humidity_reader(){  
            DHT dht(DHTPIN, DHTTYPE);
            h = dht.readHumidity();
            // Read temperature as Fahrenheit (isFahrenheit = true)
            //float newT = dht.readTemperature(true);
            // if temperature read failed, don't change t value
              if (isnan(h)) {
                Serial.println("Failed to read from DHT sensor!");
              }
              else {
                 Serial.println(h);
              }
              //return h;
    }

