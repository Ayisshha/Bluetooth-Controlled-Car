#include <SoftwareSerial.h>

// Bluetooth module pins
const int BT_RX = 2; // Arduino RX (connect to HC-05 TX)
const int BT_TX = 3; // Arduino TX (connect to HC-05 RX via voltage divider)

// Initialize SoftwareSerial
SoftwareSerial Bluetooth(BT_RX, BT_TX);

// Motor Pins
const int LEFT_IN1 = 9;
const int LEFT_IN2 = 10;
const int LEFT_EN  = 5;

const int RIGHT_IN1 = 11;
const int RIGHT_IN2 = 12;
const int RIGHT_EN  = 6;

int speed = 200;
char t;

void setup() {
  // Motor pins
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(LEFT_EN, OUTPUT);

  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT);

  // Start Bluetooth serial
  Bluetooth.begin(9600);
}

void loop() {
  if (Bluetooth.available() > 0) {
    t = Bluetooth.read();
    
    switch(t) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': leftward(); break;
      case 'R': rightward(); break;
      case 'S': stop_the(); break;
    }
  }
}

// Motor functions
void forward() {
  analogWrite(LEFT_EN, speed);
  analogWrite(RIGHT_EN, speed);

  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
}

void backward() {
  analogWrite(LEFT_EN, speed);
  analogWrite(RIGHT_EN, speed);

  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, HIGH);
}

void stop_the() {
  analogWrite(LEFT_EN, 0);
  analogWrite(RIGHT_EN, 0);

  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, LOW);
}

void leftward() {
  analogWrite(LEFT_EN, speed / 2);
  analogWrite(RIGHT_EN, speed);

  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
}

void rightward() {
  analogWrite(LEFT_EN, speed);
  analogWrite(RIGHT_EN, speed / 2);

  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
}