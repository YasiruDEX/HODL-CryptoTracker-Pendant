#include "LCDManager.h"

LCDManager::LCDManager(uint8_t lcdAddress, uint8_t lcdCols, uint8_t lcdRows)
  : lcd(lcdAddress, lcdCols, lcdRows) {}

void LCDManager::init() {
  lcd.init();
}

void LCDManager::backlight() {
  lcd.backlight();
}

void LCDManager::clear() {
  lcd.clear();
}

void LCDManager::setCursor(uint8_t col, uint8_t row) {
  lcd.setCursor(col, row);
}

void LCDManager::print(const String message) {
  lcd.print(message);
}
