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
/* ***              Definition of local function                      ***/
/* **********************************************************************/

s8 spiSetMode			(s32 s32_spiFile, u8 u8_spiMode);
s8 spiGetMode			(s32 s32_spiFile, u8 u8_spiMode);
s8 spiSetEndiannes		(s32 s32_spiFile, u8 u8_endianness);
s8 spiGetEndiannes		(s32 s32_spiFile, u8 u8_endianness);	
s8 spiSetBitsPerWord	(s32 s32_spiFile, u16 u16_bitsPerWords);
s8 spiGetBitsPerWord	(s32 s32_spiFile, u16 u16_bitsPerWords);
s8 spiSetMaxSpeed		(s32 s32_spiFile, u32 u32_maxSpeed);
s8 spiGetMaxSpeed		(s32 s32_spiFile, u32 u32_maxSpeed);

/* **********************************************************************/
/* ***              Declaration of local function                     ***/
/* **********************************************************************/
/* *********************************************************************************/ /**
    \fn      s8 spiSetMode(s32 s32_spiFile, u8 u8_spiMode)
    \brief
    \Scope:  Local
    \par
    \return  s8 (signed char)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:Aug 09.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s8 spiSetMode(s32 s32_spiFile, u8 u8_spiMode)
{
	s8 s8_ret;

	/* Set Mode */
	s8_ret = (s8)ioctl(s32_spiFile, SPI_IOC_WR_MODE, &u8_spiMode);

	return s8_ret;
}

/* *********************************************************************************/ /**
    \fn      s8 spiGetMode(s32 s32_spiFile, u8 u8_spiMode)
    \brief
    \Scope:  Local
    \par
    \return  s8 (signed char)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:Aug 09.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s8 spiGetMode(s32 s32_spiFile, u8 u8_spiMode)
{
	s8 s8_ret;

	/* Get Mode */
	s8_ret = (s8)ioctl(s32_spiFile, SPI_IOC_RD_MODE, &u8_spiMode);

	return s8_ret;
}

/* *********************************************************************************/ /**
    \fn      s8 spiSetEndiannes(s32 s32_spiFile, u8 u8_endianness)	
    \brief
    \Scope:  Local
    \par
    \return  s8 (signed char)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:Aug 09.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s8 spiSetEndiannes(s32 s32_spiFile, u8 u8_endianness)
{
	s8 s8_ret;

	s8_ret = (s8)ioctl(s32_spiFile, SPI_IOC_WR_LSB_FIRST, &u8_endianness) ;
	
	return s8_ret;	
}

/* *********************************************************************************/ /**
    \fn      s8 spiGetEndiannes(s32 s32_spiFile, u8 u8_endianness)
    \brief
    \Scope:  Local
    \par
    \return  s8 (signed char)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:Aug 09.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s8 spiGetEndiannes(s32 s32_spiFile, u8 u8_endianness)
{
	s8 s8_ret;

	s8_ret = (s8)ioctl(s32_spiFile, SPI_IOC_RD_LSB_FIRST, &u8_endianness);
	
	return s8_ret;	
}

/* *********************************************************************************/ /**
    \fn      s8 spiSetBitsPerWord(s32 s32_spiFile, u16 u16_bitsPerWords)
    \brief
    \Scope:  Local
    \par
    \return  s8 (signed char)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:Aug 09.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s8 spiSetBitsPerWord(s32 s32_spiFile, u16 u16_bitsPerWords)
{
	s8 s8_ret;

	ioctl(s32_spiFile, SPI_IOC_WR_BITS_PER_WORD, &u16_bitsPerWords);

	return s8_ret;
}

/* *********************************************************************************/ /**
    \fn      s8 spiGetBitsPerWord(s32 s32_spiFile, u16 u16_bitsPerWords)
    \brief
    \Scope:  Local
    \par
    \return  s8 (signed char)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:Aug 09.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s8 spiGetBitsPerWord(s32 s32_spiFile, u16 u16_bitsPerWords)
{
	s8 s8_ret;

	ioctl(s32_spiFile, SPI_IOC_RD_BITS_PER_WORD, &u16_bitsPerWords);

	return s8_ret;
}

/* *********************************************************************************/ /**
    \fn      s8 spiSetMaxSpeed(s32 s32_spiFile, u32 u32_maxSpeed)
    \brief
    \Scope:  Local
    \par
    \return  s8 (signed char)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:Aug 09.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s8 spiSetMaxSpeed(s32 s32_spiFile, u32 u32_maxSpeed)
{
	s8 s8_ret;

	ioctl(s32_spiFile, SPI_IOC_WR_MAX_SPEED_HZ, &u32_maxSpeed);

	return s8_ret;
}

/* *********************************************************************************/ /**
    \fn      s8 spiGetMaxSpeed(s32 s32_spiFile, u32 u32_maxSpeed)
    \brief
    \Scope:  Local
    \par
    \return  s8 (signed char)
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on:Aug 09.19
            \arg Last Edit:
 */ /* **********************************************************************************/
