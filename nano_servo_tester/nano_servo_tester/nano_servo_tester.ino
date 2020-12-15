#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);

int pwm;

void setup() {
  // put your setup code here, to run once:

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(3, OUTPUT);
}

void loop() {

  pwm = analogRead(A0);
  lcd.clear();
  lcd.print(pwm);
  delay(100);
  analogWrite(3, pwm);
  
  // put your main code here, to run repeatedly:

}
