#include "system/system_date.h"

#include <iomanip>

SystemDate::SystemDate() noexcept
    : year(1970), month(1), day(1), hour(0), minute(0), second(0), weekday(4) {}

SystemDate::SystemDate(int y, int mo, int d, int h, int mi, int s,
                       int wd) noexcept
    : year(y), month(mo), day(d), hour(h), minute(mi), second(s), weekday(wd) {}

SystemDate SystemDate::now() noexcept {
  time_t unixTime = time(NULL);
  struct tm *timeStruct = gmtime((const time_t *)&unixTime);

  return SystemDate(timeStruct->tm_year + 1900, timeStruct->tm_mon + 1,
                    timeStruct->tm_mday, timeStruct->tm_hour,
                    timeStruct->tm_min, timeStruct->tm_sec,
                    timeStruct->tm_wday);
}

void SystemDate::update() noexcept { *this = now(); }

FString SystemDate::toString() const {
  std::ostringstream ss;
  ss << std::setfill('0') << std::setw(4) << year << '-' << std::setw(2)
     << month << '-' << std::setw(2) << day << ' ' << std::setw(2) << hour
     << ':' << std::setw(2) << minute << ':' << std::setw(2) << second;
  return ss.str();
}