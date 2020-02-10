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



void setup() {

  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );

  }

  timeClient.begin();

  pinMode(D1,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(A0,INPUT);




}

void loop() {

  digitalWrite(D1,HIGH);


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

    water(25);

  }
  
  if(day == "Friday" && hour == 10 && minute == 10 && second == 10){

    water(25);

  }

  
  digitalWrite(D3, HIGH);   // Turn the LED on by making the voltage LOW
  delay(500);                      // Wait for a second
  digitalWrite(D3 , LOW);
  delay(500);


  while(analogRead(A0)>800){

    digitalWrite(D1,LOW);
    delay(200);
    
    
  }
  

  Serial.println(analogRead(A0));




}
}


void water(int seconds){
  digitalWrite(D1,LOW);
  delay(seconds*1000);
  digitalWrite(D1,HIGH); 
}
