/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin

bool trigger = false;

void setup() {

  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Attach the ESC on pin 9
  ESC.attach(2,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  delay(2000);
  ESC.write(0);
  delay(2000);
  ESC.write(180);
}

void loop() {

  if (digitalRead(A0)){
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(300); // wait for a second
    digitalWrite(LED_BUILTIN, LOW);
    trigger = !trigger;
    delay(200);
  }

  if (trigger){
    int randomNumber = random(0 , 80);

    ESC.write(randomNumber);

    
    
    for (int i = 0; i < 200; i++){
      delay(1);
      if (digitalRead(A0)){
        break;
      }
    }
  }

  if (!trigger){
    ESC.write(0);
  }
  
}
