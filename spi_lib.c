/*
 * spi_lib.c
 *
 *  Created on: Jul 23, 2019
 *      Author: gcristini
 */


/* **********************************************************************/
/* ***                 Other components included                      ***/
/* **********************************************************************/
#include "spi_lib.h"

/* **********************************************************************/
/* ***                Definition of local macros                      ***/
/* **********************************************************************/

/* **********************************************************************/
/* ***                Definition of local types                      ***/
/* **********************************************************************/

/* **********************************************************************/
/* ***                     Local variables                            ***/
/* **********************************************************************/


/* **********************************************************************/
/* ***              Declaration of local function                      ***/
/* **********************************************************************/


/* ********************************************************************************/
/* ***                     Declaration of global functions                      ***/
/* ********************************************************************************/

/* *********************************************************************************/ /**
    \fn      s32	spi_init(u8* spiDevice, ST_SPI_IOC_SETTING_TYPE* st_spiIocSetting)
    \brief
    \Scope:  Global
    \par
    \return  s32 (signed int)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:July 26.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s32	spi_init(u8* spiDevice, ST_SPI_IOC_SETTING_TYPE* st_spiIocSetting)
{
	s32 s32_spiFile;


	if ((s32_spiFile = open((const char*)spiDevice, O_RDWR)) < 0)
	{
		printf("Failed to open the bus.");

		exit(1);
	}

	/* Checks */
	/* Possible modes:
	 * 					mode |= SPI_LOOP;
	 * 					mode |= SPI_CPHA;
	 * 					mode |= SPI_CPOL;
	 * 					mode |= SPI_LSB_FIRST;
	 * 					mode |= SPI_CS_HIGH;
	 * 					mode |= SPI_3WIRE;
	 * 					mode |= SPI_NO_CS;
	 * 					mode |= SPI_READY;
	 *
	 * multiple possibilities using | */

	if (ioctl(s32_spiFile, SPI_IOC_WR_MODE, &st_spiIocSetting->write_mode) < 0)
	{
		perror("Can't set spi mode");
		return -1;
	}

	if (ioctl(s32_spiFile, SPI_IOC_RD_MODE, &st_spiIocSetting->read_mode) < 0)
	{
		perror("SPI rd_mode");
		return -1;
	}

	if (ioctl(s32_spiFile, SPI_IOC_WR_LSB_FIRST, &st_spiIocSetting->write_littleEndian) < 0)
	{
		perror("SPI rd_lsb_fist");
		return -1;
	}

	if (ioctl(s32_spiFile, SPI_IOC_RD_LSB_FIRST, &st_spiIocSetting->read_littleEndian) < 0)
	{
		perror("SPI rd_lsb_fist");
		return -1;
	}

	if (ioctl(s32_spiFile, SPI_IOC_WR_BITS_PER_WORD, &st_spiIocSetting->write_bitsPerWord) < 0)
	{
		perror("Can't set bits per word");
		return -1;
	}

	if (ioctl(s32_spiFile, SPI_IOC_RD_BITS_PER_WORD, &st_spiIocSetting->read_bitsPerWord) < 0)
	{
		perror("SPI bits_per_word");
		return -1;
	}

	if (ioctl(s32_spiFile, SPI_IOC_WR_MAX_SPEED_HZ, &st_spiIocSetting->write_maxSpeedHz) < 0)
	{
		perror("Can't set max speed hz");
		return -1;
	}

	if (ioctl(s32_spiFile, SPI_IOC_RD_MAX_SPEED_HZ, &st_spiIocSetting->read_maxSpeedHz) < 0)
	{
		perror("SPI max_speed_hz");
		return -1;
	}

	printf(	"\n*** Settings for SPI device: %s ***\n" 																				\
			"-Write:\t mode %d,\t speed %dHz,\t %d bits per word,\t %s\n" 															\
			"-Read:\t mode %d,\t speed %dHz,\t %d bits per word,\t %s\n", 															\
			spiDevice, 																												\
			st_spiIocSetting->write_mode, st_spiIocSetting->write_maxSpeedHz,														\
			st_spiIocSetting->write_bitsPerWord, st_spiIocSetting->write_littleEndian ? "Little Endian" : "Big Endian", 			\
					st_spiIocSetting->read_mode, st_spiIocSetting->read_maxSpeedHz,													\
					st_spiIocSetting->read_bitsPerWord, st_spiIocSetting->write_littleEndian ? "Little Endian" : "Big Endian\n"		);


	return s32_spiFile;
}

/* *********************************************************************************/ /**
    \fn      ssize_t spi_write(s32 s32_spiFile, u8 *dataToWrite, u8 *numOfBytesToWrite)
    \brief
    \Scope:  Global
    \par
    \return  void
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on: July 26.19
            \arg Last Edit:
 */ /* **********************************************************************************/
ssize_t spi_write(s32 s32_spiFile, u64 *dataToWrite, u8 *numOfBytesToWrite)
{
	ssize_t writeResult;

	/* Write on SPI Bus */	
	writeResult = write(s32_spiFile, dataToWrite, *numOfBytesToWrite);

	if (writeResult == -1)
	{
		perror("Write Error");
	}
	else
	{
		/* Misra */
	}

	return writeResult;
}

/* *********************************************************************************/ /**
    \fn      ssize_t spi_read(s32 s32_spiFile, u8 *dataToWrite, u8 *numOfBytesToWrite, u64* dataToRead, u8* numOfBytesToRead)
    \brief
    \Scope:  Global
    \par
    \return  void
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on: July 26.19
            \arg Last Edit:	Aug 08.19
 */ /* **********************************************************************************/
ssize_t spi_read(s32 s32_spiFile, u64 *dataToWrite, u8 *numOfBytesToWrite, u64* dataToRead, u8* numOfBytesToRead)
{
	ssize_t opResult;
		
	/* Convert data from string to decimal */
	//u8  u8_numOfBytesToRead = (u8)strtol((const char*)numOfBytesToRead, NULL, 10);

	/* Write on SPI Bus */
	opResult = spi_write(s32_spiFile, dataToWrite, numOfBytesToWrite);

	if (opResult == -1)
	{
		perror("Write Error");
	}
	else
	{
		/* Read on SPI Bus */				
		opResult = read(s32_spiFile, dataToRead, *numOfBytesToRead);
		
		if (opResult == -1)
		{
			perror("Read Error");
		}
		else
		{			
			/* Misra */
		}		
	}
	
	return opResult;
}

/* *********************************************************************************/ /**
    \fn      void spi_close(s32 s32_spiFile)
    \brief
    \Scope:  Global
    \par
    \return  void
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on: July 26.19
            \arg Last Edit:
 */ /* **********************************************************************************/
void spi_close(s32 s32_spiFile)
{
	/* Close SPI */
	close(s32_spiFile);


	return;
}
