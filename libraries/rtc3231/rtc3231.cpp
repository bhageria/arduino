/*
MIT License

Copyright (c) 2019 Vivek Bhageria

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

#include"rtc3231.h"

struct date rtc;

void initRTC3231()
{
  Wire.begin();
}

uint8_t getSeconds()
{
  readTime();
  return rtc.second;
}

uint8_t getMinutes()
{
  readTime();
  return rtc.minute;
}

uint8_t getHours()
{
  readTime();
  return rtc.hour;
}

uint8_t getDayOfWeek()
{
    readTime();
    return rtc.dayOfWeek;
}

String getNameOfDay()
{
  char *dayOfWeek[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
  readTime();
  return dayOfWeek[rtc.dayOfWeek - 1];
}

uint8_t getDay()
{
  readTime();
  return rtc.day;
}

uint8_t getMonth()
{
  readTime();
  return rtc.month;
}

uint8_t getYear()
{
  readTime();
  return rtc.year;
}


uint8_t decToBcd(uint8_t val)
{
  return( (val/10*16) + (val%10) );
}

uint8_t bcdToDec(uint8_t val)
{
  return( (val/16*10) + (val%16) );
}


int setTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t dayOfWeek, uint8_t
dayOfMonth, uint8_t month, uint8_t year)
{
 
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second)); 
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour)); 
  Wire.write(decToBcd(dayOfWeek)); 
  Wire.write(decToBcd(dayOfMonth)); 
  Wire.write(decToBcd(month)); 
  Wire.write(decToBcd(year)); 
  Wire.endTransmission();
  return 0;
}


void readTime()
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); 
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  
  rtc.second = bcdToDec(Wire.read() & 0x7f);
  rtc.minute = bcdToDec(Wire.read());
  rtc.hour = bcdToDec(Wire.read() & 0x3f);
  rtc.dayOfWeek = bcdToDec(Wire.read());
  rtc.day = bcdToDec(Wire.read());
  rtc.month = bcdToDec(Wire.read());
  rtc.year = bcdToDec(Wire.read());
}


String getTime()
{
  String fullTime;
  readTime();

  fullTime = String();
  
  //rtc.time.concat(rtc.hour);
  fullTime =  rtc.hour;
  fullTime.concat(":");
  fullTime.concat(rtc.minute);
  fullTime.concat(":");
  fullTime.concat(rtc.second);
  
  return fullTime;
}

String getDate()
{
  String fullDate;
  readTime();
  
  fullDate = String();

  fullDate =  rtc.day;
  fullDate.concat("/");
  fullDate.concat(rtc.month);
  fullDate.concat("/");
  fullDate.concat(rtc.year);
  return fullDate;
}
