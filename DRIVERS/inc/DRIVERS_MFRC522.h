/**
 * @file DRIVERS_MFRC522.h
 * @brief contains the basic API to deal with MFRC522 controller, with the help its own library
 * @version 1
 * @date 02 Dec 2023
 * @author Grupo 6
 */

/**
 * @addtogroup DRIVERS
* @brief This package provides driver functions.
* @{
 */

/** @defgroup DRIVERS_MFRC522 DRIVERS_MFRC522
* @brief Provides the core capabilities for the MFRC522 using the in-built SPI.
* @{
* */

#ifndef DRIVERS_MFRC522_H_
#define DRIVERS_MFRC522_H_


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "mfrc522.h"
#include "spi.h"
#include "pin.h"
#include <stdint.h>
#include "DELAY.H"

#define nBits 8
#define Frqncy 500000//up to 10Mbit/s
#define mode 0

#include "DRIVERS_MFRC522.h"
/**
 * @brief Does the needed initializations for the MFRC522.h library
 * @param : Does not have entry parameters
 * @return none
 */
void MFRC522_PreInit(void);

/**
 * @brief Changes the pin of reset according to the value of assert
 * @param assert: value to put in the reset pin
 * @return none
 */
void MFRC522_Reset( bool assert );

/**
 * @brief Changes the select pin according to the value of assert
 * @param assert: value to put in the select pin
 * @return none
 */
void MFRC522_Select( bool assert );

/**
 * @brief Transfers an int of 8 bytes
 * @param value: value to be transferred
 * @return value that is transmited back
 */
uint8_t MFRC522_Transfer( uint8_t value );

/**
 * @brief Waits miliseconds
 * @param millis: milliseconds to be waited
 * @return none
 */
void MFRC522_WaitMs( uint32_t millis );

/**
 * @}
 */
/**
 * @}
 */

#endif /* DRIVERS_MFRC522_H_ */
