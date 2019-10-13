#include "Ntp.h"

void Ntp::GetTime(void){  //init and get the time
  const static char* ntpServer =  "ntp.jst.mfeed.ad.jp";
  const static long  gmtOffset_sec = 9 * 3600;
  const static int daylightOffset_sec = 0;
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // struct tm timeinfo;
  return;
}
