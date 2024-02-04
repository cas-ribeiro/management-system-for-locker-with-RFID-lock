/**
 * @file DRIVERS_FLASH.h
 * @brief Contains the API that will deal with the built-in FLASH.
 * @version 1
 * @date 26 Dec 2023
 * @author Grupo 6
 */

#ifndef DRIVERS_FLASH_H_
#define DRIVERS_FLASH_H_




/**
* @addtogroup DRIVERS
* @brief This package provides driver functions.
* @{
 */

/** @defgroup FLASH_DRIVERS FLASH_DRIVERS
* @brief Provides the core capabilities for the built-in FLASH.
* @{
* */




/**
 * @brief Runs the IAP routine with BlankCheck command (checks if the sector is blank)
 * @param sector: Sector in which you wish to run the BlankCheck command
 * @return the error code that the IAP routine gave
 * @note all of this is done by calling the function in flash.h of the HAL
 */
unsigned int DRIVERS_FLASH_BlankCheck (unsigned int sector );

/**
 * @brief Runs the IAP routine with PrepareSector command (prepares the sector for write operations)
 * @param sector: Sector in which you wish to run the PrepareSector command
 * @return the error code that the IAP routine gave
 * @note this function must be run before any write operations in the flash
 */

unsigned int DRIVERS_FLASH_PrepareSector (unsigned int sector );

/**
 * @brief Runs the IAP routine with EraseSector command (erases the sector)
 * @param sector: Sector in which you wish to run the EraseSector command
 * @return the error code that the IAP routine gave
 * @note all of this is done by calling the function in flash.h of the HAL
 */
unsigned int DRIVERS_FLASH_EraseSector (unsigned int sector ) ;

/**
 * @brief Runs the IAP routine with WriteData command (writes what you want where you want)
 * @param *dstAddr: Address of the destination where I wish to write
 * @param *srcAddr: Address of the source of what I wish to write
 * @param size: Size of what I wish to write
 * @return the error code that the IAP routine gave
 * @note all of this is done by calling the function in flash.h of the HAL
 */
unsigned int DRIVERS_FLASH_WriteData(void *dstAddr , void *srcAddr , unsigned int size ) ;

/**
 * @brief Reads the state of the built-in LED and returns its logical value
 * @param *dstAddr: Address of the destination where I wish to write
 * @param *srcAddr: Address of the source of what I wish to write
 * @param size: Size of what I wish to write
 * @return the error code that the IAP routine gave
 * @note all of this is done by calling the function in flash.h of the HAL
 */
unsigned int DRIVERS_FLASH_VerifyData(void *dstAddr , void *srcAddr , unsigned int size ) ;

/**
 * @}
 */
/**
 * @}
 */

#endif /* DRIVERS_FLASH_H_ */
