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

//Initialize the RTC. It initializes the I2C communication
void initRTC3231()
{
  Wire.begin(); //Initialize I2C
}

//Get the seconds
uint8_t getSeconds()
{
  struct date temp;
  readTime(&temp);
  return temp.second;
}

//Get the minutes
uint8_t getMinutes()
{
  struct date temp;
  readTime(&temp);
  return temp.minute;
}

//Get the hours
uint8_t getHours()
{
  struct date temp;
  readTime(&temp);
  return temp.hour;
}

//Get the Day of the Week - Sunday=1, Saturday=7
uint8_t getDayOfWeek()
{
  struct date temp;
  readTime(&temp);
  return temp.dayOfWeek;
}

//Get Name of the day of the week
String getNameOfDay()
{
  char *dayOfWeek[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
  struct date temp;
  readTime(&temp);
  return dayOfWeek[temp.dayOfWeek - 1];
}

//Get the Day
uint8_t getDay()
{
  struct date temp;
  readTime(&temp);
  return temp.day;
}

//Get the Month
uint8_t getMonth()
{
  struct date temp;
  readTime(&temp);
  return temp.month;
}

//Get the Year
uint8_t getYear()
{
  struct date temp;
  readTime(&temp);
  return temp.year;
}

//Convert dec to BCD because the module understands only BCD
uint8_t decToBcd(uint8_t val)
{
  return( ((val/10)<<4) + (val%10) );
}

//Convert BCD to Dec
uint8_t bcdToDec(uint8_t val)
{
  return( ((val>>4)*10) + (val%16) );
}

//Set the time. Right now it supports only 24hr format
int setTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t dayOfWeek, uint8_t
dayOfMonth, uint8_t month, uint8_t year)
{
 
  Wire.beginTransmission(DS3231_I2C_ADDRESS); //Begin transmission
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

//Reat the time and date from the RTC
void readTime(struct date *temp)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); 
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  
  temp->second = bcdToDec(Wire.read() & 0x7f);
  temp->minute = bcdToDec(Wire.read());
  temp->hour = bcdToDec(Wire.read() & 0x3f);
  temp->dayOfWeek = bcdToDec(Wire.read());
  temp->day = bcdToDec(Wire.read());
  temp->month = bcdToDec(Wire.read());
  temp->year = bcdToDec(Wire.read());
}


String getTime()
{
  String fullTime;
  struct date temp;
  readTime(&temp);

  fullTime = String();
  
  //rtc.time.concat(rtc.hour);
  fullTime =  temp.hour;
  fullTime.concat(":");
  fullTime.concat(temp.minute);
  fullTime.concat(":");
  fullTime.concat(temp.second);
  
  return fullTime;
}

String getDate()
{
  String fullDate;
  struct date temp;
  readTime(&temp);
  
  fullDate = String();

  fullDate =  temp.day;
  fullDate.concat("/");
  fullDate.concat(temp.month);
  fullDate.concat("/");
  fullDate.concat(temp.year);
  return fullDate;
}
