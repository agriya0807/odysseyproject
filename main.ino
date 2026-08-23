#include <LiquidCrystal.h>

// Pins: LiquidCrystal(RS, E, DB4, DB5, DB6, DB7)
LiquidCrystal lcd(12, 11, 5, 8, 9, 10);

const int BUTTON_PIN = 2;
const int LED_PIN    = 3;
const int BUZZER_PIN = 4;
const int ECHO_PIN   = 6;
const int TRIG_PIN   = 7;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Active");
  delay(1000);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = duration * 0.034 / 2;
  bool buttonPressed = (digitalRead(BUTTON_PIN) == LOW);

  lcd.setCursor(0, 0);
  if (distance == 0) {
    lcd.print("Dist: Out Range ");
  } else {
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print(" cm    ");
  }

  if ((distance > 0 && distance < 15) || buttonPressed) {
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

  delay(100);
}
    