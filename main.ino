
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin Definitions
const int LED_PIN    = 3; // Digital Output
const int BUZZER_PIN = 4; // Digital Output
const int ECHO_PIN   = 6; // Ultrasonic Echo
const int TRIG_PIN   = 7; // Ultrasonic Trig

// Default I2C LCD Address (0x20 for Tinkercad, 0x27 for hardware)
LiquidCrystal_I2C lcd(0x20, 16, 2); 

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  // 1. Send Ultrasonic Pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 2. Read Echo Pulse
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  // 3. Print Distance on LCD Top Line
  lcd.setCursor(0, 0);
  if (distance == 0) {
    lcd.print("Dist: Out Range ");
  } else {
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print(" cm    ");
  }

  // 4. Trigger Alarm strictly when object is closer than 15cm (and > 0)
  if (distance > 0 && distance < 15) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    
    lcd.setCursor(0, 1);
    lcd.print("STATUS: ALARM!  ");
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    
    lcd.setCursor(0, 1);
    lcd.print("STATUS: CLEAR  ");
  }

  delay(150);
}