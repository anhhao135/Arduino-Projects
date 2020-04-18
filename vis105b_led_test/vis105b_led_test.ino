void setup() {
  // put your setup code here, to run once:


  for (int i = 2; i<14; i++){

    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
    
    }
      
  
  }




void loop() {

  delay(100);
  digitalWrite(2,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  


  

  }
