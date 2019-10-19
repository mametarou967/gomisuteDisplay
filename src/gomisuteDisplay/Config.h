//Config.h
#ifndef CONFIG_H_INCLUDE
#define CONFIG_H_INCLUDE

class  Config{
  public:
    bool ConfigLoad(const char *ConfiglePath);
    void GetSsid(char *outSsid);
    void GetPassword(char *outPassword);
    bool GetOfflineDateActivate(void);
    void GetOfflineDate(char *outOfflineDated);
    
  private:
    char ssid[32];
    char password[32];
    int offlineDateActivate;
    char offlineDate[32];
};

#endif
