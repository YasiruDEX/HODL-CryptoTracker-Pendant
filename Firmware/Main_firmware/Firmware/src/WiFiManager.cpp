#include "WiFiManager.h"

WiFiManager::WiFiManager(String ssid, String password)
  : ssid(ssid), password(password) {}

void WiFiManager::connect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    attempt++;
    if(attempt >= 15){break;}
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
}

bool WiFiManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}
