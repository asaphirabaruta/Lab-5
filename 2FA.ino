#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; 

const byte COLS = 3; 

char keys[ROWS][COLS] = { 
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};

byte colPins[COLS] = {5, 4, 3}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
const int rs = 12, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  

char password[] = "7654"; 

int photoResistor_Pin = A0; 

const int PIR_PIN = 1;  
int led_Pin = 10; 

int speaker_Pin = 11; 

bool authenticated = false;
bool motionDetected = false;

                  


void setup() {
  lcd.begin(16, 2);
  pinMode(photoResistor_Pin, INPUT); 
  pinMode(PIR_PIN, INPUT);
  pinMode(led_Pin, OUTPUT); 
  pinMode(speaker_Pin, OUTPUT); 
  Serial.begin(9600);   
}

void loop() {
  int sensorValue = analogRead(photoResistor_Pin);
  motionDetected = digitalRead(PIR_PIN);
  
  Serial.println(sensorValue);
  if ((sensorValue>700)&&(motionDetected==1))
  {
    Serial.println(sensorValue);
    Serial.println("Enter password:");
    lcd.setCursor(0, 0);
    lcd.print("Enter password: ");
    
    authenticated = authenticate(); 
    if (authenticated) { // If authentication is successful
    digitalWrite(led_Pin, LOW); 
    tone(speaker_Pin, 0, 1000);         
    delay(5000); //delay for 1 second before taking the next sensor readings
    }      
  }}
  
//Authenticating Function
bool authenticate() 
{  
  char input[5];
  int i = 0;
  while (i < 4) 
  {
    char key = keypad.getKey();
    if (key != NO_KEY) 
    {
      input[i] = key;
      i++;
    }
  }
  input[4] = '\0';
  Serial.println(input);
  lcd.setCursor(0, 1);
  lcd.print(input);
  if (strcmp(input, password) == 0) 
  {
    digitalWrite(13, LOW);
    Serial.println("Password is right, enter");
    
  } 
  else 
  {
    
    digitalWrite(led_Pin, HIGH);
    tone(speaker_Pin, 500, 5000);
    delay(5000);
    digitalWrite(led_Pin, LOW);

  }
}
