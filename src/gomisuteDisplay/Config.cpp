// wifiConfig.cpp
#include <string.h>
#include <M5Stack.h>
#include <ArduinoJson.h>
#include "Config.h"

bool Config::ConfigLoad(const char *ConfiglePath){
  bool loadResult = false;
  bool readResult = false;
  int wifiConfigIndex = 0;
  char wifiConfig[256] = {0};
  const char *ssidChar;
  const char *passwordChar;
  const char *offlineDateChar;

  memset(ssid,0,sizeof(ssid));
  
  File file = SD.open(ConfiglePath);

  if (file) {
    while (file.available()) {
      char readData = file.read();
      Serial.write(readData);
      wifiConfig[wifiConfigIndex] = readData;
      wifiConfigIndex = wifiConfigIndex + 1;

    }
    file.close();
  }

  // Deserialization
  // Use a DynamicJsonDocument to store in the heap (recommended for documents larger than 1KB) 
  // -> 1024
  DynamicJsonDocument doc(1024);

  deserializeJson(doc, wifiConfig);

  wifiActivate = doc["wifiActivate"];
  Serial.printf("wifiActivate is %d \n", wifiActivate);
  ssidChar = doc["ssid"];
  Serial.printf("ssidChar is %s\n",ssidChar);
  passwordChar = doc["password"];
  offlineDateChar = doc["offlineDate"];
  
  memcpy(password,passwordChar,strlen(passwordChar));
  memcpy(offlineDate,offlineDateChar,strlen(offlineDateChar));
  memcpy(ssid,ssidChar,strlen(ssidChar));
  Serial.printf("ssid is %s\n",ssid);
  Serial.printf("password is %s\n",password);
  Serial.printf("offlineDate is %s\n",offlineDate);

  return true;
}

bool Config::GetWifiActivate(){
  if(wifiActivate == 0){
    return false;
  }else{
    return true;
  }
}

void Config::GetSsid(char *outSsid){
  memcpy(outSsid,ssid,strlen(ssid));
  return;
}

void Config::GetPassword(char *outPassword){
  memcpy(outPassword,password,strlen(password));
  return;
}
