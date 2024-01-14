#include <Arduino.h>
#include "WiFiManager.h"
#include "FirebaseManager.h"
#include "HTTPManager.h"
#include "ServoManager.h"
#include "LCDManager.h"

ServoManager zAxisServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "UNITY";
const char* password = "basnayake";
const char* referenceUrl = "earendeldata-default-rtdb.asia-southeast1.firebasedatabase.app";
const char* httpUrl = "https://www.okx.com/api/v5/market/ticker?instId=BTC-USD-SWAP";

FirebaseManager firebase(referenceUrl);
WiFiManager wifiManager(ssid, password, lcd);
HTTPManager httpManager;

const int MAX_PLANETS = 10;
const int numberOfPlanets = 10;

String planetNames[MAX_PLANETS];
String raValues[MAX_PLANETS];
String decValues[MAX_PLANETS];

String Price = "none";

const String planetsWithMoon[numberOfPlanets] = {
  "Sun", "Moon", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"
};

String planetNeeded;
String starData;
String prevPlanet;

// Function declarations
int findIndex(const String array[], int size, const String &targetValue);
void initialize();
void handlePlanetData();
void handleStarData();

void setup() {
  zAxisServo.attach(D3);
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  initialize();
}

void loop() {

  handlePlanetData();
  Serial.println(Price);
  delay(30*1000);
}

// Function definitions
void initialize() {
  wifiManager.connect();
}

void handlePlanetData() {
  httpManager.fetchData(httpUrl, coin, raValues, decValues);
}

