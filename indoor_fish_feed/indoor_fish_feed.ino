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

#define servo1_back 105
#define servo2_back 158
#define servo3_back 39

#define servo1_pin D3
#define servo2_pin D4
#define servo3_pin D1


Servo servo1;
Servo servo2;
Servo servo3;

static PCD8544 lcd;

void setup() {


  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );

  }

  timeClient.begin();

  pinMode(D5, OUTPUT);


}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, password);
  }

  if(WiFi.status() == WL_CONNECTED){

  
  timeClient.update();
  String day = daysOfTheWeek[timeClient.getDay()];
  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();
  int second = timeClient.getSeconds();


  if(day == "Monday" && hour == 10 && minute == 10 && second == 10){

    feed(1);
    feed(2);

  }

  if(day == "Thursday" && hour == 10 && minute == 10 && second == 10){

    feed(1);
    feed(2);

  }

  if(day == "Tuesday" && hour == 13 && minute == 30 && second == 0){

    feed(3);
  }

  if(day == "Friday" && hour == 13 && minute == 30 && second == 0){

    feed(3);
  }

  if(day == "Sunday" && hour == 13 && minute == 30 && second == 0){

    feed(3);
  }
  
  digitalWrite(D5, HIGH);   // Turn the LED on by making the voltage LOW
  delay(500);                      // Wait for a second
  digitalWrite(D5 , LOW);
  delay(500);
  // Turn the LED off by making the voltage HIGH

  

}

}


void feed(int servo_num){

  if(servo_num==1){
    servo1.attach(servo1_pin);
    servo1.write(servo1_back);
    delay(1000);
    servo1.write(servo1_back + 20);
    delay(1000);
    servo1.write(servo1_back);
    delay(1000);
    servo1.detach();
  }

  if(servo_num==2){
    servo2.attach(servo2_pin);
    servo2.write(servo2_back);
    delay(1000);
    servo2.write(servo2_back + 20);
    delay(1000);
    servo2.write(servo2_back);
    delay(1000);
    servo2.detach();
  }

  if(servo_num==3){
for (int i = 0; i<1; i++){
    servo3.attach(servo3_pin);
    servo3.write(servo3_back + 20);
    delay(1000);
    servo3.write(servo3_back);
    delay(1000);
    servo3.write(servo3_back + 20);
    delay(1000);
    servo3.detach();
   }
  }
  }
