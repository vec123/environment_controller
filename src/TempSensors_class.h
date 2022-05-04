#include <DHT.h>
#include <Arduino.h>

class Dth_sensor {
  DHT dht(DHTPIN, DHTTYPE);

  public:    
    // DHT DHT_sensor_init(int, int);
    int DHT_temperature_reader(dht);
    int DHT_humidity_reader(dht);s
}

void Dth_sensor::DHT_sensor_init(int DHTPIN, int DHTTYPE){
    DHT dht(DHTPIN, DHTTYPE);
    return dht;
}

DHT  Dth_sensor::DHT_sensor_setup(DHT dht){
    dht.begin();
    return dht;
}

float Dth_sensor::DHT_temperature_reader(DHT dht){  
      float newD = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      //float newT = dht.readTemperature(true);
      // if temperature read failed, don't change t value
        if (isnan(newD)) {
          Serial.println("Failed to read from DHT sensor!");
        }
        else {
         // Serial.println(newD);
        }
        return newD;
 }

float Dth_sensor::DHT_humidity_reader(DHT dht){  
      float newD = dht.readHumidity();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      //float newT = dht.readTemperature(true);
      // if temperature read failed, don't change t value
        if (isnan(newD)) {
          Serial.println("Failed to read from DHT sensor!");
        }
        else {
          // Serial.println(newD);
        }
        return newD;
 }