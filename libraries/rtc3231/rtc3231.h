#ifndef TwoWire_h
  #include "Wire.h"
#endif

#define DS3231_I2C_ADDRESS 0x68

struct date
{
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t dayOfWeek;
  uint8_t day;
  uint8_t month;
  uint8_t year;
  String time;
};


void initRTC3231();
uint8_t getSeconds();
uint8_t getMinutes();
uint8_t getHours();
uint8_t getDayOfWeek();
String getNameOfDay();
uint8_t getDay();
uint8_t getMonth();
uint8_t getYear();
uint8_t decToBcd(uint8_t val);
uint8_t bcdToDec(uint8_t val);
int setTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t dayOfWeek, uint8_t
dayOfMonth, uint8_t month, uint8_t year);
void readTime();
String getTime();
String getDate();
