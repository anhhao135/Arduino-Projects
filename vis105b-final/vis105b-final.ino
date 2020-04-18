void setup() {
  // put your setup code here, to run once:


  for (int i = 2; i<14; i++){

    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
    
    }
      
  
  }




void loop() {


if (analogRead(A0)>800){

  

  for (int i = 2; i<14; i++){

    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);

    
    }

}

  
if (analogRead(A0)<800){
  

  for (int i = 2; i<14; i++){

        if(analogRead(A0)>800){
      break;
    }

    if(digitalRead(A1) == HIGH){
      break;
    }

    int delaytime = map(analogRead(A0), 0, 1023, 1, 1000);

    

  digitalWrite(i,HIGH);
  delay(delaytime);
  digitalWrite(i, LOW);
  delay(delaytime);

  Serial.println("osc");

      if(analogRead(A0)>800){
      break;
    }
    
    
   }
  // put your main code here, to run repeatedly:



  if (digitalRead(A1) == HIGH){

    Serial.println("rnd");
    int delaytime = map(analogRead(A0), 0, 1023, 1, 1000);

    int number = random(2,14);
    Serial.println(number);
    
      digitalWrite(number,HIGH);
      delay(delaytime);
      digitalWrite(number, LOW);
      delay(delaytime);
    }
    
  }

}
