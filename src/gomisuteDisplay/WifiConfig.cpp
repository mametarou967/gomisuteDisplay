// wifiConfig.cpp
#include <string.h>
#include <M5Stack.h>
#include <ArduinoJson.h>
#include "WifiConfig.h"

bool WifiConfig::wifiConfigLoad(const char *wifiConfiglePath){
  bool loadResult = false;
  bool readResult = false;
  int wifiConfigIndex = 0;
  char wifiConfig[256] = {0};
  const char *ssidChar;
  const char *passwordChar;
  
  File file = SD.open(wifiConfiglePath);

  if (file) {
    while (file.available()) {
      char readData = file.read();
      Serial.write(readData);
      wifiConfig[wifiConfigIndex] = readData;
      wifiConfigIndex = wifiConfigIndex + 1;

      /*
      if(WIFI_CONFIG_FILE_SIZE >= wifiConfigIndex){
        Serial.printf("wifiConfigLoad error size over");
        break;
      }
      */
    }
    file.close();
  }

  // Deserialization

  // Use a DynamicJsonDocument to store in the heap (recommended for documents larger than 1KB) 
  // -> 1024
  DynamicJsonDocument doc(1024);

  deserializeJson(doc, wifiConfig);
  ssidChar = doc["ssid"];
  passwordChar = doc["password"];
  memcpy(ssid,ssidChar,strlen(ssidChar));
  memcpy(password,passwordChar,strlen(passwordChar));
  Serial.println(ssid);
  Serial.println(password);

  return true;
}

void WifiConfig::GetSsid(char *outSsid){
  memcpy(outSsid,ssid,strlen(ssid));
  return;
}

void WifiConfig::GetPassword(char *outPassword){
  memcpy(outPassword,password,strlen(password));
  return;
}
