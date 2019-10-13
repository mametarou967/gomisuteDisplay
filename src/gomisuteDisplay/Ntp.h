#ifndef NTP_H_INCLUDE
#define NTP_H_INCLUDE
#include <M5Stack.h>

class Ntp{
  public:
    bool GetTime(struct tm *timenow);

};

#endif
