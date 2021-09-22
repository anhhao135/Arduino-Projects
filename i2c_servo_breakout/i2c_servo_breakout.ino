
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

void setup() {


  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  // put your setup code here, to run once:

}

void loop() {

  for (int i = 9; i < 16; i++){
  
    pwm.setPWM(i, 4096, 0);
    delay(20);
    pwm.setPWM(i, 0, 4096);
    delay(20);
    
  }


  // put your main code here, to run repeatedly:

}
