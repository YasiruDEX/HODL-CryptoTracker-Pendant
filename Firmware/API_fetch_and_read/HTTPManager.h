#ifndef HTTP_MANAGER_H
#define HTTP_MANAGER_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

class HTTPManager {
public:
  HTTPManager();
  void fetchData(const String& apiUrl, String& coin, String raValues[], String decValues[]);
private:
  void processPayload(const String& payload, std::vector<String>& planetNames, std::vector<String>& raValues, std::vector<String>& decValues);
};

#endif
