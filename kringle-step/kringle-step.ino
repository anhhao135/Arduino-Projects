/* Example sketch to control a 28BYJ-48 stepper motor with ULN2003 driver board and Arduino UNO. More info: https://www.makerguides.com */

// Include the Arduino Stepper.h library:
#include <Stepper.h>

// Define number of steps per rotation:
const int stepsPerRevolution = 2038;

// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 5, 3, 4, 2);

void setup() {
  // Set the speed to 5 rpm:
  myStepper.setSpeed(5);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

void loop() {
  // Step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);

}
