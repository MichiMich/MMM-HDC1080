/*
 * ReadHDC1080.c
 *
 *This program reads the temperature and humidity from a i2c-connected
 * HDC1080 sensor.
 *
 * Returnvalues: 0=Temperature + humidty read successfully
 * 					1=Temperature error
 * 					2=Humidity error
 * 					-1=Temperature + humidity error
 *
 *Call example: int iHDC1080Result = ReadHDC1080();
 *
 *  Created on: 24.09.2016
 *      Author: Michael f.
 */
#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <sys/stat.h>

static int fd;

float fTemperaturetmp=0, fHumiditytmp=0;

int iI2cAddress = 0x40;

unsigned short i2c_read(unsigned char addr,
	                        unsigned char reg,
	                        int delay);


int main()
{
	

//Use i2c-2, this i2c works without problems on BBB and dont needs to be enabled in boot file
  fd=open("/dev/i2c-1", O_RDWR); //"/dev/i2c-2" on BBB, i2c-1 on Raspberry pi

  unsigned short temp = i2c_read(iI2cAddress,0,20000);
  unsigned short hum  = i2c_read(iI2cAddress,1,20000);

  close(fd);

  if ((temp!=0xffff) && (hum!=0xffff))
  {
	fTemperaturetmp= temp * (160.0/65536.0) - 40.0;
	fHumiditytmp= hum  * (100.0/65536.0);
	printf("%.3f,%.3f\n",  fTemperaturetmp, fHumiditytmp);
  }
  
	return(0);
}


unsigned short i2c_read(unsigned char addr,
                        unsigned char reg,
                        int delay)
{
  static struct i2c_msg msgs[1];
  int r;

  struct i2c_rdwr_ioctl_data msgset =
  {
    msgs, sizeof(msgs) / sizeof(*msgs)
  };
  unsigned char buf[4];

  buf[0] = reg;
  msgs[0].addr = addr;
  msgs[0].flags = 0;
  msgs[0].buf =  (void *)buf;
  msgs[0].len = 1;

  r = ioctl(fd, I2C_RDWR, &msgset);
  if (r<0) return 0xffff;

  if (delay) usleep(delay);

  msgs[0].addr = addr;
  msgs[0].flags = I2C_M_RD;
  msgs[0].buf = (void *)buf;
  msgs[0].len = 2;

  r = ioctl(fd, I2C_RDWR, &msgset);
  if (r<0) return 0xffff;

  return buf[0]*256 + buf[1];
}










