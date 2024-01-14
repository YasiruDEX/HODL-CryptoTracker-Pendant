#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password, LiquidCrystal_I2C& lcd)
  : ssid(ssid), password(password), lcd(lcd) {}

void WiFiManager::connect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  lcd.setCursor(0, 0);
  lcd.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    lcd.print('.');
    delay(1000);
  }
  lcd.clear();
  Serial.println();
}
