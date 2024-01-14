#include <Arduino.h>
#include "WiFiManager.h"
#include "FirebaseManager.h"
#include "HTTPManager.h"
#include "ServoManager.h"
#include "LCDManager.h"

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

ServoManager zAxisServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);
U8G2_SH1106_128X32_VISIONOX_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

const char* ssid = "UNITY";
const char* password = "basnayake";
const char* referenceUrl = "earendeldata-default-rtdb.asia-southeast1.firebasedatabase.app";
const char* httpUrl = "https://www.okx.com/api/v5/market/ticker?instId=BTC-USD-SWAP";

FirebaseManager firebase(referenceUrl);
WiFiManager wifiManager(ssid, password, lcd);
HTTPManager httpManager;

String Price = "none";
String previousPrice = "none";

bool up = false;

String planetNeeded;
String starData;
String prevPlanet;

// Function declarations
int findIndex(const String array[], int size, const String& targetValue);
void initialize();
void handlePlanetData();
void handleStarData();
void makeHttpRequest();

unsigned long previousMillis = 0;
const long interval = 20000;  // 20 seconds

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}
void u8g2_string(uint8_t a) {

  u8g2.setFontDirection(3);
  // Convert Price to integer
  int priceInt = Price.toInt();

  // Draw the integer value on the display
  u8g2.drawStr(58, 31, String(priceInt).c_str());
  u8g2.drawStr(68, 17, "$");

  u8g2.setFontDirection(0);

  #define cross_block_width 50
  #define cross_block_height 32
  static const unsigned char cross_block_bits[] U8X8_PROGMEM  = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xfe, 0x07, 0x00, 0x00, 0x00, 0x80, 0x0f, 0xff, 0x0f, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0xff, 
  0x1f, 0x00, 0x00, 0x00, 0xf0, 0xbf, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x3f, 0x00, 
  0x00, 0x00, 0xf8, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 
  0xfc, 0xff, 0x0f, 0x7f, 0x00, 0x00, 0x00, 0xfc, 0xf9, 0x07, 0x7e, 0x00, 0x00, 0x00, 0xfc, 0xe0, 
  0x07, 0x7c, 0x00, 0x00, 0xf0, 0x7f, 0xe0, 0x03, 0xfc, 0x1f, 0x00, 0xf0, 0x7f, 0xc0, 0x03, 0xfc, 
  0x1f, 0x00, 0xf0, 0x7f, 0xc0, 0x03, 0xfc, 0x1f, 0x00, 0xf0, 0x3f, 0xc0, 0x03, 0xfc, 0x1f, 0x00, 
  0x00, 0x3c, 0xc0, 0x03, 0x7c, 0x00, 0x00, 0x00, 0x3c, 0xc0, 0x03, 0x7c, 0x00, 0x00, 0x00, 0x3c, 
  0xc0, 0x03, 0x7c, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0xff, 0xff, 
  0xff, 0x1f, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x1f, 
  0x00, 0x00, 0xfc, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 
  0xfc, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x3c, 0x00, 
  0x00, 0x7c, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x7c, 
  0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
   uint8_t frame_size = 28;
  u8g2.drawXBMP(0, 0, cross_block_width, cross_block_height, cross_block_bits);   

  #define dollar_block_width 16
  #define dollar_block_height 16  

  static const unsigned char dollar_block_bits[] U8X8_PROGMEM  = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xf9, 0xc7, 0xf0, 0x47, 0xe0, 0x63, 0xe0, 0x70, 0x86, 
    0x31, 0x86, 0x03, 0xe3, 0x07, 0xe1, 0x8f, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  if (up) {

    int top_arrow = 80;

    u8g2.drawTriangle(top_arrow - a + 5, 16, top_arrow + 20 - a, 2, top_arrow + 20 - a, 30);
    u8g2.drawBox(20 + top_arrow - a, 8, 20, 16);
    u8g2.drawXBMP(100-a, 8, dollar_block_width, dollar_block_height, dollar_block_bits); 

  } else {
    int down_arrow = 60;

    u8g2.drawTriangle(down_arrow + 55 + a, 16, down_arrow + 40 + a, 2, down_arrow + 40 + a, 30);
    u8g2.drawBox(20 + down_arrow + a, 8, 20, 16);
    u8g2.drawXBMP(85+a, 8, dollar_block_width, dollar_block_height, dollar_block_bits); 
  }
}

uint8_t draw_state = 0;

void setup() {
  zAxisServo.attach(D3);
  u8g2.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  initialize();
  makeHttpRequest();
}

void loop() {
  unsigned long currentMillis = millis();

  int priceInt = Price.toInt();
  int previousPriceInt = previousPrice.toInt(); // Convert previousPrice to integer

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    previousPrice = Price;
    makeHttpRequest();
  }



  // picture loop
  u8g2.clearBuffer();
  u8g2_prepare();
  u8g2_string(draw_state & 7);
  u8g2.sendBuffer();

  // increase the state
  draw_state++;
  if (draw_state >= 12 * 8)
    draw_state = 0;

  // deley between each page
  delay(100);

  Serial.print("Old Price: ");
  Serial.print(previousPrice);
  Serial.print(", New Price: ");
  Serial.println(Price);

  if (priceInt > previousPriceInt) {
    up = true;
  } else if (priceInt < previousPriceInt) {
    up = false;
  }

  // Other non-blocking tasks can be performed here
}

// Function definitions
void initialize() {
  wifiManager.connect();
}

void handlePlanetData() {
  httpManager.fetchData(httpUrl, Price);
}

void makeHttpRequest() {
  handlePlanetData();
  Serial.println(Price);
}
