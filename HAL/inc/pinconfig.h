/**
 * @file   pinconfig.h
 * @brief Contains the API that will make the configuration of pins
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */

#ifndef PINCONFIG_H_
#define PINCONFIG_H_





#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

/**
 * @addtogroup HAL
* @brief This package provides hardware abstraction layer functions.
* @{
 */

/** @defgroup PINCONFIG PINCONFIG
* @brief Provides the core capabilities for Pin configurations.
* @{
* */
#include "pin.h"

#define LPC_PINSEL_NUM_PINS 16 //cada PINSEL controla 16 pinos, isto é porque cada pino ocupa 2 bits de 32 bits do registo
//Modos de ligação dos pinos
#define THIRD_MODE 3
#define SECOND_MODE 2
#define FIRST_MODE 1
#define GPIO_MODE 0
/**
 * @brief Selects and sets the mode of the pin which its Id was given
 * @param id: Pin which is to be selected and set a given mode
 * @param mode: mode to be set to the given pin
 */
void PIN_settype (PinID_typedef id, int mode);

/**
 * @}
 */
/**
 * @}
 */

#endif /* PINCONFIG_H_ */
