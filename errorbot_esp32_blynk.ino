#define BLYNK_TEMPLATE_ID " "
#define BLYNK_TEMPLATE_NAME "Rc Car"
#define BLYNK_AUTH_TOKEN " "

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------- WiFi Credentials --------
char ssid[] = "Aayein :]";
char pass[] = "  ";

// -------- Motor Pins (ONLY Channel A used) --------
#define IN1 26
#define IN2 27
// IN3 & IN4 NOT USED (damaged channel)

// -------- Physical 1-Way Switch --------
#define SWITCH_PIN 33   // switch between GPIO33 and GND
bool robotEnabled = false;

// -------- OLED --------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- OLED Faces --------
void drawHappyFace() {
  display.clearDisplay();
  display.drawCircle(64, 32, 20, WHITE);
  display.fillCircle(56, 26, 3, WHITE);
  display.fillCircle(72, 26, 3, WHITE);
  display.drawLine(56, 38, 72, 38, WHITE); // smile
  display.display();
}

void drawSleepFace() {
  display.clearDisplay();
  display.drawCircle(64, 32, 20, WHITE);
  display.drawLine(54, 26, 58, 26, WHITE);
  display.drawLine(70, 26, 74, 26, WHITE);
  display.display();
}

// -------- Motor Functions --------
void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  if (robotEnabled) {
    drawHappyFace();   // idle but enabled
  } else {
    drawSleepFace();   // disabled
  }
}

void forward() {
  if (!robotEnabled) return;

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("FORWARD");
  display.display();
}

void backward() {
  if (!robotEnabled) return;

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("BACKWARD");
  display.display();
}

// -------- Physical Switch Check --------
void checkSwitch() {
  // INPUT_PULLUP logic:
  // LOW  = switch ON
  // HIGH = switch OFF
  if (digitalRead(SWITCH_PIN) == LOW) {
    if (!robotEnabled) {
      robotEnabled = true;
      drawHappyFace();
    }
  } else {
    if (robotEnabled) {
      robotEnabled = false;
      stopRobot();
    }
  }
}

// -------- Blynk Buttons --------
BLYNK_WRITE(V1) { param.asInt() ? forward()  : stopRobot(); }
BLYNK_WRITE(V2) { param.asInt() ? backward() : stopRobot(); }

// Optional Blynk ON/OFF button
BLYNK_WRITE(V4) {
  robotEnabled = param.asInt();
  stopRobot();
}

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // OLED Init
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connecting");
  display.display();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  display.clearDisplay();
  display.println("Connected");
  display.display();

  delay(1000);
  drawSleepFace(); // default state
}

void loop() {
  Blynk.run();
  checkSwitch();
}
