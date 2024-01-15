#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "NodeMCU";
const char *password = "";

ESP8266WebServer server(80);

String SSID = "";
String PASSWORD = "";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  // Print the IP address
  Serial.println(WiFi.softAPIP());

  // Define webpage routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/update", HTTP_GET, handleUpdate);
  
  // Start server
  server.begin();
}

void loop() {
  if (SSID == ""){
    server.handleClient();
  }else{
    Serial.println("Sucess");
  }

  Serial.println(SSID);
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP8266 Webpage</h1>";
  html += "<p>SSID: " + String(SSID) + "</p>";
  html += "<p>PASSWORD: " + String(PASSWORD) + "</p>";
  html += "<form action='/update' method='get'>";
  html += "SSID: <input type='text' name='SSID'><br>";
  html += "PASSWORD: <input type='text' name='PASSWORD'><br>";
  html += "<input type='submit' value='Update'>";
  html += "</form>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleUpdate() {
  if (server.hasArg("SSID")) {
    SSID = server.arg("SSID");
  }

  if (server.hasArg("PASSWORD")) {
    PASSWORD = server.arg("PASSWORD");
  }

  handleRoot();
}
