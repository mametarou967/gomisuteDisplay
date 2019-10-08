#include <M5Stack.h>

#define DATA_RECORD_NUM 400
#define DATA_DISPLAY_RECORD_NUM 8 // today + tomorrow + next day6

enum FileSize{
  S50X50,
  S150X150
};

enum GomiShubetsu{
  KANEN,
  FUNEN,
  HOKAPURA,
  SHIGEN,
  RIPURA,
  SONOTA,
  GOMI_SHUBETSU_FUMEI
};

enum DayOfWeek{
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  DAY_OF_WEEK_FUMEI
};

struct GomiCalendar{
  char day[12];
  enum DayOfWeek dayOfWeek;
  enum GomiShubetsu gomiShubetsu;
};

struct GomiCalendar gomiCalendar[DATA_RECORD_NUM];
struct GomiCalendar gomiDisplayCalendar[DATA_DISPLAY_RECORD_NUM];

void setup() {

  Serial.begin(115200);
  Serial.println("start");
  
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(WHITE);

  Serial.println("read start");
  loadGomiCalendarFromCSV(gomiCalendar,"/test.csv",3);
  Serial.println("read end");

  Serial.println("get start");
  bool result = getTermGomisuteCalendar(gomiDisplayCalendar,gomiCalendar,"2019/10/19",DATA_DISPLAY_RECORD_NUM);
  if(result) Serial.println("get sucess");
  Serial.println("get end");

  for(int i = 0;i < DATA_DISPLAY_RECORD_NUM;i++){
    Serial.printf("[%s],%d,%d",gomiDisplayCalendar[i].day,gomiDisplayCalendar[i].dayOfWeek,gomiDisplayCalendar[i].gomiShubetsu);
  }

  // Main
  printMainTextToday(gomiDisplayCalendar[0].day,gomiDisplayCalendar[0].dayOfWeek);
  printMainPicture(getFilePath(gomiDisplayCalendar[0].gomiShubetsu,S150X150),0);
  printMainTextTomorrow(gomiDisplayCalendar[1].day,gomiDisplayCalendar[1].dayOfWeek);
  printMainPicture(getFilePath(gomiDisplayCalendar[1].gomiShubetsu,S150X150),1);
  // Sub
  for(int subIndex = 0;subIndex < 6;subIndex++ ){
    printSubTextDayOfWeek(gomiDisplayCalendar[subIndex + 2].dayOfWeek,subIndex);
    printSubPicture(getFilePath(gomiDisplayCalendar[subIndex + 2].gomiShubetsu,S50X50),subIndex);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
