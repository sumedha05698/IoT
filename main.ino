/*
 * ============================================================
 *  IoT-Based Multi-LED Control & Environmental Monitoring
 *  Platform : ESP32 + Blynk IoT
 *  Sensors  : DHT22 (Temperature & Humidity)
 *  LEDs     : Red, Yellow, Green, Blue
 *  Author   : Sumedha.C
 *  Version  : 2.0
 * ============================================================
 *
 * Blynk Virtual Pin Map:
 *  V0  → Red LED toggle
 *  V1  → Yellow LED toggle
 *  V2  → Green LED toggle
 *  V3  → Blue LED toggle
 *  V4  → Temperature (read)
 *  V5  → Humidity (read)
 *  V6  → All LEDs toggle (master)
 *  V7  → Red LED status indicator
 *  V8  → Yellow LED status indicator
 *  V9  → Green LED status indicator
 *  V10 → Blue LED status indicator
 *  V11 → Heat Index (read)
 * ============================================================
 */

// ─── Blynk Credentials ─────────────────────────────────────
#define BLYNK_TEMPLATE_ID   "TMPL3HHX6qTVb"
#define BLYNK_TEMPLATE_NAME "LED PROJECT"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN_HERE"   // ← Replace before uploading

// ─── Libraries ─────────────────────────────────────────────
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h>

// ─── WiFi Credentials ──────────────────────────────────────
char ssid[] = "YOUR_WIFI_SSID";     // ← Replace with your WiFi name
char pass[] = "YOUR_WIFI_PASSWORD"; // ← Replace with your WiFi password

// ─── Pin Definitions ───────────────────────────────────────
#define DHT_PIN   15
#define LED_R     24   // Red   LED
#define LED_Y     27   // Yellow LED
#define LED_G     10   // Green LED
#define LED_B     14   // Blue  LED

// ─── Objects & Variables ───────────────────────────────────
DHTesp    dht;
BlynkTimer timer;

int value0 = 0;   // Red
int value1 = 0;   // Yellow
int value2 = 0;   // Green
int value3 = 0;   // Blue
int value6 = 0;   // Master (All)

// ─── Send Sensor Data to Blynk ─────────────────────────────
void sendSensor() {
  TempAndHumidity data = dht.getTempAndHumidity();

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("[ERROR] Failed to read from DHT sensor!");
    return;
  }

  float heatIndex = dht.computeHeatIndex(data.temperature, data.humidity, false);

  // Serial Monitor output
  Serial.printf("[DHT22] Temp: %.1f°C | Humidity: %.1f%% | Heat Index: %.1f°C\n",
                data.temperature, data.humidity, heatIndex);

  // Send to Blynk Cloud
  Blynk.virtualWrite(V4, data.temperature);
  Blynk.virtualWrite(V5, data.humidity);
  Blynk.virtualWrite(V11, heatIndex);   // NEW: Heat Index
}

// ─── Individual LED Handlers ───────────────────────────────
BLYNK_WRITE(V0) {
  value0 = param.asInt();
  digitalWrite(LED_R, value0);
  Blynk.virtualWrite(V7, value0);
  cekAllLed();
}

BLYNK_WRITE(V1) {
  value1 = param.asInt();
  digitalWrite(LED_Y, value1);
  Blynk.virtualWrite(V8, value1);
  cekAllLed();
}

BLYNK_WRITE(V2) {
  value2 = param.asInt();
  digitalWrite(LED_G, value2);
  Blynk.virtualWrite(V9, value2);
  cekAllLed();
}

BLYNK_WRITE(V3) {
  value3 = param.asInt();
  digitalWrite(LED_B, value3);
  Blynk.virtualWrite(V10, value3);
  cekAllLed();
}

// ─── Master (All LEDs) Handler ─────────────────────────────
BLYNK_WRITE(V6) {
  value6 = param.asInt();

  // Apply to all LEDs
  value0 = value1 = value2 = value3 = value6;

  digitalWrite(LED_R, value6);
  digitalWrite(LED_Y, value6);
  digitalWrite(LED_G, value6);
  digitalWrite(LED_B, value6);

  // Sync status indicators
  Blynk.virtualWrite(V7,  value6);
  Blynk.virtualWrite(V8,  value6);
  Blynk.virtualWrite(V9,  value6);
  Blynk.virtualWrite(V10, value6);

  // Sync toggle buttons
  Blynk.virtualWrite(V0, value6);
  Blynk.virtualWrite(V1, value6);
  Blynk.virtualWrite(V2, value6);
  Blynk.virtualWrite(V3, value6);

  Serial.printf("[MASTER] All LEDs turned %s\n", value6 ? "ON" : "OFF");
}

// ─── Check & Sync Master Toggle ────────────────────────────
void cekAllLed() {
  int allOn  = (value0 == 1 && value1 == 1 && value2 == 1 && value3 == 1);
  int allOff = (value0 == 0 && value1 == 0 && value2 == 0 && value3 == 0);

  if (allOn)  Blynk.virtualWrite(V6, 1);
  if (allOff) Blynk.virtualWrite(V6, 0);
}

// ─── Blynk Connected Callback ──────────────────────────────
BLYNK_CONNECTED() {
  Serial.println("[BLYNK] Connected to cloud!");
  Blynk.syncAll();   // Restore last state from server
}

// ─── Setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("\n==============================");
  Serial.println("  IoT LED Control + DHT22");
  Serial.println("==============================");

  // Init DHT sensor
  dht.setup(DHT_PIN, DHTesp::DHT22);

  // Init LED pins
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Ensure all LEDs start OFF
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Send sensor data every 2 seconds
  timer.setInterval(2000L, sendSensor);

  Serial.println("[SETUP] Initialization complete.");
}

// ─── Loop ──────────────────────────────────────────────────
void loop() {
  Blynk.run();
  timer.run();
}
