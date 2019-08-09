/*
 * SVN File Revision
 * $Rev:: 1946          $:  Revision of last commit
 * $Author:: Montuschi  $:  Author of last commit
 * $Date:: 2017-20-09#  $:  Date of last commit
 */

/* **********************************************************************/ /**
 \file   HallSensor.h
 \brief  This file contains hall sensor functions\n
 \date
   \arg  Created on: October 20.17 \n
   \arg
 \author
   \arg  Gabriele Montuschi \n
   \arg
 */ /* ***********************************************************************/
#ifndef SPI_LIB_H_
#define SPI_LIB_H_

/* **********************************************************************/
/* ***              System and library files included                 ***/
/* **********************************************************************/
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>

/* **********************************************************************/
/* ***                Definition of global macros                     ***/
/* **********************************************************************/
#define SPI_SPEED_10KHZ	10000u
#define SPI_SPEED_1MHZ 	1000000u

/* **********************************************************************/
/* ***                Definition of global types                      ***/
/* **********************************************************************/
/* Wrap assembly definition of data types */
/* Char (8 bits) */
typedef __u8 	u8;
typedef __s8	s8;

/* Short (16 bits) */
typedef __u16 	u16;
typedef __s16 	s16;

/* Int (32 bits) */
typedef __u32	u32;
typedef __s32	s32;

/* Long long (64 bits) */
typedef __u64	u64;
typedef __s64	s64;

typedef struct
{
	u8 	write_mode;
	u8 	read_mode;
	u8 	write_littleEndian;
	u8 	read_littleEndian;
	u8 	write_bitsPerWord;
	u8 	read_bitsPerWord;
	u32 write_maxSpeedHz;
	u32 read_maxSpeedHz;
}ST_SPI_IOC_SETTING_TYPE;


/* **********************************************************************/
/* ***            Declaration of global functions                     ***/
/* **********************************************************************/
s32 	spi_init(u8* spiDevice, ST_SPI_IOC_SETTING_TYPE* st_spiIocSetting);
ssize_t spi_write(s32 s32_spiFile, u64 *dataToWrite, u8 *numOfBytesToWrite);
ssize_t spi_read(s32 s32_spiFile, u64 *dataToWrite, u8 *numOfBytesToWrite, u64* dataToRead, u8* numOfBytesToRead);
void	spi_close(s32 s32_spiFile);


#endif /* SPI_LIB_H_ */
