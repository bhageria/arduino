/*
  
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

/******* 
 *  Version Control
 *  25-Feb-2020  Srinivas
 *  -------------------------
 *  main.h
 *  CALLED LoadMotorState in main - setup to power mtr after power cut
 *  CALLED loadLocalMotorState in main - loop to power mtr after power cut
 *  --------------------------
 *  motor_control.h
 *  ADDED eeprom.h to write and read motor sts
 *  ADDED checkMotorState, LoadMotorState, loadLocalMotorState to satisy mtr power state after powercut 
*******/

#include"main.h"
#include"wifi_control.h"
String data;
String check;

uint8_t serialStatus = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Device started");
  //SDInit();
}
 

void loop()
{
  if(wifiConnect == 0)
  {
    
    if(Serial.available())
    {
      data = Serial.readStringUntil('\n');
      Serial.println(sizeof(data));
      Serial.println((data));
      if(data == "wifis") //
      {
        //serialStatus = 0;
        Serial.println("stop");  //send 'stop' to the slave device to stop transmitting because wifi is connected
        wifiConnect = 1;
      }
      else
      {
        Serial.println("weird message");
      }
    } 
    wifiConnectStatus = 0;
  }
  else
  {
    if(wifiConnectStatus == 0 && wifiConnect == 1)
    {
      Serial.println("Entering wifi init");
      wifiInit(&wifiConnectStatus);
    }
    else
    {
      server.handleClient();
    }
  }
}
