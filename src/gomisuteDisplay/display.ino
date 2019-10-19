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

int getColor(enum DayOfWeek dayOfWeek){
  int color = BLACK;

  if(dayOfWeek == SATURDAY) color = BLUE;
  else if(dayOfWeek == SUNDAY) color = RED;

  return color;
}

void printMainText(const char* buf,int color,int index){
  if(buf == NULL) return;
  if(index >= SUB_INDEX_MAX)  return;
  printPt16(buf,ORGPOINTX + (MAIN_OFFSETX * index),MAIN_TEXT_ORGPOINTY,color);
}

void printMainTextToday(const char* YYYYMMDDString,enum DayOfWeek dayOfWeek){
  char date[10] = {0};
  int strOffset = 0;

  printPt16("本日 ",ORGPOINTX,MAIN_TEXT_ORGPOINTY,BLACK);
  strOffset = 5;
  // YYYYを除去
  memcpy(date,YYYYMMDDString + 5,strlen(YYYYMMDDString + 5));
  printPt16(date,ORGPOINTX + (strOffset * 8),MAIN_TEXT_ORGPOINTY,BLACK);
  strOffset = strOffset + strlen(date);
  printPt16("(",ORGPOINTX + (strOffset * 8),MAIN_TEXT_ORGPOINTY,BLACK);
  strOffset = strOffset + 1;
  printPt16(dayOfWeekEnumToString(dayOfWeek),ORGPOINTX + (strOffset * 8),MAIN_TEXT_ORGPOINTY,getColor(dayOfWeek));
  strOffset = strOffset + 2;
  printPt16(")",ORGPOINTX + (strOffset * 8),MAIN_TEXT_ORGPOINTY,BLACK);
}

void printMainTextTomorrow(const char* YYYYMMDDString,enum DayOfWeek dayOfWeek){
  char date[10] = {0};
  int strOffset = 0;

  printPt16("明日 ",ORGPOINTX + MAIN_OFFSETX,MAIN_TEXT_ORGPOINTY,BLACK);
  strOffset = 5;
  // YYYYを除去
  memcpy(date,YYYYMMDDString + 5,strlen(YYYYMMDDString + 5));
  printPt16(date,ORGPOINTX + MAIN_OFFSETX + (strOffset * 8),MAIN_TEXT_ORGPOINTY,BLACK);
  strOffset = strOffset + strlen(date);
  printPt16("(",ORGPOINTX + MAIN_OFFSETX + (strOffset * 8),MAIN_TEXT_ORGPOINTY,BLACK);
  strOffset = strOffset + 1;
  printPt16(dayOfWeekEnumToString(dayOfWeek),ORGPOINTX + MAIN_OFFSETX + (strOffset * 8),MAIN_TEXT_ORGPOINTY,getColor(dayOfWeek));
  strOffset = strOffset + 2;
  printPt16(")",ORGPOINTX + MAIN_OFFSETX + (strOffset * 8),MAIN_TEXT_ORGPOINTY,BLACK);
}

void printMainPicture(String fileName,int index){
  char buf[64] = {0};
  
  fileName.toCharArray(buf,sizeof(buf));
  if(buf == NULL) return;
  if(index >= MAIN_INDEX_MAX)  return;
  M5.Lcd.drawJpgFile(SD, buf,ORGPOINTX + (MAIN_OFFSETX * index),MAIN_PICTURE_ORGPOINTY);
}

void printSubText(const char* buf,int color,int index){
  if(buf == NULL) return;
  if(index >= SUB_INDEX_MAX)  return;
  printPt16(buf,17/* 即値オフセット*/ + ORGPOINTX + (SUB_OFFSETX * index),SUB_TEXT_ORGPOINTY,color);
}

void printSubTextDayOfWeek(enum DayOfWeek dayOfWeek,int index){
  printSubText(dayOfWeekEnumToString(dayOfWeek),getColor(dayOfWeek),index);
}

void printSubPicture(String fileName,int index){
  char buf[64] = {0};
  
  fileName.toCharArray(buf,sizeof(buf));
  if(buf == NULL) return;
  if(index >= SUB_INDEX_MAX)  return;
  M5.Lcd.drawJpgFile(SD, buf,ORGPOINTX + (SUB_OFFSETX * index),SUB_PICTURE_ORGPOINTY);
}