s8 spiGetMaxSpeed(s32 s32_spiFile, u32 u32_maxSpeed)
{
	s8 s8_ret;

	ioctl(s32_spiFile, SPI_IOC_WR_MAX_SPEED_HZ, &u32_maxSpeed);

	return s8_ret;
}


/* ********************************************************************************/
/* ***                     Declaration of global functions                      ***/
/* ********************************************************************************/

/* *********************************************************************************/ /**
    \fn      s32 spi_init(u8* spiDevice, ST_SPI_IOC_SETTING_TYPE* st_spiIocSetting)
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

	if (spiSetMode(s32_spiFile, st_spiIocSetting->spiMode) < 0)
	{
		perror("Can't set spi mode");
		return -1;
	}

	if (spiGetMode(s32_spiFile, st_spiIocSetting->spiMode) < 0)
	{
		perror("Can't get spi mode");
		return -1;
	}

	if (spiSetEndiannes(s32_spiFile, st_spiIocSetting->spiEndianness) < 0)
	{
		perror("Can't set endianness");
		return -1;
	}

	if (spiGetEndiannes(s32_spiFile, st_spiIocSetting->spiEndianness) < 0)
	{
		perror("Can't get endianness");
		return -1;
	}

	/* Use WriteBitsPerWord as default value: it will changed into write and read functions */
	if (spiSetBitsPerWord(s32_spiFile, st_spiIocSetting->spiWriteBitsPerWord) < 0)
	{
		
		perror("Can't set bits per word");
		return -1;
	}

	if (spiGetBitsPerWord(s32_spiFile, st_spiIocSetting->spiWriteBitsPerWord) < 0)
	{
		perror("Can't get write bits per word");
		return -1;
	}

	if (spiSetMaxSpeed(s32_spiFile, st_spiIocSetting->spiMaxSpeedHz) < 0)
	{
		perror("Can't set max speed hz");
		return -1;
	}

	if (spiGetMaxSpeed(s32_spiFile, st_spiIocSetting->spiMaxSpeedHz) < 0)
	{
		perror("Can't get max speed hz");
		return -1;
	}

	printf(	"\n*** Settings for SPI device: %s ***\n" 																				\
			"-Write:\t mode %d,\t speed %dHz,\t %d bits per word,\t %s\n" 															\
			"-Read:\t mode %d,\t speed %dHz,\t %d bits per word,\t %s\n", 															\
			spiDevice, 																												\
			st_spiIocSetting->spiMode, st_spiIocSetting->spiMaxSpeedHz,																\
			st_spiIocSetting->spiWriteBitsPerWord, st_spiIocSetting->spiEndianness ? "Little Endian" : "Big Endian", 				\
					st_spiIocSetting->spiMode, st_spiIocSetting->spiMaxSpeedHz,														\
					st_spiIocSetting->spiReadBitsPerWord, st_spiIocSetting->spiEndianness ? "Little Endian" : "Big Endian\n"		);


	return s32_spiFile;
}

/* *********************************************************************************/ /**
    \fn      ssize_t spi_write(s32 s32_spiFile, u64 *dataToWrite, u8 *numOfBytesToWrite, u16 bitsPerWord)
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
ssize_t spi_write(s32 s32_spiFile, u64 *dataToWrite, u8 *numOfBytesToWrite, u16 bitsPerWord)
{
	ssize_t writeResult;

	/* Set bits per words */
	spiSetBitsPerWord(s32_spiFile, bitsPerWord);

	/* Write on SPI Bus */	
	writeResult = write(s32_spiFile, dataToWrite, *numOfBytesToWrite);
	
	if (writeResult == -1)
	{
		perror("Write Error");
	}
	else
	{
		*numOfBytesToWrite = writeResult;
	}

	return writeResult;
}

/* *********************************************************************************/ /**
    \fn      ssize_t spi_read(s32 s32_spiFile, u64 *dataToWrite, u8 *numOfBytesToWrite, u64* dataToRead, u8* numOfBytesToRead, u16 bitsPerWord)
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
ssize_t spi_read(s32 s32_spiFile, u64 *dataToWrite, u8 *numOfBytesToWrite, u64* dataToRead, u8* numOfBytesToRead, u16 bitsPerWord)
{
	ssize_t opResult;
		
	/* Write on SPI Bus */
	opResult = spi_write(s32_spiFile, dataToWrite, numOfBytesToWrite, bitsPerWord);

	if (opResult == -1)
	{
		perror("Write Error");
	}
	else
	{
		/* Set bits per Words */		
		spiSetBitsPerWord(s32_spiFile, bitsPerWord);	

		/* Read on SPI Bus */
		opResult = read(s32_spiFile, dataToRead, *numOfBytesToRead);
		
		if (opResult == -1)
		{
			perror("Read Error");
		}
		else
		{
			*numOfBytesToRead = opResult;
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
