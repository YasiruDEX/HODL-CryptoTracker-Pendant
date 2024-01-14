#include "HTTPManager.h"

HTTPManager::HTTPManager() {}

void HTTPManager::fetchData(const String& apiUrl, String& coin) {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, apiUrl)) {
    int httpCode = https.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        DynamicJsonDocument doc(512); // Adjust the size based on your JSON complexity
        deserializeJson(doc, payload);
        JsonArray data = doc["data"];

        if (data.size() > 0) {
          JsonObject coinData = data[0];
          String price = coinData["askPx"];
          coin = price;

        } else {
          Serial.println("[https] No data found in the JSON");
        }
      }
    } else {
      Serial.printf("[https] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[https] Unable to connect\n");
  }
}
