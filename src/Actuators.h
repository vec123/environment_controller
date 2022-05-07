#include <Arduino.h>
#include <ir_Toshiba.h>

class Actuator{
    public:
        String myName;
        void label(String);
        void setup();
        void action();
};
void Actuator::label(String name){myName = name;}
void Actuator::setup(){}
void Actuator::action(){}

class DigitalOnOffActuator : public Actuator{
    public:
        int myPin;
        void setup(int pin){
            myPin = pin; 
            pinMode(myPin,INPUT); 
        }
        void on(){
            digitalWrite(myPin, HIGH);
        }
        void off(){
            digitalWrite(myPin, HIGH);
        }
};

class OnDuration : public DigitalOnOffActuator{
    public: 
        unsigned long timetracker;
        unsigned long duration; 

        void setup(int pin, unsigned long on_duration){
            myPin = pin; 
            pinMode(myPin,INPUT); 
            timetracker = millis();
            duration = on_duration;
        }
        void on(){
                while (millis() - timetracker <= duration) {
                    digitalWrite(myPin, HIGH);
                } 
                if  (millis() - timetracker > duration){
                    digitalWrite(myPin, LOW);
                }
            timetracker =  millis();
        }
};

class ACActuator : public DigitalOnOffActuator{
    public:
        void on(){
            IRToshibaAC ac(myPin);
            ac.on();
        }
        void set_temp(int setpoint_temp){
            IRToshibaAC ac(myPin);
            ac.setFan(1);
            ac.setMode(kToshibaAcCool);
            ac.setTemp(26);
        }

        void off(){
            IRToshibaAC ac(myPin);
            ac.off();
        }
}; 

class Waterpump : public OnDuration{};
