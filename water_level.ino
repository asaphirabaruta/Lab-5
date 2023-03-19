#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int analogInPin = A0;
int sensorValue = 0;

void setup() {
  
  lcd.begin(16, 2);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
}


void loop() {
  sensorValue = analogRead(analogInPin);  
  Serial.print(sensorValue);
  Serial.print("\n");
  lcd.clear();
  delay(2);

  if((sensorValue>=281)&&(sensorValue<=700)){
      Serial.print("Full: ");
      
      lcd.setCursor(0, 0);
      lcd.print("Status: Full");
      lcd.setCursor(0, 1);
      lcd.print("Level: ");
      lcd.print(sensorValue);
      lcd.print(" mm");
      digitalWrite(10,HIGH);
      digitalWrite(6,HIGH);
      tone(6, 800, 800);
      digitalWrite(8,LOW);
      
      delay(100);
      }    
  else if((sensorValue>=201)&&(sensorValue<=280)){
    Serial.print("Medium: ");
    lcd.setCursor(0, 0);
    lcd.print("Status: Medium");
    lcd.setCursor(0, 1);
    lcd.print("Level: ");
    lcd.print(sensorValue);
    lcd.print(" mm");    
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(6,LOW);
    delay(100);
    }  
  else if((sensorValue>=100)&&(sensorValue<=200)){
    Serial.print("Almost Empty: ");
    lcd.setCursor(0, 0);
    lcd.print("Status: Empty");
    lcd.setCursor(0, 1);
    lcd.print("Level: ");
    lcd.print(sensorValue);
    lcd.print(" mm");
    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(10,LOW);
    digitalWrite(6,HIGH);
    tone(6, 300, 300);
    delay(100);
    }
  else{
    Serial.print("Empty: ");
    lcd.setCursor(0, 0);
    lcd.print("Status: Empty");
    lcd.setCursor(0, 1);
    lcd.print("Level: ");
    lcd.print(sensorValue);
    lcd.print(" mm");
    digitalWrite(9,HIGH);    
    digitalWrite(8,LOW);
    digitalWrite(10,LOW);
    digitalWrite(6,HIGH);
    tone(6, 1000, 1000);
    delay(100);
    }
}
