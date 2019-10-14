#include <M5Stack.h>
#include <WiFi.h>
#include <HCSR04.h>
#include "WifiConfig.h"
#include "Ntp.h"
#define DATA_RECORD_NUM 400
#define DATA_DISPLAY_RECORD_NUM 8 // today + tomorrow + next day6
#define DATE_BUFF_LEN 12

// triggerPinをpin2につなぎます
// echoPinをpin5につなぎます
UltraSonicDistanceSensor distanceSensor(2, 5);

char ssid[32] = {0};
char password[32] = {0};
char nowDateString[DATE_BUFF_LEN] = {0};
char preDateString[DATE_BUFF_LEN] = {0};

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
  char day[DATE_BUFF_LEN];
  enum DayOfWeek dayOfWeek;
  enum GomiShubetsu gomiShubetsu;
};

struct GomiCalendar gomiCalendar[DATA_RECORD_NUM];
struct GomiCalendar gomiDisplayCalendar[DATA_DISPLAY_RECORD_NUM];
struct tm brightStartTime;

bool GetLocalTime(struct tm *timenow){
  if (!getLocalTime(timenow)) {
    Serial.println("Failed to obtain time");
    return false;
  }
  return true;
}

void ConvertTmToString(char *dateString,struct tm *dateTm){
  sprintf(dateString,"%d/%d/%d",dateTm->tm_year + 1900,dateTm->tm_mon + 1,dateTm->tm_mday);
}

void displayAll(struct GomiCalendar gomiDisplayCalendar[]){
  M5.Lcd.clear(WHITE);
  
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

void setup() {

  Serial.begin(115200);
  Serial.println("start");
  
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(WHITE);
  M5.Lcd.setBrightness(90);

  WifiConfig wifiConfig;
  wifiConfig.wifiConfigLoad("/config/wifiConfig.json");
  wifiConfig.GetSsid(ssid);
  wifiConfig.GetPassword(password);
 
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  Serial.printf("password to %s ", password);
  WiFi.disconnect(true);
  WiFi.disconnect(true,true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("CONNECTED");

  // NTPより時間の取得
  struct tm timeinfo;
  Ntp ntp;
  ntp.GetTime();
  
  // 取得した時間を整形して保持
  char dateString[DATE_BUFF_LEN] = {0};
  GetLocalTime(&timeinfo);
  ConvertTmToString(nowDateString,&timeinfo);
  strcpy(preDateString,nowDateString);
  Serial.printf("now[date]%s",nowDateString);
  Serial.printf("pre[date]%s",preDateString);
  
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  
  // csv read
  Serial.println("read start");
  loadGomiCalendarFromCSV(gomiCalendar,"/test.csv",5);
  Serial.println("read end");

  Serial.println("get start");
  bool result = getTermGomisuteCalendar(gomiDisplayCalendar,gomiCalendar,nowDateString,DATA_DISPLAY_RECORD_NUM);
  if(result) Serial.println("get sucess");
  Serial.println("get end");

  displayAll(gomiDisplayCalendar);
  // 輝度基準時間をすべての画像の描画後に設定する
  GetLocalTime(&brightStartTime);
}


void loop() {

  // 現在時刻を取得
  struct tm timeinfo;
  GetLocalTime(&timeinfo);
  ConvertTmToString(nowDateString,&timeinfo);

  // 日付が変更された場合は表示を更新
  if(strcmp(preDateString,nowDateString) != 0){
    Serial.println("diff");
    Serial.printf("now[date]%s",nowDateString);
    Serial.printf("pre[date]%s",preDateString);
    bool result = getTermGomisuteCalendar(gomiDisplayCalendar,gomiCalendar,nowDateString,DATA_DISPLAY_RECORD_NUM);
    if(result) Serial.println("get sucess");

    displayAll(gomiDisplayCalendar);

    // 前回日時を更新
    memcpy(preDateString,nowDateString,strlen(preDateString));
  }

  // ボタンを押すか、一定の距離に人が近づくとLEDを明るくする
  double distance = distanceSensor.measureDistanceCm();
  Serial.println(distance);
  if(M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()){
    Serial.println("button pressed");
    M5.Lcd.setBrightness(90);
    GetLocalTime(&brightStartTime); // 明るくした時間を記録
  }else if((distance >= 0.0) && (distance <= 30.0)){
    Serial.println("distance sence");
    M5.Lcd.setBrightness(90);
    GetLocalTime(&brightStartTime); // 明るくした時間を記録
  }

  Serial.printf("pre[]%ld\n",mktime(&brightStartTime));
  Serial.printf("now[]%ld\n",mktime(&timeinfo));
  Serial.printf("diff[]%lf\n",difftime(mktime(&brightStartTime),mktime(&timeinfo)));
  // LEDを明るくしてから20秒後にLEDを暗くする
  if( difftime(mktime(&timeinfo),mktime(&brightStartTime)) > 20.0 ){
    Serial.println("time passed");
    M5.Lcd.setBrightness(1);
  }

  // put your main code here, to run repeatedly:
  delay(1000);  // 1秒
  M5.update();
}
