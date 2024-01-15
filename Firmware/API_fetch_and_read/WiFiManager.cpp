#include "WiFiManager.h"

WiFiManager::WiFiManager(String ssid, String password, LiquidCrystal_I2C& lcd)
  : ssid(ssid), password(password), lcd(lcd) {}

void WiFiManager::connect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  lcd.setCursor(0, 0);
  lcd.print("Connecting");
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    attempt++;
    if(attempt >= 15){break;}
    Serial.print('.');
    lcd.print('.');
    delay(1000);
  }
  lcd.clear();
  Serial.println();
}

bool WiFiManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}
