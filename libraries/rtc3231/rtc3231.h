/*
MIT License

Copyright (c) [year] [fullname]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
  */

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
