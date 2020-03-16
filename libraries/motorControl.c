#include"motorControl.h"

void motorControl()
{
	if(0==motorInitStatus)
	{
		Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        pinMode(MOTOR_PIN,OUTPUT);
        motorInitStatus = 1;
	}
}