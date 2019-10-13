//wifiConfig.h
#ifndef WIFI_CONFIG_H_INCLUDE
#define WIFI_CONFIG_H_INCLUDE

class  WifiConfig{
  public:
    bool wifiConfigLoad(const char *wifiConfiglePath);
    void GetSsid(char *outSsid);
    void GetPassword(char *outPassword);
    
  private:
    char ssid[32];
    char password[32];
};

#endif
