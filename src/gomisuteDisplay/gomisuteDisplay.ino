#include <M5Stack.h>

void printPt16(const char* buf,uint16_t x, uint16_t y, int color){
  M5.Lcd.setTextColor(color);
  M5.Lcd.loadFont("genshin-regular-16pt", SD);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.printf(buf);
  M5.Lcd.unloadFont();
}

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(WHITE);
  
  printPt16("本日(2019/09/28)",0,0,BLACK);
  M5.Lcd.drawJpgFile(SD, "/gomi_mark01_moeru.jpg",0,16);
  printPt16("test",0,166,BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:

}
