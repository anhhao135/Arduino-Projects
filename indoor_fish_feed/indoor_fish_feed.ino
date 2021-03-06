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
#define servo2_back 2


#define servo1_pin D1
#define servo2_pin D2



Servo servo1;
Servo servo2;


static PCD8544 lcd;


void setup() {


  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );

  }

  timeClient.begin();

  pinMode(D5, OUTPUT);



  delay(1000);
  feed(1);
  delay(1000);
  feed(2);

  Serial.begin(9600);
  


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


  if(day == "Monday" && hour == 10 && minute == 10 && second == 10){

    feed(1);
    feed(2);

  }

  if(day == "Wednesday" && hour == 10 && minute == 10 && second == 10){

    feed(1);
    feed(2);

  }


  if(day == "Friday" && hour == 10 && minute == 10 && second == 10){

    feed(1);
    feed(2);

  }
  
  digitalWrite(D5, HIGH);   // Turn the LED on by making the voltage LOW
  delay(400);                      // Wait for a second
  digitalWrite(D5 , LOW);
  delay(400);
  // Turn the LED off by making the voltage HIGH


Serial.print(hour);
Serial.print(minute);
Serial.print(second);
Serial.println("");
 
  

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
  }
