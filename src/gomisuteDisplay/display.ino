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
  if(buf == NULL) return;
  if(index >= SUB_INDEX_MAX)  return;
  printPt16(buf,ORGPOINTX + (MAIN_OFFSETX * index),MAIN_TEXT_ORGPOINTY,color);
}

void printMainPicture(const char* fileName,int index){
  if(fileName == NULL) return;
  if(index >= MAIN_INDEX_MAX)  return;
  M5.Lcd.drawJpgFile(SD, fileName,ORGPOINTX + (MAIN_OFFSETX * index),MAIN_PICTURE_ORGPOINTY);
}

void printSubText(const char* buf,int color,int index){
  if(buf == NULL) return;
  if(index >= SUB_INDEX_MAX)  return;
  printPt16(buf,17/* 即値オフセット*/ + ORGPOINTX + (SUB_OFFSETX * index),SUB_TEXT_ORGPOINTY,color);
}

void printSubPicture(const char* fileName,int index){
  if(fileName == NULL) return;
  if(index >= SUB_INDEX_MAX)  return;
  M5.Lcd.drawJpgFile(SD, fileName,ORGPOINTX + (SUB_OFFSETX * index),SUB_PICTURE_ORGPOINTY);
}
