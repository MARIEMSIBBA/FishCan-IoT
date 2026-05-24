#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ── WiFi ─────────────────────────────
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const char* API_URL = "http://192.168.8.44:8000/data";
// ── Pins ─────────────────────────────
#define PIN_TORQUE    34
#define PIN_TEMP      35
#define PIN_LED_GREEN 25
#define PIN_LED_RED   26

// ── Seuils ───────────────────────────
const float TORQUE_MIN = 8.0;
const float TORQUE_MAX = 14.0;
const float VIB_MAX    = 1.5;
const float TEMP_MIN   = 112.0;
const float TEMP_MAX   = 125.0;
const float F0_MIN     = 3.0;

float f0 = 0.0;

// ─────────────────────────────────────
void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi OK");
}

// ── Capteurs ─────────────────────────
float readTemperature() {
  int raw = analogRead(PIN_TEMP);
  return 110.0 + (raw / 4095.0) * 18.0;
}

float readTorque() {
  int raw = analogRead(PIN_TORQUE);
  return 5.0 + (raw / 4095.0) * 12.0;
}

float readVibration() {
  if (random(0,100) < 80)
    return 0.4 + (random(0,90)/100.0);
  else
    return 1.5 + (random(0,70)/100.0);
}

float computeF0(float temp) {
  float dt = 2.0 / 60.0;
  f0 += dt * pow(10.0, (temp - 121.1) / 10.0);
  return f0;
}

// ── STATUS SIMPLIFIÉ ─────────────────
String getSeamingStatus(float torque, float vib) {
  if (torque < TORQUE_MIN || torque > TORQUE_MAX || vib > VIB_MAX)
    return "ANOMALY";
  return "NORMAL";
}

String getSterilizationStatus(float temp, float f0val) {
  // ❌ anomalie température
  if (temp < TEMP_MIN || temp > TEMP_MAX)
    return "ANOMALY";
  // ✅ température OK → même si F0 pas encore atteint
  return "NORMAL";
}

// ── LED ──────────────────────────────
void updateLED(String seam, String steril) {

  if (seam == "ANOMALY" || steril == "ANOMALY") {
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_RED, HIGH);
  } else {
    digitalWrite(PIN_LED_GREEN, HIGH);
    digitalWrite(PIN_LED_RED, LOW);
  }
}

// ── HTTP ─────────────────────────────
void sendData(float temp, float torque, float vib, float f0val,
              String seam, String steril) {

  StaticJsonDocument<300> doc;

  doc["temperature"] = temp;
  doc["torque"] = torque;
  doc["vibration"] = vib;
  doc["F0"] = f0val;
  doc["seaming_status"] = seam;
  doc["sterilization_status"] = steril;

  String json;
  serializeJson(doc, json);

  HTTPClient http;
  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");

  int code = http.POST(json);

  // ── Affichage ───────────────────────
  Serial.println("\n====== DATA ======");
  Serial.println("Temp: " + String(temp));
  Serial.println("Torque: " + String(torque));
  Serial.println("Vibration: " + String(vib));
  Serial.println("F0: " + String(f0val));
  Serial.println("Seaming: " + seam);
  Serial.println("Sterilization: " + steril);
  Serial.println("HTTP: " + String(code));
  Serial.println("==================");

  http.end();
}

// ─────────────────────────────────────
void setup() {
  Serial.begin(115200);

  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  connectWiFi();
}

// ─────────────────────────────────────
void loop() {

  float temp   = readTemperature();
  float torque = readTorque();
  float vib    = readVibration();
  float f0val  = computeF0(temp);

  String seam   = getSeamingStatus(torque, vib);
  String steril = getSterilizationStatus(temp, f0val);

  updateLED(seam, steril);
  sendData(temp, torque, vib, f0val, seam, steril);

  delay(2000);
}