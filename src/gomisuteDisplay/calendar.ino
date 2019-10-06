char KANEN_CHAR[] = { 0x89 , 0xC2 , 0x94 , 0x52 };  // 可燃
char FUNEN_CHAR[] = { 0x95 , 0x73 , 0x94 , 0x52 };  // 不燃
char HOKAPURA_CHAR[] = { 0x91 , 0xBC , 0x83 , 0x76 , 0x83 , 0x89 }; // 他プラ
char REPURA_CHAR[] = { 0x83 , 0x8A , 0x83 , 0x76 , 0x83 , 0x89 }; // リプラ
char SHIGEN_CHAR[] = { 0x8E , 0x91 , 0x8C , 0xB9 }; // 資源

char SUNDAY_CHAR[] = { 0x93 , 0xFA }; // 日
char MONDAY_CHAR[] = { 0x8C , 0x8E }; // 月
char TUESDAY_CHAR[] =  { 0x89 , 0xCE }; // 火
char WEDNESDAY_CHAR[] =  { 0x90 , 0x85 }; // 水 
char THURSDAY_CHAR[] = { 0x96 , 0xD8 }; // 木
char FRIDAY_CHAR[] =  { 0x8B, 0xE0 }; // 金
char SATURDAY_CHAR[] = { 0x93 , 0x79 }; // 土 


enum GomiShubetsu gomiStringToEnum(const char* gomiShubetsuChar){
  enum GomiShubetsu gomiShubetsu = GOMI_SHUBETSU_FUMEI;
  
  if(memcmp(gomiShubetsuChar,KANEN_CHAR,sizeof(KANEN_CHAR)) == 0){
    gomiShubetsu = KANEN;
  }else if(memcmp(gomiShubetsuChar,FUNEN_CHAR,sizeof(FUNEN_CHAR)) == 0){
    gomiShubetsu = FUNEN;
  }else if(memcmp(gomiShubetsuChar,HOKAPURA_CHAR,sizeof(HOKAPURA_CHAR)) == 0){
    gomiShubetsu = HOKAPURA;
  }else if(memcmp(gomiShubetsuChar,REPURA_CHAR,sizeof(REPURA_CHAR)) == 0){
    gomiShubetsu = RIPURA;
  }else if(memcmp(gomiShubetsuChar,SHIGEN_CHAR,sizeof(SHIGEN_CHAR)) == 0){
    gomiShubetsu = SHIGEN;
  }

  return gomiShubetsu;
}

enum DayOfWeek dayOfWeekStringToEnum(const char* dayOfWeekChar){
  enum DayOfWeek dayOfWeek = DAY_OF_WEEK_FUMEI;

  if(memcmp(dayOfWeekChar,SUNDAY_CHAR,sizeof(SUNDAY_CHAR)) == 0){
    dayOfWeek = SUNDAY;
  }else if(memcmp(dayOfWeekChar,MONDAY_CHAR,sizeof(MONDAY_CHAR)) == 0){
    dayOfWeek = MONDAY;
  }else if(memcmp(dayOfWeekChar,TUESDAY_CHAR,sizeof(TUESDAY_CHAR)) == 0){
    dayOfWeek = TUESDAY;
  }else if(memcmp(dayOfWeekChar,WEDNESDAY_CHAR,sizeof(WEDNESDAY_CHAR)) == 0){
    dayOfWeek = WEDNESDAY;
  }else if(memcmp(dayOfWeekChar,THURSDAY_CHAR,sizeof(THURSDAY_CHAR)) == 0){
    dayOfWeek = THURSDAY;
  }else if(memcmp(dayOfWeekChar,FRIDAY_CHAR,sizeof(FRIDAY_CHAR)) == 0){
    dayOfWeek = FRIDAY;
  }else if(memcmp(dayOfWeekChar,SATURDAY_CHAR,sizeof(SATURDAY_CHAR)) == 0){
    dayOfWeek = SATURDAY;
  }

  return dayOfWeek;
}

bool loadGomiCalendarFromCSV(struct GomiCalendar *gomiCalendar,const char* fileName,int number){
  File file = SD.open(fileName);
  const char delimiter = ',';
  const char lineBreakChar1 = 0xd;
  const char lineBreakChar2 = 0xa;
  const char endOfFile = 0xff;
  bool endOfFileFlg = false;

  int row = 0;
  int column = 0;
  char buf[64] = {0}; // 64は適当
  int bufIndex = 0;

  while(1){
    char c = file.read();
    switch(c){
    case delimiter:
      // Serial.printf("delimiter\n");
      // 文字のコピー
      if(row > 0){
        int gomiCalendarIndex = row - 1;
        if(column == 0){  // day field
          memcpy((gomiCalendar + gomiCalendarIndex)->day,buf,10);
          Serial.printf("[%d]%s write\n",gomiCalendarIndex,(gomiCalendar + gomiCalendarIndex)->day);
        }else if(column == 1){
          ( gomiCalendar + gomiCalendarIndex)->dayOfWeek = dayOfWeekStringToEnum(buf);
          Serial.printf("[%d]%d write\n",gomiCalendarIndex,( gomiCalendar + gomiCalendarIndex )->dayOfWeek);
        }else if(column == ( number - 1 + 2 )){
          ( gomiCalendar + gomiCalendarIndex )->gomiShubetsu = gomiStringToEnum(buf);
          Serial.printf("[%d]%d write\n",gomiCalendarIndex,( gomiCalendar + gomiCalendarIndex )->gomiShubetsu);
        }
      }
      column = column + 1;
      // bufferの初期化
      bufIndex = 0;
      memset(buf,0x0,64);
      break;
    case lineBreakChar1:
      break;
    case lineBreakChar2:
      row = row + 1;
      column = 0;
      // bufferの初期化
      bufIndex = 0;
      memset(buf,0x0,64);
      break;
    case endOfFile:
      Serial.printf("endOfFile\n");
      endOfFileFlg = true;
      break;
    default:
      buf[bufIndex++] = c;
    }

    if(endOfFileFlg == true) break;
  }
}

bool getTermGomisuteCalendar(struct GomiCalendar *gomiCalendar,struct GomiCalendar *gomiMasterCalendar,const char *baseDayString,int numberOfRecords){
  int baseIndex = -1;
  bool result = false;

  // baseIndexを探す
  Serial.printf("target[%s]",baseDayString);
  // for(int index = 0;index < DATA_RECORD_NUM;index++){
  for(int index = 188;index < 192;index++){
    printf("%s\n",(gomiMasterCalendar + index)->day);
    if(memcmp((gomiMasterCalendar + index)->day,baseDayString,strlen(baseDayString)) == 0){
      baseIndex = index;
      printf("good\n");
      break;
    }
  }

  if(baseIndex != -1){
    // baseIndexからコピーする
    Serial.printf("copy size[%d]",sizeof(struct GomiCalendar));
    for(int index = 0;index < numberOfRecords;index++){
      if(index >= DATA_RECORD_NUM) break;
      Serial.printf("copy do[%d]",index);
      memcpy((gomiCalendar + index),(gomiMasterCalendar + baseIndex + index),sizeof(struct GomiCalendar));
    }
    result = true;
  }

  return result;
}
