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

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "VEML6070.h"

void VEML6070_begin(veml6070_integrationtime_t itime) {
	int fd;
	int data;
	wiringPiSetup();
	fdL = wiringPiI2CSetup(VEML6070_ADDR_L);
	fdH = wiringPiI2cSetup(VEML6070_ADDR_H);/*Use i2cdetect command to find your respective device address*/
	if (fdL == -1)
	{
		printf("Can't setup the I2C device\n");
		return -1;
	}
	if (fdH == -1)
	{
		printf("Can't setup the I2C device\n");
		return -1;
	}
	wiringPiI2CWrite(fdL, (itime << 2) | 0x02)
	delay(500);
}

uint16_t VEML6070_readUV() {
	
	uint16_t uvi = wiringPiI2CReadReg16(fdH);
	uvi <<= 8;
	uvi |= wiringPiI2CReadReg16(fdL);
	return uvi;
}

void *VEML6070Loop(void *some_void_ptr)
{
	struct TBME bme;
	struct TGPS *GPS;

	GPS = (struct TGPS *)some_void_ptr;

	VEML6070_begin(VEML6070_4_T)

	while (VEML6070_ADDR_L)
	{
		if ((fdL >= 0)
		{
			GPS->UV = VEML6070_readUV()

			printf("UV Intensity is %5.2lf\n", GPS->UV);
		}

		sleep(10);
	}

	return NULL;
}