/**
 * @file   flash.h
 * @brief Contains the API that will deal with non volatile memory (Flash)
 * @version 1
 * @date 22 Nov 2023
 * @author Grupo 6
 */

#ifndef FLASH_H_
#define FLASH_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


/**
 * @addtogroup HAL
* @brief This package provides hardware abstraction layer functions.
* @{
 */

/** @defgroup FLASH FLASH
* @brief Provides the core capabilities for the non volatile memory (Flash).
* @{
* */
#include <stdint.h>
#include <stddef.h>

#define SECTORblw16 4096
#define SECTORabv16 32768

/*typedef void (*IAP)(uint32_t [], uint32_t[]);
extern IAP iap_routine_entry;
//IAP iap_routine_entry = (IAP)0x1FFF1FF1;*/
#define IAP_CMD_SIZE 5

static volatile uint32_t iap_cmd[IAP_CMD_SIZE];
static volatile uint32_t iap_result[IAP_CMD_SIZE];

// comandos IAP
#define	IAP_CMD_PREPARE_SECTORS			50
#define	IAP_CMD_COPY_RAM_TO_FLASH		51
#define	IAP_CMD_ERASE_SECTORS			52
#define	IAP_CMD_BLANK_CHECK_SECTORS		53
#define	IAP_CMD_READ_PART_ID			54
#define	IAP_CMD_READ_BOOT_ROM_VERSION	55
#define	IAP_CMD_COMPARE				    56
#define	IAP_CMD_REINVOKE_ISP			57
#define IAP_CMD_READ_SERIAL_NUMBER		58

enum error_code {
    CMD_SUCCESS,
    INVALID_COMMAND,
    SRC_ADDR_ERROR,
    DST_ADDR_ERROR,
    SRC_ADDR_NOT_MAPPED,
    DST_ADDR_NOT_MAPPED,
    COUNT_ERROR,
    INVALID_SECTOR,
    SECTOR_NOT_BLANK,
    SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
    COMPARE_ERROR,
    BUSY,
    PARAM_ERROR,
    ADDR_ERROR,
    ADDR_NOT_MAPPED,
    CMD_LOCKED,
    INVALID_CODE,
    INVALID_BAUD_RATE,
    INVALID_STOP_BIT,
    CODE_READ_PROTECTION_ENABLED
};


/**
 * @addtogroup HAL
* @brief This package provides hardware abstraction layer functions.
* @{
 */

/** @defgroup FLASH FLASH
* @brief Provides the core capabilities for the non volatile memory built-in flash.
* @{
* */

/**
 * @brief Calls the IAP routine that is already stored in a given address of memory.
 * @param : Does not have entry parameters
 */

void call_iap();

/**
 * @brief Runs the IAP routine with BlankCheck command (checks if the sector is blank)
 * @param sector: Sector in which you wish to run the BlankCheck command
 * @return the error code that the IAP routine gave
 */

unsigned int FLASH_BlankCheck (unsigned int sector );

/**
 * @brief Runs the IAP routine with PrepareSector command (prepares the sector for write operations)
 * @param sector: Sector in which you wish to run the PrepareSector command
 * @return the error code that the IAP routine gave
 * @note this function must be run before any write operations in the flash
 */

unsigned int FLASH_PrepareSector (unsigned int sector );

/**
 * @brief Runs the IAP routine with EraseSector command (erases the sector)
 * @param sector: Sector in which you wish to run the EraseSector command
 * @return the error code that the IAP routine gave
 */

unsigned int FLASH_EraseSector (unsigned int sector ) ;

/**
 * @brief Runs the IAP routine with WriteData command (writes what you want where you want)
 * @param *dstAddr: Address of the destination where I wish to write
 * @param *srcAddr: Address of the source of what I wish to write
 * @param size: Size of what I wish to write
 * @return the error code that the IAP routine gave
 */

unsigned int FLASH_WriteData(void *dstAddr , void *srcAddr , unsigned int size ) ;

/**
 * @brief Reads the state of the built-in LED and returns its logical value
 * @param *dstAddr: Address of the destination where I wish to write
 * @param *srcAddr: Address of the source of what I wish to write
 * @param size: Size of what I wish to write
 * @return the error code that the IAP routine gave
 */

unsigned int FLASH_VerifyData(void *dstAddr , void *srcAddr , unsigned int size ) ;


//unsigned int calculate_padded_size(unsigned int size);



//void FLASH_padder(void *inputStruct, size_t structSize);

/**
 * @}
 */
/**
 * @}
 */
#endif /* FLASH_H_ */
