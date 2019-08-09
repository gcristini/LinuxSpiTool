/*
 *  SVN File Revision
 *  $Rev:: 7864                                                               	$:  Revision of last commit
 *  $Author:: Cristini                                                          $:  Author of last commit
 *  $Date:: 										                     	 	$:  Date of last commit
 */

/* *********************************************************************************/ /**
    \file   spi_tool.c
    \brief  .\n
    \date   \arg
    \author Gabriele Cristini
                  \arg \Datalogic
 */ /* **********************************************************************************/



/* **********************************************************************/
/* ***              System and library files included                 ***/
/* **********************************************************************/
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

/* **********************************************************************/
/* ***                 Other components included                      ***/
/* **********************************************************************/
#include "spi_lib.h"


/* **********************************************************************/
/* ***                Definition of local macros                      ***/
/* **********************************************************************/
#define ever (;;) // Enjoy :)

/* **********************************************************************/
/* ***                Definition of local types                      ***/
/* **********************************************************************/
typedef struct
{
	u8*		spiDevice;			//SPI device path
	u8*		rwOp;				//Read/write operation
	u64		dataToWrite;		//Data To Write
	u64		dataToRead;			//Data To Read (is not an input argument)
	u8	 	numOfBytesToWrite;	//Number of bytes to write
	u8	 	numOfBytesToRead;	//Number of bytes to read
}ST_SPI_STRUCT_TYPE;

typedef enum
{
	SPI_NULL		= 0u,
	SPI_CHECK_ARGS	= 1u,
	SPI_INIT		= 2u,
	SPI_WRITE		= 3u,
	SPI_READ		= 4u,
	SPI_CLOSE		= 5u,
	SPI_SHOW_USAGE	= 6u,
	SPI_EXIT		= 7u
}EN_MAIN_OPERATION_TYPE;

/* **********************************************************************/
/* ***                     Local variables                            ***/
/* **********************************************************************/
EN_MAIN_OPERATION_TYPE 	en_spi_operation = 	SPI_NULL;


/* **********************************************************************/
/* ***              Declaration of local function                     ***/
/* **********************************************************************/
/* *********************************************************************************/ /**
    \fn      void showUsage(void)
    \brief
    \Scope:  Local
    \par     void
    \return  void
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on: July 26.19
            \arg Last Edit: Aug 09.19
 */ /* **********************************************************************************/
void showUsage(void)
{
	printf("\n*** Show Usage: ***\n");
	printf("spi_tool <device> [w | r] <data to write> <n. of bytes to write> <n.of bytes to read>\n\n");
	printf("--Rules:\n");
	printf("-The number of bytes to write should be more or less than the number of bytes to read\n");
	printf("-Number of bytes should be even\n\n");
	printf("--Example:\n");
	printf("-Write:\t spi_tool w 0x55 1\n");
	printf("-Read:\t spi_tool r 0x55 2 2\n");

	return;
}


/* *********************************************************************************/ /**
    \fn      int main(int argc, char *argv[])
    \brief
    \Scope:  Global
    \par     argc, *argv[]
    \return  int
    \author
            \arg Gabriele Cristini
    \date
            \arg Created on: July 26.19
            \arg Last Edit:
 */ /* **********************************************************************************/
int main(int argc, char *argv[])
{
	/* Variable Declaration */
	ST_SPI_STRUCT_TYPE 		st_spiStruct;
	s32 					s32_spiFile;
	ST_SPI_IOC_SETTING_TYPE	st_spiIocSetting;
	
	/* Main Program */	
	for ever
	{
		switch (en_spi_operation)
		{
		case SPI_NULL:

			/* Go to check arguments state */
			en_spi_operation = SPI_CHECK_ARGS;

			break;

		case SPI_CHECK_ARGS:

			if (	(argc < 5 || argc > 6)														||
					(strcmp((const char *)argv[2], "r") && strcmp((const char *)argv[2], "w"))	||
					(!strcmp((const char *)argv[1], "--help"))									)
			{
				/* Go to show usage state */
				en_spi_operation = SPI_SHOW_USAGE;
			}
			else
			{
				/* Go to spi init state */
				en_spi_operation = SPI_INIT;
			}

			break;

		case SPI_INIT:

			/* Read Input Parameters */
			st_spiStruct.spiDevice 					= (u8*)		argv[1];
			st_spiStruct.rwOp						= (u8*)		argv[2];			
			st_spiStruct.dataToWrite				= (u64)		strtol((const char*)argv[3], NULL, 16); /* Hex */
			st_spiStruct.dataToRead					= (u64)		0u;
			st_spiStruct.numOfBytesToWrite			= (u8) 		atoi(argv[4]);	/* Dec */
			
			/* Variables Initialization */
			st_spiIocSetting.spiWriteBitsPerWord 	= (u16)		(st_spiStruct.numOfBytesToWrite*8u);			
			st_spiIocSetting.spiMode				= (u8)		0u;
			st_spiIocSetting.spiMaxSpeedHz			= (u32)		SPI_SPEED_1MHZ;
			st_spiIocSetting.spiEndianness			= (u8)		SPI_BIG_ENDIAN;
			
			/* If SPI read... */
			if (!strcmp((const char *)st_spiStruct.rwOp , "r"))
			{
				st_spiStruct.numOfBytesToRead 			= (u8)	atoi(argv[5]); /* Dec */				
				st_spiIocSetting.spiReadBitsPerWord		= (u16)	(st_spiStruct.numOfBytesToRead*8u);

				/* Go to spi read state */
				en_spi_operation = SPI_READ;
			}
			else
			{
				/* Go to spi write state */
				en_spi_operation = SPI_WRITE;
			}

			/* SPI Initialization */
			s32_spiFile = spi_init(st_spiStruct.spiDevice, &st_spiIocSetting);

			break;

		case SPI_WRITE:

			/* SPI Write */
			spi_write(s32_spiFile, &st_spiStruct.dataToWrite, &st_spiStruct.numOfBytesToWrite, st_spiIocSetting.spiWriteBitsPerWord);

			printf("--> Written 0x%x (%d bytes) on bus %s\n", st_spiStruct.dataToWrite, st_spiStruct.numOfBytesToWrite, st_spiStruct.spiDevice);

			/* Go to spi close state */
			en_spi_operation = SPI_CLOSE;

			break;

		case SPI_READ:

			/* SPI Read */
			spi_read(s32_spiFile, &st_spiStruct.dataToWrite, &st_spiStruct.numOfBytesToWrite, &st_spiStruct.dataToRead, &st_spiStruct.numOfBytesToRead, st_spiIocSetting.spiReadBitsPerWord);			
			
			if (st_spiStruct.dataToRead == 0u)
			{
				printf("--> No data read on %s\n", st_spiStruct.spiDevice);
			}
			else 
			{
				printf("--> Read 0x%x (%d bytes) on bus %s\n", st_spiStruct.dataToRead, st_spiStruct.numOfBytesToRead, st_spiStruct.spiDevice);
			}

			/* Go to spi close state */
			en_spi_operation = SPI_CLOSE;

			break;

		case SPI_CLOSE:

			/* SPI closing */
			spi_close(s32_spiFile);

			/* Go to spi exit state */
			en_spi_operation = SPI_EXIT;

			break;

		case SPI_SHOW_USAGE:

			/* Show usage */
			showUsage();

			/* Go to spi exit state */
			en_spi_operation = SPI_EXIT;

			break;

		case SPI_EXIT:

			printf("\n");

			/* Exit from program */
			exit(1);

			break;

		default:
			/* MISRA */
			break;

		}
	}

	return 1;
}
