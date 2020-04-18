#include <PCD8544.h>
#include <Servo.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "Lil Wayne's Lil Shack";
const char *password = "Gl4st0nbury";

const long utcOffsetInSeconds = -28800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

#define servo1_back 2 
#define servo1_pin D1

Servo servo1;

void setup() {

  Serial.begin(115200);


  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );

  }

  timeClient.begin();

  pinMode(D5, OUTPUT);

  feed(1);


}

void loop() {

  if(WiFi.status() != WL_CONNECTED){

    

        


  while(WiFi.status() != WL_CONNECTED){
  digitalWrite(D5, HIGH);   // Turn the LED on by making the voltage LOW
  delay(100);                      // Wait for a second
  digitalWrite(D5 , LOW);
  delay(100);
  }
      
  }

  
  if(WiFi.status() == WL_CONNECTED){

  
  timeClient.update();
  String day = daysOfTheWeek[timeClient.getDay()];
  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();
  int second = timeClient.getSeconds();

  Serial.println(hour);
  Serial.println(minute);
  Serial.println(second);
  Serial.println("--");

 

  if(day == "Tuesday" && hour == 13 && minute == 30 && second == 0){

    feed(1);
  }

  if(day == "Friday" && hour == 13 && minute == 30 && second == 0){

    feed(1);
  }

  if(day == "Saturday" && hour == 13 && minute == 30 && second == 0){

    feed(1);
  }

  
  digitalWrite(D5, HIGH);   // Turn the LED on by making the voltage LOW
  delay(400);
  Serial.println("LED");
  // Wait for a second
  digitalWrite(D5, LOW);  // Turn the LED off by making the voltage HIGH
  delay(400);
  

}


}



void feed(int servo_num){


for (int i = 0; i<2; i++){
  if(servo_num==1){
    servo1.attach(servo1_pin);
    servo1.write(servo1_back + 50);
    delay(1000);
    servo1.write(servo1_back);
    delay(1000);
    servo1.write(servo1_back + 50);
    delay(1000);
    servo1.detach();
   }
  }

}
