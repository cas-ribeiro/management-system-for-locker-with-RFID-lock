/**
* @file   spi.h
 * @brief Contains the API that will deal with the SPI
 * @version 1
 * @date 29 Nov 2023
 * @author Grupo 6
 */

#ifndef SPI_H_
#define SPI_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>

/* PINOS SPI USADOS
 * MOSI |P0.18
 * MISO | P0.17
 * SCK  | P0.15
 * SS   | P0.16
 * RST  | P0.0
 */

#define MOSI_PIN 18
#define MISO_PIN 17
#define SCK_PIN 15
#define SS_PIN 16
#define RST_PIN 0

#define PCSPI 8 //pagina 65
#define PCLK_SPI 16 //pagina 58
#define SPIF 7
#define BitEnable 2
#define BITS 8
#define MSTR 5
#define CPHA 3

/**
 * @addtogroup HAL
* @brief This package provides hardware abstraction layer functions.
* @{
 */

/** @defgroup SPI SPI
* @brief Provides the core capabilities for the SPI.
* @{
* */

/**
 * @brief Initializes the SPI
 * @param : Does not have entry parameters
 * @note This function must be called prior to any other SPI function
 */

void SPI_Init ( void);

/**
 * @brief Configures the SPI according to the entry parameters
 * @param bitData : Number of bits given
 * @param frequency : Rhythm of reception and transmission
 * @param mode : Mode of Operation
 */

void SPI_ConfigTransfer(int bitData, int frequency , int mode);

/**
 * @brief Transfers a word and receives a word
 * @param value: The word to be sent
 * @return the word received
 */

unsigned short SPI_Transfer(unsigned short value ) ;




/**
 * @}
 */
/**
 * @}
 */
#endif /* SPI_H_ */
