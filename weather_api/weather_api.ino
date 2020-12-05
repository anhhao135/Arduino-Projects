 /*
  * Author: Emmanuel Odunlade 
  * Complete Project Details https://randomnerdtutorials.com
  */
  
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const long utcOffsetInSeconds = -28800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


// Replace with your SSID and password details
char ssid[] = "Lil Wayne's Lil Shack";        
char pass[] = "Gl4st0nbury";   

WiFiClient client;

// Open Weather Map API server name
const char server[] = "api.openweathermap.org";

// Replace the next line to match your city and 2 letter country code
String nameOfCity = "London,UK"; 
// How your nameOfCity variable would look like for Lagos on Nigeria
//String nameOfCity = "Lagos,NG"; 

// Replace the next line with your API Key
String apiKey = "ec06d0c044d2746881fd12b1a90f76f6"; 

String text;

int jsonend = 0;
boolean startJson = false;
int status = WL_IDLE_STATUS;

int rainLed = 2;  // Indicates rain
int clearLed = 3; // Indicates clear sky or sunny
int snowLed = 4;  // Indicates snow
int hailLed = 5;  // Indicates hail

#define JSON_BUFF_DIMENSION 2500

unsigned long lastConnectionTime = 10 * 60 * 1000;     // last time you connected to the server, in milliseconds
const unsigned long postInterval = 10 * 60 * 1000;  // posting interval of 10 minutes  (10L * 1000L; 10 seconds delay for testing)

float currentTemp;
float currentHumidity;
String currentWeather;

void setup() {


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("test");
  
  pinMode(clearLed, OUTPUT);
  pinMode(rainLed, OUTPUT);
  pinMode(snowLed, OUTPUT);
  pinMode(hailLed, OUTPUT);
  Serial.begin(115200);
  
  text.reserve(JSON_BUFF_DIMENSION);
  
  WiFi.begin(ssid,pass);
  Serial.println("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  printWiFiStatus();
  Serial.println("Request");

  
  timeClient.begin();
}

void loop() { 

  Serial.println("loop");

  timeClient.update();

  lcd.clear();
  lcd.print(timeClient.getFormattedTime());

  
  //OWM requires 10mins between request intervals
  //check if 10mins has passed then conect again and pull
  if (millis() - lastConnectionTime > postInterval) {
    // note the time that the connection was made:
    lastConnectionTime = millis();
    makehttpRequest();
  }

  lcd.setCursor(0, 1);
  lcd.print(String(currentTemp) + 'F');
  lcd.setCursor(0, 2);
  lcd.print(String(currentHumidity) + '%');
  lcd.setCursor(0, 3);
  lcd.print(currentWeather);

  delay(200);
}

// print Wifi status
void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

// to request data from OWM
void makehttpRequest() {
  // close any connection before send a new request to allow client make connection to server
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {

    
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET /data/2.5/forecast?q=" + nameOfCity + "&APPID=" + apiKey + "&mode=json&units=metric&cnt=2 HTTP/1.1");
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
    
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    
    char c = 0;
    while (client.available()) {
      c = client.read();
      // since json contains equal number of open and close curly brackets, this means we can determine when a json is completely received  by counting
      // the open and close occurences,
      //Serial.print(c);
      if (c == '{') {
        startJson = true;         // set startJson true to indicate json message has started
        jsonend++;
      }
      if (c == '}') {
        jsonend--;
      }
      if (startJson == true) {
        text += c;
      }
      // if jsonend = 0 then we have have received equal number of curly braces 
      if (jsonend == 0 && startJson == true) {
        parseJson(text.c_str());  // parse c string text in parseJson function
        text = "";                // clear text string for the next time
        startJson = false;        // set startJson to false to indicate that a new message has not yet started
      }
    }
  }
  else {
    // if no connction was made:
    Serial.println("connection failed");
    return;
  }
}

//to parse json data recieved from OWM
void parseJson(const char * jsonString) {
  //StaticJsonBuffer<4000> jsonBuffer;
  const size_t bufferSize = 2*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + 4*JSON_OBJECT_SIZE(1) + 3*JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 2*JSON_OBJECT_SIZE(7) + 2*JSON_OBJECT_SIZE(8) + 720;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  // FIND FIELDS IN JSON TREE
  JsonObject& root = jsonBuffer.parseObject(jsonString);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  JsonArray& list = root["list"];
  JsonObject& nowT = list[0];
  JsonObject& later = list[1];

  // including temperature and humidity for those who may wish to hack it in
  
  String city = root["city"]["name"];

  Serial.println(city);
  
  float tempNow = nowT["main"]["temp"];
  tempNow = (tempNow * (9/5)) + 32;
  float humidityNow = nowT["main"]["humidity"];
  String weatherNow = nowT["weather"][0]["description"];

  currentTemp = tempNow;
  currentHumidity = humidityNow;
  currentWeather = weatherNow;
 

  Serial.println(tempNow);
  Serial.println(humidityNow);
  Serial.println(weatherNow);

  float tempLater = later["main"]["temp"];
  float humidityLater = later["main"]["humidity"];
  String weatherLater = later["weather"][0]["description"];

  // checking for four main weather possibilities
  diffDataAction(weatherNow, weatherLater, "clear");
  diffDataAction(weatherNow, weatherLater, "rain");
  diffDataAction(weatherNow, weatherLater, "snow");
  diffDataAction(weatherNow, weatherLater, "hail");
  
  Serial.println();
}

//representing the data
void diffDataAction(String nowT, String later, String weatherType) {
  int indexNow = nowT.indexOf(weatherType);
  int indexLater = later.indexOf(weatherType);
  // if weather type = rain, if the current weather does not contain the weather type and the later message does, send notification
  if (weatherType == "rain") { 
    if (indexNow == -1 && indexLater != -1) {
      digitalWrite(rainLed,HIGH);
      digitalWrite(clearLed,LOW);
      digitalWrite(snowLed,LOW);
      digitalWrite(hailLed,LOW);
      Serial.println("Oh no! It is going to " + weatherType + " later! Predicted " + later);
    }
  }
  // for snow
  else if (weatherType == "snow") {
    if (indexNow == -1 && indexLater != -1) {
      digitalWrite(snowLed,HIGH);
      digitalWrite(clearLed,LOW);
      digitalWrite(rainLed,LOW);
      digitalWrite(hailLed,LOW);
      Serial.println("Oh no! It is going to " + weatherType + " later! Predicted " + later);
    }
    
  }
  // can't remember last time I saw hail anywhere but just in case
  else if (weatherType == "hail") { 
   if (indexNow == -1 && indexLater != -1) {
      digitalWrite(hailLed,HIGH);
      digitalWrite(clearLed,LOW);
      digitalWrite(rainLed,LOW);
      digitalWrite(snowLed,LOW);
      Serial.println("Oh no! It is going to " + weatherType + " later! Predicted " + later);
   }

  }
  // for clear sky, if the current weather does not contain the word clear and the later message does, send notification that it will be sunny later
  else {
    if (indexNow == -1 && indexLater != -1) {
      Serial.println("It is going to be sunny later! Predicted " + later);
      digitalWrite(clearLed,HIGH);
      digitalWrite(rainLed,LOW);
      digitalWrite(snowLed,LOW);
      digitalWrite(hailLed,LOW);
    }
  }
}
