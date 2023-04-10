/*
 * rtc_module.cpp
 *
 *  Created on: Apr 2, 2023
 *      Author: renatobarresi
 */

#include "rtc_module.h"
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

/* Private variables */
static RTC_HandleTypeDef hrtc;

/* Private functions */

/**
 * @brief Convert a decimal number to a Binary-Coded Decimal (BCD) representation.
 *
 * This function takes an unsigned integer as input and returns its BCD
 * representation. The input number must be less than or equal to 9999, as the
 * BCD representation is limited to 4 decimal digits (16 bits).
 *
 * @param num The decimal number to convert (0 <= num <= 9999).
 * @return The BCD representation of the input decimal number.
 */
uint32_t dec2bcd(uint32_t num) {
    if (num > 9999) {
        return 0xFFFF; // Invalid input, return maximum value
    }

    unsigned int ones = num % 10;
    unsigned int temp = num / 10;

    unsigned int tens = temp % 10;
    temp /= 10;

    unsigned int hundreds = temp % 10;
    temp /= 10;

    unsigned int thousands = temp;

    return (thousands << 12) | (hundreds << 8) | (tens << 4) | ones;
}

/* Public methods */

/**
 * @brief initializes the RTC
 *
 * @return HAL_ok if operation was successful
 * @return HAL_Error if operation had an error
 */
HAL_StatusTypeDef RTCModule::init()
{
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_OK != HAL_RTC_Init(&hrtc))
  {
	return HAL_ERROR;
  }
  return HAL_OK;
}

void RTCModule::setTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    RTC_TimeTypeDef time = {0};
    time.Hours = hours;
    time.Minutes = minutes;
    time.Seconds = seconds;
    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
}

/**
 * @brief Set the RTC date.
 *
 * This method sets the RTC date, including week day, month, day, and year.
 *
 * @param weekDay The week day (1 = Monday, 2 = Tuesday, ..., 7 = Sunday).
 * @param month The month (1 = January, 2 = February, ..., 12 = December).
 * @param date The day of the month (1-31).
 * @param year The year (offset from 1900).
 */
void RTCModule::setDate(uint8_t weekDay, uint8_t month, uint8_t date, uint8_t year)
{
    RTC_DateTypeDef rtcDate = {0};
    rtcDate.WeekDay = weekDay;
    rtcDate.Month = month;
    rtcDate.Date = date;
    rtcDate.Year = year;
    HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);
}

void RTCModule::getTime(uint8_t* hours, uint8_t* minutes, uint8_t* seconds)
{
    RTC_TimeTypeDef time = {0};
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    *hours = time.Hours;
    *minutes = time.Minutes;
    *seconds = time.Seconds;
}

void RTCModule::getDate(uint8_t* weekDay, uint8_t* month, uint8_t* date, uint8_t* year)
{
    RTC_DateTypeDef rtcDate = {0};
    HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);
    *weekDay = rtcDate.WeekDay;
    *month = rtcDate.Month;
    *date = rtcDate.Date;
    *year = rtcDate.Year;
}

/**
 * @brief Set the time and date based on a formatted string.
 *
 * This method takes a reference to a string in the format "HH:mm:ss-dd/MM/yyyy"
 * and sets the RTC time and date accordingly using the setTime and setDate methods.
 *
 * @param pBuff The formatted string containing the time and date information.
 */
void RTCModule::setTimeAndDate(const std::string &pBuff)
{
    int hours, minutes, seconds;
    int day, month, year, weekDay;

    // Parse the input string using sscanf
    sscanf(pBuff.c_str(), "%02d:%02d:%02d-%02d/%02d/%04d", &hours, &minutes, &seconds, &day, &month, &year);

    // Calculate the day of the week using Zeller's Congruence
    // https://en.wikipedia.org/wiki/Zeller%27s_congruence
    int q = day;
    int m = month < 3 ? month + 12 : month;
    int K = year % 100;
    int J = year / 100;
    int h = (q + ((13 * (m + 1)) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7;

    // Convert h (0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday) to weekDay (1 = Monday, 2 = Tuesday, ..., 7 = Sunday)
    weekDay = (h + 5) % 7 + 1;

    // Set the time and date
    setTime(hours, minutes, seconds);
    setDate(weekDay, month, day, year - 1900);
}

/**
 * @brief Get the current time and date as a formatted string.
 *
 * This method returns the current time and date as a string in the format "HH:mm:ss-dd/MM/yyyy".
 *
 * @return A formatted string containing the current time and date.
 */
std::string RTCModule::getTimeAndDate() {
    uint8_t hours, minutes, seconds;
    uint8_t weekDay, month, date, year;

    // Get the current time and date
    getTime(&hours, &minutes, &seconds);
    getDate(&weekDay, &month, &date, &year);

    // Format the time and date as a string
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << static_cast<int>(hours) << ":"
        << std::setw(2) << static_cast<int>(minutes) << ":"
        << std::setw(2) << static_cast<int>(seconds) << "-"
        << std::setw(2) << static_cast<int>(date) << "/"
        << std::setw(2) << static_cast<int>(month) << "/"
        << std::setw(4) << static_cast<int>(year + 1900);

    return oss.str();
}
