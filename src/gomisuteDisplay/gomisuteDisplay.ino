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
  bool result = getTermGomisuteCalendar(gomiDisplayCalendar,gomiCalendar,"2019/10/6",DATA_DISPLAY_RECORD_NUM);
  if(result) Serial.println("get sucess");
  Serial.println("get end");

  for(int i = 0;i < DATA_DISPLAY_RECORD_NUM;i++){
    Serial.printf("[%s],%d,%d",gomiDisplayCalendar[i].day,gomiDisplayCalendar[i].dayOfWeek,gomiDisplayCalendar[i].gomiShubetsu);
  }

  // test print
  printMainText("本日 10/30(月)",BLACK,0);
  printMainPicture(getFilePath(gomiDisplayCalendar[0].gomiShubetsu,S150X150),0);
  printMainText("明日 10/31(火)",BLACK,1);
  printMainPicture(getFilePath(gomiDisplayCalendar[1].gomiShubetsu,S150X150),1);
  // Sub
  printSubText("水",BLACK,0);
  printSubPicture(getFilePath(gomiDisplayCalendar[2].gomiShubetsu,S50X50),0);
  printSubText("木",BLACK,1);
  printSubPicture(getFilePath(gomiDisplayCalendar[3].gomiShubetsu,S50X50),1);
  printSubText("金",BLACK,2);
  printSubPicture(getFilePath(gomiDisplayCalendar[4].gomiShubetsu,S50X50),2);
  printSubText("土",BLUE,3);
  printSubPicture(getFilePath(gomiDisplayCalendar[5].gomiShubetsu,S50X50),3);
  printSubText("日",RED,4);
  printSubPicture(getFilePath(gomiDisplayCalendar[6].gomiShubetsu,S50X50),4);
  printSubText("月",BLACK,5);
  printSubPicture(getFilePath(gomiDisplayCalendar[7].gomiShubetsu,S50X50),5);
}

void loop() {
  // put your main code here, to run repeatedly:

}
