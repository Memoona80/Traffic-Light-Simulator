#include "arduino_secrets.h"

const int NS_R = 2, NS_Y = 3, NS_G = 4;
const int EW_R = 10, EW_Y = 6, EW_G = 7;
const int irsensor = 8;

// Time settings
unsigned long greentime = 5000;
unsigned long yellowtime = 2000;
unsigned long previousMillis = 0;

int state = 0;
bool pedestrianDetected = false;

void setup() {
  pinMode(NS_R, OUTPUT);
  pinMode(NS_Y, OUTPUT);
  pinMode(NS_G, OUTPUT);
  pinMode(EW_R, OUTPUT);
  pinMode(EW_Y, OUTPUT);
  pinMode(EW_G, OUTPUT);
  pinMode(irsensor, INPUT);

  Serial.begin(9600);
  setState(0);
  previousMillis = millis();
}

void loop() {
  if (digitalRead(irsensor) == LOW && !pedestrianDetected) {
    Serial.println("Pedestrian detected");
    pedestrianDetected = true;
    setAllRed();
    return;
  }

  if (pedestrianDetected) {
    if (digitalRead(irsensor) == HIGH) {
      Serial.println("Pedestrian gone, resume normal sequence");
      pedestrianDetected = false;
      setState(state);
      previousMillis = millis();
    }
    return;
  }

  unsigned long currentMillis = millis();

  if (state == 0 || state == 2) {
    if (currentMillis - previousMillis >= greentime) {
      previousMillis = currentMillis;
      state = (state == 0) ? 1 : 3;
      setState(state);
    }
  } else if (state == 1 || state == 3) {
    if (currentMillis - previousMillis >= yellowtime) {
      previousMillis = currentMillis;
      state = (state == 1) ? 2 : 0;
      setState(state);
    }
  }
}

void setState(int s) {
  // Turn off all LEDs
  digitalWrite(NS_Y, LOW);
  digitalWrite(NS_G, LOW);
  digitalWrite(NS_R, LOW);
  digitalWrite(EW_Y, LOW);
  digitalWrite(EW_G, LOW);
  digitalWrite(EW_R, LOW);

  switch (s) {
    case 0: // NS = Green
      Serial.println("NS Green | EW Red");
      digitalWrite(NS_G, HIGH);
      digitalWrite(EW_R, HIGH);
      break;
    case 1: // NS = Yellow
      Serial.println("NS Yellow | EW Red");
      digitalWrite(NS_Y, HIGH);
      digitalWrite(EW_R, HIGH);
      break;
    case 2: // EW = Green
      Serial.println("NS Red | EW Green");
      digitalWrite(NS_R, HIGH);
      digitalWrite(EW_G, HIGH);
      break;
    case 3: // EW = Yellow
      Serial.println("NS Red | EW Yellow");
      digitalWrite(NS_R, HIGH);
      digitalWrite(EW_Y, HIGH);
      break;
  }
}

void setAllRed() {
  digitalWrite(NS_Y, LOW);digitalWrite(NS_G, LOW);digitalWrite(NS_R, HIGH);digitalWrite(EW_Y, LOW);digitalWrite(EW_G, LOW);digitalWrite(EW_R, HIGH);
}
