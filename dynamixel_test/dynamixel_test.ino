#include <SoftwareSerial.h>
#include <DynamixelShield.h>



SoftwareSerial soft_serial(7, 8);


void setup(){

  soft_serial.begin(115200);
  
}

void loop(){

  delay(1000);
  soft_serial.println("sonia");
  
}
