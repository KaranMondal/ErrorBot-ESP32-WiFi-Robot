#define BLYNK_TEMPLATE_ID " "
#define BLYNK_TEMPLATE_NAME "ErrorBot"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------- WiFi Credentials --------
char ssid[] = " ";
char pass[] = " ";

// -------- Motor Pins (Single Channel) --------
#define IN1 26
#define IN2 27

// -------- Physical Safety Switch --------
#define SWITCH_PIN 33   // switch between GPIO33 and GND
bool robotEnabled = false;

// -------- OLED --------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- Robot State --------
enum RobotState { IDLE, FORWARD, BACKWARD };
RobotState currentState = IDLE;

// -------- OLED UI FUNCTIONS --------
void drawHeader(const char* title) {
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(title);
  display.drawLine(0, 10, 128, 10, WHITE);
}

void drawStatus(const char* status) {
  display.setTextSize(1);
  display.setCursor(0, 14);
  display.print("Status: ");
  display.println(status);
}

void drawFace(bool happy) {
  display.drawCircle(96, 40, 12, WHITE);
  if (happy) {
    display.fillCircle(92, 36, 2, WHITE);
    display.fillCircle(100, 36, 2, WHITE);
    display.drawLine(92, 44, 100, 44, WHITE);
  } else {
    display.drawLine(90, 36, 94, 36, WHITE);
    display.drawLine(98, 36, 102, 36, WHITE);
  }
}

void updateOLED(const char* motionText) {
  display.clearDisplay();
  drawHeader("ErrorBot");
  drawStatus(robotEnabled ? "ENABLED" : "DISABLED");

  display.setCursor(0, 28);
  display.print("Motion: ");
  display.println(motionText);

  drawFace(robotEnabled);
  display.display();
}

// -------- MOTOR FUNCTIONS --------
void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  currentState = IDLE;
  updateOLED("IDLE");
}

void forward() {
  if (!robotEnabled) return;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  currentState = FORWARD;
  updateOLED("FORWARD");
}

void backward() {
  if (!robotEnabled) return;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  currentState = BACKWARD;
  updateOLED("BACKWARD");
}

// -------- SWITCH CHECK --------
void checkSwitch() {
  if (digitalRead(SWITCH_PIN) == LOW) {
    if (!robotEnabled) {
      robotEnabled = true;
      updateOLED("IDLE");
    }
  } else {
    if (robotEnabled) {
      robotEnabled = false;
      stopRobot();
    }
  }
}

// -------- BLYNK CONTROLS --------
BLYNK_WRITE(V1) { param.asInt() ? forward() : stopRobot(); }
BLYNK_WRITE(V2) { param.asInt() ? backward() : stopRobot(); }

BLYNK_WRITE(V4) {
  robotEnabled = param.asInt();
  stopRobot();
}

// -------- SETUP --------
void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("ErrorBot");
  display.display();
  delay(1500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.println("Connecting WiFi...");
  display.display();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  updateOLED("IDLE");
}

// -------- LOOP --------
void loop() {
  Blynk.run();
  checkSwitch();
}
