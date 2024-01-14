#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include <LiquidCrystal_I2C.h>

class LCDManager {
public:
  LCDManager(uint8_t lcdAddress, uint8_t lcdCols, uint8_t lcdRows);
  void init();
  void backlight();
  void clear();
  void setCursor(uint8_t col, uint8_t row);
  void print(const String message);
private:
  LiquidCrystal_I2C lcd;
};

#endif
