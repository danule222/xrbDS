/**
 * @file date.h
 * @brief Date class that retrieves date/time from Nintendo DS RTC when
 * available.
 * @copyright 2025 Daniel Ramirez Morilla
 *
 * @author Daniel Ramirez Morilla
 * @date 2025-10-16
 */

#ifndef XRBDS_SYSTEM_DATE_H
#define XRBDS_SYSTEM_DATE_H

#include "core/types.h"

/**
 * @brief Class to handle date and time information.
 *
 * This class provides methods to retrieve the current date and time from the
 * Nintendo DS RTC (Real-Time Clock). It includes functionality to get
 * individual components of the date and time, as well as a method to format the
 * date and time as a string.
 */
class SystemDate {
public:
  /// @brief Default constructor initializing to epoch time.
  SystemDate() noexcept;

  /// @brief Parameterized constructor.
  SystemDate(int y, int mo, int d, int h, int mi, int s, int wd = 0) noexcept;

  /// @brief Get the current date and time from the system RTC.
  static SystemDate now() noexcept;

  /// @brief Update the current instance with the latest date and time.
  void update() noexcept;

  /// @brief Convert the date and time to a formatted string.
  FString toString() const;

  /// Getters for individual components

  /// @brief Get the year component.
  /// @return The year (e.g., 2022).
  int getYear() const noexcept { return year; }

  /// @brief Get the month component.
  /// @return The month (1-12).
  int getMonth() const noexcept { return month; }

  /// @brief Get the day component.
  /// @return The day of the month (1-31).
  int getDay() const noexcept { return day; }

  /// @brief Get the hour component.
  /// @return The hour of the day (0-23).
  int getHour() const noexcept { return hour; }

  /// @brief Get the minute component.
  /// @return The minute of the hour (0-59).
  int getMinute() const noexcept { return minute; }

  /// @brief Get the second component.
  /// @return The second of the minute (0-59).
  int getSecond() const noexcept { return second; }

  /// @brief Get the weekday component.
  /// @return The weekday (0-6, where 0 is Sunday).
  int getWeekday() const noexcept { return weekday; }

private:
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int weekday;
};

#endif // XRBDS_SYSTEM_DATE_H