#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PCD8544.h>
#include <Servo.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>



const char *ssid     = "Lil Wayne's Lil Shack";
const char *password = "Gl4st0nbury";

String last_fed = "Not fed yet";

const long utcOffsetInSeconds = -28800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

LiquidCrystal_I2C lcd(0x27, 20, 4);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

int servo_num = 4; 

int* backPWMArray;
int* frontPWMArray;





void setup() {
  Serial.begin(9600);


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WIFI CONNECTING...");
    delay ( 500 );

  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WIFI CONNECTED!");

  delay(500);

  timeClient.begin();

  pinMode(LED_BUILTIN, OUTPUT);// Initialize the LED_BUILTIN pin as an output
  pinMode(14, INPUT);
  



  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);

  backPWMArray = (int*)calloc(servo_num,sizeof(int));
  frontPWMArray = (int*)calloc(servo_num,sizeof(int));


  for (int i = 0; i < servo_num; i++){

    Serial.println(digitalRead(14));

    while (digitalRead(14)){

      lcd.clear();
      
      int backPWM = analogRead(A0);
      
      lcd.setCursor(0, 0);
      lcd.print(backPWM);
      lcd.setCursor(0, 1);
      lcd.print("back" + String(i));
      
      pwm.setPWM(i, 0, backPWM);

      delay(50);
      
      backPWMArray[i] = backPWM;
      
    }

    delay(200);

    while (digitalRead(14)){

      lcd.clear();
      
      int frontPWM = analogRead(A0);
      
      lcd.setCursor(0, 0);
      lcd.print(frontPWM);
      lcd.setCursor(0, 1);
      lcd.print("front" + String(i));
      
      pwm.setPWM(i, 0, frontPWM);

      delay(50);
      
      frontPWMArray[i] = frontPWM;
      
    }

    delay(200);
    
  }
  
  
  

  
}

void loop() {

  String day;
  int hour;
  int minute;
  int second;

  String date_string;

  lcd.setCursor(0, 0);

  if(WiFi.status() != WL_CONNECTED){
  
    while(WiFi.status() != WL_CONNECTED){
      lcd.clear();
      lcd.print("WIFI CONNECTING...");

      
      digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on by making the voltage LOW
      delay(50);                      // Wait for a second
      digitalWrite(LED_BUILTIN , LOW);
      delay(50);
    }
      
  }

  if(WiFi.status() == WL_CONNECTED){
    timeClient.update();
    day = daysOfTheWeek[timeClient.getDay()];
    hour = timeClient.getHours();
    minute = timeClient.getMinutes();
    second = timeClient.getSeconds();

    date_string = day + " " + String(hour) + ":" + String(minute) + ":" + String(second);
    lcd.clear();
    lcd.print(date_string);
    lcd.setCursor(0,1);
    lcd.print(last_fed);
    delay(10);
  }


  if(day == "Tuesday" && hour == 13 && minute == 30 && second == 0){

    for (int i = 0; i < servo_num; i++){
      feed(i);
    }

    last_fed = "Last fed: " + date_string;
  }

  if(day == "Friday" && hour == 13 && minute == 30 && second == 0){

    for (int i = 0; i < servo_num; i++){
      feed(i);
    }

    last_fed = "Last fed: " + date_string;
  }

  if (!digitalRead(14)){
    for (int i = 0; i < servo_num; i++){
      feed(i);
    }
  }
  
  lcd.setCursor(0, 3);
  lcd.print("haha fish go bloop");
  
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on by making the voltage LOW
  delay(30);                      // Wait for a second
  digitalWrite(LED_BUILTIN , LOW);
  delay(30);
  
}



void feed(int servo_num){

  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Feeding " + String(servo_num));

  pwm.setPWM(servo_num, 0, backPWMArray[servo_num]);
  delay(500);
  pwm.setPWM(servo_num, 0, frontPWMArray[servo_num]);
  delay(500);
}
