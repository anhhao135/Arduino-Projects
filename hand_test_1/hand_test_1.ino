int relax;
int clench;

void setup() {
  // put your setup code here, to run once:


Serial.begin(9600);


Serial.println("Clench");
delay(2000);
clench = analogRead(A0);
Serial.println(clench);
Serial.println("Relax");
delay(2000);
relax = analogRead(A0);
Serial.println(relax);


}

void loop() {
  // put your main code here, to run repeatedly:



double data1 = analogRead(A0);
//double data2 = analogRead(A1);


Serial.println(map(data1,relax,clench, 0, 100));
//Serial.println(data2);

delay(50);


}
