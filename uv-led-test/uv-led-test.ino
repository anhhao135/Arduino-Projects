void setup() {
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
Serial.begin(9600);
}

void loop() {


for( int i = 2; i<9; i++){

  double delaytime = map (analogRead(A0), 0, 680, 1, 200);
 
  digitalWrite(i,HIGH);
  delay(delaytime);
  digitalWrite(i,LOW);
  delay(delaytime);

}



  // put your main code here, to run repeatedly:

}
