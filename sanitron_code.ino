#define BLYNK_TEMPLATE_ID "TMPL3DMdU3XEB"
#define BLYNK_TEMPLATE_NAME "xyz"
#define BLYNK_AUTH_TOKEN "9jUlkqvIyOlSJ6Qpv0g7mSdD0ELmLTkV"
#define BLYNK_PRINT Serial

#include <ESP32Servo.h> 
#include <BlynkSimpleEsp32.h>

// Movement
const int motor1A = 21;   // IN1  
const int motor1B = 19;   // IN2
const int enA = 26;       // ENA   
const int motor2A = 22;   // IN3
const int motor2B = 23;   // IN4
const int enB = 32;       // ENB

// BO motor
const int motor3A = 5;    // IN1
const int motor3B = 18;   // IN2
const int en2A = 19;      // ENA
const int servoPin1 = 33; 
const int servoPin2 = 25;
const int pirPin = 12; // PIR sensor output pin
// Relay
const int relayPin = 13; // Relay pin

Servo myservo1;  // Servo 1
Servo myservo2;  // Servo 2

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  Blynk.begin(BLYNK_AUTH_TOKEN, "Error", "idontknow");

  // Movement
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(enB, OUTPUT);
  
  // Extension and Spinning
  pinMode(motor3A, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(en2A, OUTPUT);
  
  // Relay
  pinMode(relayPin, OUTPUT);
  
  // Attach the servos
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
  
  // Set the PIR sensor pin as INPUT
  pinMode(pirPin, INPUT);
  
  Serial.println("PIR Sensor Test");
  delay(2000); // Give the sensor time to calibrate
}

BLYNK_WRITE(V0) { // Forward Button
  int value = param.asInt();
  if (value == 1) {
    Serial.println("Switch on V0 is ON");
    forward();
  } else {
    Serial.println("Switch on V0 is OFF");
    stopMotorsDrive();
  }
}

BLYNK_WRITE(V1) { // Backward Button
  int value = param.asInt();
  if (value == 1) {
    Serial.println("Switch on V1 is ON");
    backward();
  } else {
    Serial.println("Switch on V1 is OFF");
    stopMotorsDrive();
  }
}

BLYNK_WRITE(V2) { // Right Button
  int value = param.asInt();
  if (value == 1) {
    Serial.println("Switch on V2 is ON");
    right();
  } else {
    Serial.println("Switch on V2 is OFF");
    stopMotorsDrive();
  }
}

BLYNK_WRITE(V3) { // Left Button
  int value = param.asInt();
  if (value == 1) {
    Serial.println("Switch on V3 is ON");
    left();
  } else {
    Serial.println("Switch on V3 is OFF");
    stopMotorsDrive();
  }
}

BLYNK_WRITE(V4) { // Extension and retraction
  int value = param.asInt();
  if (value == 1) {
    Serial.println("Switch on V4 is ON");
    extension();
    spin();
  } else {
    Serial.println("Switch on V4 is OFF");
    retraction();
    stopMotorsEs();
  }
}

void loop() {
  Blynk.run();
  
  // Read the PIR sensor output
  int pirState = digitalRead(pirPin);
  
  if (pirState == HIGH) {
    // Motion detected
    Serial.println("Motion detected!");
  } else {
    // No motion
    Serial.println("No motion.");
  }
  
  // Delay to avoid flooding the serial monitor
  delay(1000);
}

// Driving Functions
void forward() {
  ledcWrite(enA, 255);
  ledcWrite(enB, 255);
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void backward() {
  ledcWrite(enA, 255);
  ledcWrite(enB, 255);
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void left() {
  ledcWrite(enA, 255);
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  ledcWrite(enB, 255);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void right() {
  ledcWrite(enA, 255);
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  ledcWrite(enB, 255);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void stopMotorsDrive() {
  ledcWrite(enA, 0);
  ledcWrite(enB, 0);
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}

void extension() {
  digitalWrite(relayPin, HIGH);
  for (int pos = 0; pos <= 180; pos++) {
    myservo1.write(pos);
    myservo2.write(pos); // Tell servo to go to position in variable 'pos'
    delay(15); // Wait 15ms for the servo to reach the position
  }
}

void retraction() {
  digitalWrite(relayPin, LOW);
  for (int pos = 180; pos >= 0; pos--) {
    myservo1.write(pos);
    myservo2.write(pos); // Tell servo to go to position in variable 'pos'
    delay(15); // Wait 15ms for the servo to reach the position
  }
}

void spin() {
  ledcWrite(en2A, 255);
  digitalWrite(motor3A, HIGH);
  digitalWrite(motor3B, LOW);
}

void stopMotorsEs() {
  ledcWrite(en2A, 0);
  digitalWrite(motor3A, LOW);
  digitalWrite(motor3B, LOW);
}
