class Actuator{
    public:
        String myName;
        void label(String);
        void setup();
        void action();
};

void Sensor::label(String name){myName = name;}
void Sensor::setup(){}
void Sensor::read(){}
