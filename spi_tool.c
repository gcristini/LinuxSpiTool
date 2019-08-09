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
	u8*		dataToWrite;		//Data To Write
	u64		dataToRead;			//Data To Read (is not an input argument)
	u8* 	numOfBytesToWrite;	//Number of bytes to write
	u8*	 	numOfBytesToRead;	//Number of bytes to read
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
void showUsage(void)
{
	printf("\n*** Show Usage: ***\n");
	printf("spi_tool <device> [w | r] <data to write> <n. of bytes to write> <n.of bytes to read>\n");
	printf("--Example:\n");
	printf("-Write:\t spi_tool w 0x55 1\n");
	printf("-Read:\t spi_tool r 0x55 1 2\n");

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
	u8 						nBytes;

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
			st_spiStruct.spiDevice 				= (u8*)		argv[1];
			st_spiStruct.rwOp					= (u8*)		argv[2];
			st_spiStruct.dataToWrite			= (u8*)		argv[3];
			st_spiStruct.dataToRead				= (u64)		0u;
			st_spiStruct.numOfBytesToWrite		= (u8*) 	argv[4];

			/* Variables Initialization */
			st_spiIocSetting.write_bitsPerWord 	= (u8)		(atoi(st_spiStruct.numOfBytesToWrite)*8u);
			st_spiIocSetting.write_mode			= (u8)		0u;
			st_spiIocSetting.write_maxSpeedHz	= (u32)		SPI_SPEED_1MHZ;
			st_spiIocSetting.write_littleEndian = (u8)		0u;
			
			/* If SPI read... */
			if (!strcmp((const char *)st_spiStruct.rwOp , "r"))
			{
				st_spiStruct.numOfBytesToRead 		= (u8*)	argv[5];
				st_spiIocSetting.read_bitsPerWord 	= (u8)	(atoi(st_spiStruct.numOfBytesToRead) * 8);
				st_spiIocSetting.read_mode			= (u8)	0u;
				st_spiIocSetting.read_maxSpeedHz	= (u32)	SPI_SPEED_1MHZ;
				st_spiIocSetting.read_littleEndian 	= (u8)	0u;

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
			nBytes = spi_write(s32_spiFile, st_spiStruct.dataToWrite, st_spiStruct.numOfBytesToWrite);

			printf("--> Written %s (%d bytes) on bus %s\n", st_spiStruct.dataToWrite, nBytes, st_spiStruct.spiDevice);

			/* Go to spi close state */
			en_spi_operation = SPI_CLOSE;

			break;

		case SPI_READ:

			/* SPI Read */
			nBytes = (u8)spi_read(s32_spiFile, st_spiStruct.dataToWrite, st_spiStruct.numOfBytesToWrite, &st_spiStruct.dataToRead, st_spiStruct.numOfBytesToRead);			
			
			if (st_spiStruct.dataToRead == 0u)
			{
				printf("--> No data read on %s\n", st_spiStruct.spiDevice);
			}
			else 
			{
				printf("--> Read 0x%x (%d bytes) on bus %s\n", st_spiStruct.dataToRead, nBytes, st_spiStruct.spiDevice);
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
