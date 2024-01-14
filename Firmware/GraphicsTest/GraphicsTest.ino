#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X32_VISIONOX_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}
void u8g2_string(uint8_t a) {

  u8g2.setFontDirection(3);
  u8g2.drawStr(58, 31, String(41500 + a).c_str());
  u8g2.drawStr(68, 17, "$");
  Serial.println(a);

  u8g2.setFontDirection(0);

  int top_arrow = 9;

  u8g2.drawTriangle(top_arrow-a+5,16, top_arrow+20-a,2, top_arrow+20-a,30);
  u8g2.drawBox(20+top_arrow-a,8,20,16);

  int down_arrow = 60;

  u8g2.drawTriangle(down_arrow+55+a,16, down_arrow+40+a,2, down_arrow+40+a,30);
  u8g2.drawBox(20+down_arrow+a,8,20,16);
}

uint8_t draw_state = 0;

void setup(void) {
  u8g2.begin();
  Serial.begin(115200);
}

void loop(void) {
  // picture loop  
  u8g2.clearBuffer();
  u8g2_prepare();
  u8g2_string(draw_state&7);
  u8g2.sendBuffer();
  
  // increase the state
  draw_state++;
  if ( draw_state >= 12*8 )
    draw_state = 0;

  // deley between each page
  delay(100);

}
