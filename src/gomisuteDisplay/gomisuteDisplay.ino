#include <M5Stack.h>

#define DATA_RECORD_NUM 400

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
  char day[10];
  enum DayOfWeek dayOfWeek;
  enum GomiShubetsu gomiShubetsu;
};

struct GomiCalendar gomiCalendar[DATA_RECORD_NUM];
struct GomiCalendar gomiCalendar

void setup() {

  Serial.begin(115200);
  Serial.println("start");
  
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(WHITE);

  Serial.println("read start");

  loadGomiCalendarFromCSV(gomiCalendar,"/test.csv",3);

  Serial.println("read end");

  // test print
  printMainText("本日 10/30(月)",BLACK,0);
  printMainPicture("/pic150x150/moeru.jpg",0);
  printMainText("明日 10/31(火)",BLACK,1);
  printMainPicture("/pic150x150/can.jpg",1);
  // Sub
  printSubText("水",BLACK,0);
  printSubPicture(getFilePath(FUNEN,S50X50),0);
  printSubText("木",BLACK,1);
  printSubPicture(getFilePath(HOKAPURA,S50X50),1);
  printSubText("金",BLACK,2);
  printSubPicture(getFilePath(SHIGEN,S50X50),2);
  printSubText("土",BLUE,3);
  printSubPicture(getFilePath(RIPURA,S50X50),3);
  printSubText("日",RED,4);
  printSubPicture(getFilePath(SONOTA,S50X50),4);
  printSubText("月",BLACK,5);
  printSubPicture(NULL,5);
}

void loop() {
  // put your main code here, to run repeatedly:

}
