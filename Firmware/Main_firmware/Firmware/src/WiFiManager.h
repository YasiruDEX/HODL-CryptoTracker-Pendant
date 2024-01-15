#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>

class WiFiManager {
public:
  WiFiManager(String ssid, String password, LiquidCrystal_I2C& lcd);
  void connect();
  bool isConnected();
public:
  String ssid;
  String password;
  LiquidCrystal_I2C& lcd;
};

#endif
