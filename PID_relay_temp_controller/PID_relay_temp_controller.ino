#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <PID_v1.h>
#define RelayPin 6

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, 6, 2, 0, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;
void setup()
{
  pinMode(RelayPin, OUTPUT);

  windowStartTime = millis();

  //initialize the variables we're linked to


  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(-20, 20);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  dht.begin();

  Setpoint = 86;
    
  Serial.begin(9600);
}

void loop()
{

  double t = dht.readTemperature();
  t = (t*1.8)+32;
  t = t+5;
  Input = t;
  myPID.Compute();
  Serial.println(t);
  Serial.println(Output);

  /************************************************
     turn the output pin on/off based on pid output
   ************************************************/

/*
  unsigned long now = millis();
  if (now - windowStartTime > WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (Output > now - windowStartTime){
    digitalWrite(RelayPin, HIGH);

  }
  else{
    digitalWrite(RelayPin, LOW);

  }

*/


  if (Output>0){
    digitalWrite(RelayPin,LOW);
  }
  else{
    digitalWrite(RelayPin,HIGH);
  }

  delay(500);

  
}
