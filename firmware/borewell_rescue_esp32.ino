/***************************************************
  Borewell Rescue System using IoT
  ESP32 + Blynk firmware

  Controls:
    - 2x DC motors (winch / vertical movement) via L298N driver
    - 1x Servo motor (gripper mechanism)
    - 1x Stepper motor (28BYJ-48 via ULN2003 driver) for extraction/rotation
    - 1x Ultrasonic sensor (depth / obstacle detection)
    - 3x Status LEDs (Red / Yellow / Green)

  NOTE: Replace the placeholder WiFi and Blynk credentials below
  before uploading. Do NOT commit real credentials to GitHub —
  see secrets.h.example in this folder for a safer pattern.
***************************************************/

#define BLYNK_TEMPLATE_ID   "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "ESP32_Robot_Control"
#define BLYNK_AUTH_TOKEN    "YourAuthToken"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>
#include <Stepper.h>

// ---------------- WiFi credentials ----------------
char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";

// ---------------- Motor A Pins ----------------
#define ENA 25
#define IN1 26
#define IN2 27

// ---------------- Motor B Pins ----------------
#define ENB 14
#define IN3 12
#define IN4 13

// ---------------- Servo Pin ----------------
#define SERVO_PIN 4

// ---------------- Stepper Pins ----------------
#define IN1_STP 16
#define IN2_STP 17
#define IN3_STP 18
#define IN4_STP 19

// ---------------- Ultrasonic Pins ----------------
#define TRIG_PIN 5
#define ECHO_PIN 23

// ---------------- LED Pins ----------------
#define LED1 32   // Red    - Error / Stuck
#define LED2 33   // Yellow - In Progress
#define LED3 15   // Green  - Complete

Servo myServo;
Stepper myStepper(2048, IN1_STP, IN3_STP, IN2_STP, IN4_STP);

// Ultrasonic distance
long duration;
int distance;

// --------------- BLYNK FUNCTIONS ---------------

// DC Motor A
BLYNK_WRITE(V0) { digitalWrite(IN1, param.asInt()); digitalWrite(IN2, LOW); }
BLYNK_WRITE(V1) { digitalWrite(IN2, param.asInt()); digitalWrite(IN1, LOW); }

// DC Motor B
BLYNK_WRITE(V2) { digitalWrite(IN3, param.asInt()); digitalWrite(IN4, LOW); }
BLYNK_WRITE(V3) { digitalWrite(IN4, param.asInt()); digitalWrite(IN3, LOW); }

// Servo (gripper)
BLYNK_WRITE(V4) {
  int pos = param.asInt();
  myServo.write(pos);
}

// Stepper CW
BLYNK_WRITE(V5) {
  if (param.asInt()) myStepper.step(512);
}

// Stepper CCW
BLYNK_WRITE(V6) {
  if (param.asInt()) myStepper.step(-512);
}

// Status LEDs
BLYNK_WRITE(V7) { digitalWrite(LED1, param.asInt()); }
BLYNK_WRITE(V8) { digitalWrite(LED2, param.asInt()); }
BLYNK_WRITE(V9) { digitalWrite(LED3, param.asInt()); }

// ---------------- Ultrasonic function ----------------
void readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  Blynk.virtualWrite(V10, distance);
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo.attach(SERVO_PIN);
  myStepper.setSpeed(10);

  // WiFi + Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  readUltrasonic();
  delay(1000);
}
