#include <M5Stack.h>
#include <WiFi.h>
#include <ArduinoJson.h>

const char* ntpServer =  "ntp.jst.mfeed.ad.jp";
const long  gmtOffset_sec = 9 * 3600;
const int   daylightOffset_sec = 0;

#define DATA_RECORD_NUM 400
#define DATA_DISPLAY_RECORD_NUM 8 // today + tomorrow + next day6
#define DATE_BUFF_LEN 12

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

void setup() {

  Serial.begin(115200);
  Serial.println("start");
  
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(WHITE);

  // wifi setup
  DynamicJsonDocument doc(1024);
  int wifiConfigIndex = 0;
  char wifiConfig[256] = {0};
  File file = SD.open("/config/wifiConfig.json");
  if (file) {
    while (file.available()) {
      char readData = file.read();
      Serial.write(readData);
      wifiConfig[wifiConfigIndex] = readData;
      wifiConfigIndex = wifiConfigIndex + 1;
    }
    file.close();
  }
  deserializeJson(doc, wifiConfig);
  const char *ssid = doc["ssid"];
  const char *password = doc["password"];
  Serial.printf("[ssid]%s ",ssid);
  Serial.printf("[password]%s ",password);
  

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  char dateString[DATE_BUFF_LEN] = {0};
  sprintf(dateString,"%d/%d/%d",timeinfo.tm_year + 1900,timeinfo.tm_mon + 1,timeinfo.tm_mday);
  Serial.printf("[date]%s",dateString);
  
  // csv read
  Serial.println("read start");
  loadGomiCalendarFromCSV(gomiCalendar,"/test.csv",5);
  Serial.println("read end");

  Serial.println("get start");
  bool result = getTermGomisuteCalendar(gomiDisplayCalendar,gomiCalendar,dateString,DATA_DISPLAY_RECORD_NUM);
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
