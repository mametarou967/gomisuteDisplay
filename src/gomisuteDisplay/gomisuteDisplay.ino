#include <M5Stack.h>

// common window
#define ORGPOINTX 10

// main window offset
#define MAIN_TEXT_ORGPOINTY  0
#define MAIN_PICTURE_ORGPOINTY 24
#define MAIN_OFFSETX  150
#define MAIN_INDEX_MAX 2

// sub window offset
#define SUB_TEXT_ORGPOINTY 174
#define SUB_PICTURE_ORGPOINTY 190
#define SUB_OFFSETX 50
#define SUB_INDEX_MAX 6


void printPt16(const char* buf,uint16_t x, uint16_t y, int color){
  M5.Lcd.setTextColor(color);
  M5.Lcd.loadFont("font/genshin-regular-16pt", SD);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.printf(buf);
  M5.Lcd.unloadFont();
}

void printMainText(const char* buf,int color,int index){
  if(index >= SUB_INDEX_MAX)  return;
  printPt16(buf,ORGPOINTX + (MAIN_OFFSETX * index),MAIN_TEXT_ORGPOINTY,color);
}

void printMainPicture(const char* fileName,int index){
  if(index >= MAIN_INDEX_MAX)  return;
  M5.Lcd.drawJpgFile(SD, fileName,ORGPOINTX + (MAIN_OFFSETX * index),MAIN_PICTURE_ORGPOINTY);
}

void printSubText(const char* buf,int color,int index){
  if(index >= SUB_INDEX_MAX)  return;
  printPt16(buf,17/* 即値オフセット*/ + ORGPOINTX + (SUB_OFFSETX * index),SUB_TEXT_ORGPOINTY,color);
}

void printSubPicture(const char* fileName,int index){
  if(index >= SUB_INDEX_MAX)  return;
  M5.Lcd.drawJpgFile(SD, fileName,ORGPOINTX + (SUB_OFFSETX * index),SUB_PICTURE_ORGPOINTY);
}


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(WHITE);
  
  printMainText("本日 10/30(月)",BLACK,0);
  printMainPicture("/pic150x150/moeru.jpg",0);
  printMainText("明日 10/31(火)",BLACK,1);
  printMainPicture("/pic150x150/can.jpg",1);
  // Sub
  printSubText("水",BLACK,0);
  printSubPicture("/pic50x50/moenai.jpg",0);
  printSubText("木",BLACK,1);
  printSubPicture("/pic50x50/petbottle.jpg",1);
  printSubText("金",BLACK,2);
  printSubPicture("/pic50x50/plastic.jpg",2);
  printSubText("土",BLUE,3);
  printSubPicture("/pic50x50/shigen.jpg",3);
  printSubText("日",RED,4);
  printSubPicture("/pic50x50/sonohoka.jpg",4);
  printSubText("月",BLACK,5);
  printSubPicture("/pic50x50/blank.jpg",5);
}

void loop() {
  // put your main code here, to run repeatedly:

}
