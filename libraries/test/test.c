#include"test.h"

void testControl()
{
	if(0==motorInitStatus)
	{
		Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        pinMode(TEST_PIN,OUTPUT);
        motorInitStatus = 1;
	}

	digitalWrite(TEST_PIN,HIGH);
	delay_ms(500);
	digitalWrite(TEST_PIN,LOW);
	delay_ms(500);
}