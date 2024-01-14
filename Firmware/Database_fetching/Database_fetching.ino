/*
  Complete project details: https://RandomNerdTutorials.com/esp8266-nodemcu-https-requests/ 
  Based on the BasicHTTPSClient.ino Created on: 20.08.2018 (ESP8266 examples)
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>


// Replace with your network credentials
const char* ssid = "UNITY";
const char* password = "basnayake";

void setup() {
  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  //Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    // Ignore SSL certificate validation
    client->setInsecure();
    
    //create an HTTPClient instance
    HTTPClient https;
    
    //Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://www.okx.com/api/v5/market/ticker?instId=BTC-USD-SWAP")) {  // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);

          DynamicJsonDocument doc(4096);
          deserializeJson(doc, payload);

          // Extracting data for each planet
          JsonArray data = doc["data"];
          for (JsonObject planet : data) {
            String name = planet["name"];
            JsonObject ra = planet["rightAscension"];
            JsonObject dec = planet["declination"];

            // Extracting RA and Dec values
            int raHours = ra["hours"];
            int raMinutes = ra["minutes"];
            float raSeconds = ra["seconds"];
            bool raNegative = ra["negative"];

            int decDegrees = dec["degrees"];
            int decArcMinutes = dec["arcminutes"];
            float decArcSeconds = dec["arcseconds"];
            bool decNegative = dec["negative"];

            // Displaying extracted data
            Serial.println("Planet: " + name);
            Serial.println("Right Ascension: " + String(raNegative ? "-" : "") + String(raHours) + "h " + String(raMinutes) + "m " + String(raSeconds) + "s");
            Serial.println("Declination: " + String(decNegative ? "-" : "") + String(decDegrees) + "° " + String(decArcMinutes) + "' " + String(decArcSeconds) + "\"");
            Serial.println("-----------------------------------");
          }
          // Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  Serial.println();
  Serial.println("Waiting 5S before the next round...");
  delay(10000);
}
