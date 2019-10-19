//Config.h
#ifndef CONFIG_H_INCLUDE
#define CONFIG_H_INCLUDE

class  Config{
  public:
    bool ConfigLoad(const char *ConfiglePath);
    bool GetWifiActivate(void);
    void GetSsid(char *outSsid);
    void GetPassword(char *outPassword);
    void GetOfflineDate(char *outOfflineDated);
    
  private:
    int wifiActivate;
    char ssid[32];
    char password[32];
    char offlineDate[32];
};

#endif
