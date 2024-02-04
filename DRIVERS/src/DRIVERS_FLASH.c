/**
 * @file DRIVERS_FLASH.c
 * @brief Contains the API that will deal with the built-in FLASH.
 * @version 1
 * @date 26 Dec 2023
 * @author Grupo 6
 */


#include "flash.h"
#include "DRIVERS_FLASH.h"



unsigned int DRIVERS_FLASH_BlankCheck (unsigned int sector ){

	return FLASH_BlankCheck(sector);

}

unsigned int DRIVERS_FLASH_PrepareSector (unsigned int sector ) {

	return FLASH_PrepareSector(sector);
}

unsigned int DRIVERS_FLASH_EraseSector (unsigned int sector ) {

	return FLASH_EraseSector(sector);
}

unsigned int DRIVERS_FLASH_WriteData(void *dstAddr , void *srcAddr , unsigned int size ) {

	return FLASH_WriteData(dstAddr , srcAddr , size );
}

unsigned int DRIVERS_FLASH_VerifyData(void *dstAddr , void *srcAddr , unsigned int size ) {

	return FLASH_VerifyData(dstAddr , srcAddr , size );
}
