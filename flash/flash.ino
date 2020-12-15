void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);// Initialize the LED_BUILTIN pin as an output
  pinMode(14, INPUT);
}

void loop() {
  delay(50);
  Serial.println(analogRead(A0));
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(digitalRead(14));
}
