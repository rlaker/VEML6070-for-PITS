/***************************************************
This is a library for the Adafruit VEML6070 UV Sensor Breakout
Designed specifically to work with the VEML6070 sensor from Adafruit
----> https://www.adafruit.com/products/2899
These sensors use I2C to communicate, 2 pins are required to
interface
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!
Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, all text above must be included in any redistribution
****************************************************/
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "VEML6070.h"
#include "gps.h"
#include "misc.h"

int VEML6070_begin(veml6070_integrationtime_t itime)
{
	int fdL;
	int fdH;
	wiringPiSetup();
	fdL = wiringPiI2CSetup(VEML6070_ADDR_L);
	fdH = wiringPiI2CSetup(VEML6070_ADDR_H);/*Use i2cdetect command to find your respective device address*/
	if (fdL == -1)
	{
		printf("Can't setup the I2C device\n");
		return 1;
	}
	if (fdH == -1)
	{
		printf("Can't setup the I2C device\n");
		return 1;
	}
	wiringPiI2CWrite(fdL, (itime << 2) | 0x02);
	delay(500);
	return 0;
}

uint16_t VEML6070_readUV() 
{	
	int fdL = wiringPiI2CSetup(VEML6070_ADDR_L);
	int fdH = wiringPiI2CSetup(VEML6070_ADDR_H); 
	uint16_t uvi = wiringPiI2CRead(fdH);
	uvi <<= 8;
	uvi |= wiringPiI2CRead(fdL);
	return uvi;
}

void *VEML6070Loop(void *some_void_ptr)
{

	struct TGPS *GPS;
	uint16_t UV_data;

	GPS = (struct TGPS *)some_void_ptr;


	VEML6070_begin(VEML6070_4_T);

	while (VEML6070_ADDR_L)
	{
		UV_data = VEML6070_readUV();
		GPS->UV_data = UV_data;
		printf("UV Intensity is %f\n", GPS->UV_data);
		sleep(10);
	}

	return 0;
}
