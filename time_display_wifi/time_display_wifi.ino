#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const char *ssid     = "Lil Wayne's Lil Shack";
const char *password = "Gl4st0nbury";

const long utcOffsetInSeconds = -28800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("test");

  Serial.begin(115200);



  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );

  }

  timeClient.begin();



}

void loop() {

  timeClient.update();

  lcd.clear();
  lcd.print(timeClient.getFormattedTime());

  delay(100);

  /*
  String day = daysOfTheWeek[timeClient.getDay()];
  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();
  int second = timeClient.getSeconds();

  Serial.println(hour);
  Serial.println(minute);
  Serial.println(second);
  Serial.println("--");

  */


  

  

}
