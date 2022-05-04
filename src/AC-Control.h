#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Toshiba.h>

IRToshibaAC init_IR_AC_Control(int InfarredLED){
   pinMode(InfarredLED, OUTPUT);
   IRToshibaAC ac(InfarredLED);
   return ac; 
}

IRToshibaAC AC_setup(IRToshibaAC ac){
      ac.on();
      ac.setFan(1);
      ac.setMode(kToshibaAcCool);
      ac.setTemp(26);
      return ac;
}

IRToshibaAC AC_control(IRToshibaAC ac, int command_temp, bool ac_onoff){
    if (ac_onoff == true){
      //Send AC-Temperature
      ac.setTemp(int(command_temp));
      ac.send();
      //#if SEND_TOSHIBA_AC
      //Serial.println("Sending IR command to A/C ...");
      //ac.setTemp(26);
      //ac.send();
      // #endif 
    }
    else if (ac_onoff == false){
      //turn AC off
      ac.off();
    }
    return ac;
 }

