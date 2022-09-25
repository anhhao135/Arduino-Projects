
#include<Wire.h>

#include <filters.h>

const float cutoff_freq   = 30;  //Cutoff frequency in Hz
const float sampling_time = 0.001; //Sampling time in seconds.
IIR::ORDER  order  = IIR::ORDER::OD3; // Order (OD1 to OD4)

// Low-pass filter
Filter f(cutoff_freq, sampling_time, order);

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;


int a1 = 9;
int b1 = 8;
int c1 = 7;
int d1 = 6; //top display

int a2 = 5;
int b2 = 3;
int c2 = 2;
int d2 = 4; //bottom display


int counter = 0;



void setup() {

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);

  pinMode(10, OUTPUT);

  digitalWrite(10,HIGH);


  for (int i = 0; i < 100; i ++){
    displayNumber(i);
    delay(25);
  }
}
 
void loop() {

  digitalWrite(10,HIGH);

  int delayTime = 1000;

  for(int i=0; i < 100; i++){
    int randomNum = random(0,100);
    
    displayNumber(randomNum);
    
    delay(delayTime);

    delayTime = delayTime * 0.95;
  }

  

  


  /*

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  float y_lpf = f.filterIn(y);

  


  if (y_lpf > 225 && y_lpf < 270){
    

    displayNumber(counter % 99);
    counter ++;
    delay(100);
    digitalWrite(10,HIGH);
  }

  else{
    digitalWrite(10,LOW);
  }


  */

  

}
 
void output(int d, int c, int b, int a, int ain, int bin, int cin, int din) {
  if (a == 1) digitalWrite(ain, HIGH);
  else if (a == 0) digitalWrite(ain, LOW); 
  if (b == 1) digitalWrite(bin, HIGH);
  else if (b == 0) digitalWrite(bin, LOW);
  if (c == 1) digitalWrite(cin, HIGH);
  else if (c == 0) digitalWrite(cin, LOW);
  if (d == 1) digitalWrite(din, HIGH);
  else if (d == 0) digitalWrite(din , LOW);
}


void displayNumber(int numberIn){
  int dig1 = (numberIn /   10 ) % 10;
  int dig2 = (numberIn /  1 ) % 10;

  switch(dig1){
    case 0: output(0,0,0,0,a1,b1,c1,d1);
    break;
    case 1: output(0,0,0,1,a1,b1,c1,d1);
    break;
    case 2: output(0,0,1,0,a1,b1,c1,d1);
    break;
    case 3: output(0,0,1,1,a1,b1,c1,d1);
    break;
    case 4: output(0,1,0,0,a1,b1,c1,d1);
    break;
    case 5: output(0,1,0,1,a1,b1,c1,d1);
    break;
    case 6: output(0,1,1,0,a1,b1,c1,d1);
    break;
    case 7: output(0,1,1,1,a1,b1,c1,d1);
    break;
    case 8: output(1,0,0,0,a1,b1,c1,d1);
    break;
    case 9: output(1,0,0,1,a1,b1,c1,d1);
    break;
  }

  switch(dig2){
    case 0: output(0,0,0,0,a2,b2,c2,d2);
    break;
    case 1: output(0,0,0,1,a2,b2,c2,d2);
    break;
    case 2: output(0,0,1,0,a2,b2,c2,d2);
    break;
    case 3: output(0,0,1,1,a2,b2,c2,d2);
    break;
    case 4: output(0,1,0,0,a2,b2,c2,d2);
    break;
    case 5: output(0,1,0,1,a2,b2,c2,d2);
    break;
    case 6: output(0,1,1,0,a2,b2,c2,d2);
    break;
    case 7: output(0,1,1,1,a2,b2,c2,d2);
    break;
    case 8: output(1,0,0,0,a2,b2,c2,d2);
    break;
    case 9: output(1,0,0,1,a2,b2,c2,d2);
    break;
  }
  
}

 
