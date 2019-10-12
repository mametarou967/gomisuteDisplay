//wifiConfig.h
#ifndef WIFI_CONFIG_H_INCLUDE
#define WIFI_CONFIG_H_INCLUDE

class  WifiConfig{
  public:
    bool wifiConfigLoad(const char *wifiConfiglePath);
    String GetSsid(void);
    String GetPassword(void);
    
  private:
    String ssid;
    String password;
};

#endif
