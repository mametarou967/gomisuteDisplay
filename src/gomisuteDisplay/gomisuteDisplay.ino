#include <M5Stack.h>

// main window offset
#define MAIN_TEXT_OFFSETY  0
#define MAIN_PICTURE_OFFSETY 24
#define MAIN1_OFFSETX  10
#define MAIN2_OFFSETX  160

// sub window offset
#define SUB_TEXT_ORGPOINTY 184
#define SUB_PICTURE_ORGPOINTY 200
#define ORGPOINTX 10
#define SUB_OFFSETX 50 
#define SUB_INDEX_MAX 6


void printPt16(const char* buf,uint16_t x, uint16_t y, int color){
  M5.Lcd.setTextColor(color);
  M5.Lcd.loadFont("font/genshin-regular-16pt", SD);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.printf(buf);
  M5.Lcd.unloadFont();
}

void printMain1Text(const char* buf){
  printPt16(buf,MAIN1_OFFSETX,MAIN_TEXT_OFFSETY,BLACK);
}

void printMain1Picture(const char* fileName){
  M5.Lcd.drawJpgFile(SD, fileName,MAIN1_OFFSETX,MAIN_PICTURE_OFFSETY);
}

void printMain2Text(const char* buf){
  printPt16(buf,MAIN2_OFFSETX,MAIN_TEXT_OFFSETY,BLACK);
}

void printMain2Picture(const char* fileName){
  M5.Lcd.drawJpgFile(SD, fileName,MAIN2_OFFSETX,MAIN_PICTURE_OFFSETY);
}


void printSubText(const char* buf,int index){
  if(index >= SUB_INDEX_MAX)  return;
  printPt16(buf,ORGPOINTX + (SUB_OFFSETX * index),SUB_TEXT_ORGPOINTY,BLACK);
}

void printSubPicture(const char* fileName,int index){
  if(index >= SUB_INDEX_MAX)  return;
  M5.Lcd.drawJpgFile(SD, fileName,ORGPOINTX + (SUB_OFFSETX * index),SUB_PICTURE_ORGPOINTY);
}


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(WHITE);
  
  printMain1Text("本日 10/30(月)");
  printMain1Picture("/pic150x150/moeru.jpg");
  printMain2Text("明日 10/31(火)");
  printMain2Picture("/pic150x150/can.jpg");
  // Sub
  printSubText("11/1(水)",0);
  printSubPicture("/pic50x50/moenai.jpg",0);
  printSubText("11/1(木)",1);
  printSubPicture("/pic50x50/petbottle.jpg",1);
  printSubText("11/1(金)",2);
  printSubPicture("/pic50x50/plastic.jpg",2);
  printSubText("11/1(土)",3);
  printSubPicture("/pic50x50/shigen.jpg",3);
  printSubText("11/1(日)",4);
  printSubPicture("/pic50x50/sonohoka.jpg",4);
  printSubText("11/1(月)",5);
  printSubPicture("/pic50x50/blank.jpg",5);
}

void loop() {
  // put your main code here, to run repeatedly:

}
