/**
 * @file LED.h
 * @brief Contains the API to work with the in-built LED
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */

#ifndef LED_H_
#define LED_H_




#include <stdbool.h>

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

/**
 * @addtogroup DRIVERS
* @brief This package provides driver functions.
* @{
 */

/** @defgroup LED LED
* @brief Provides the core capabilities for the built-in LED.
* @{
* */

#define LED_PIN 22
#define LED_PORT 0
#define LED_MODE_ON 3
#define LED_DIR 1

/**
 * @brief Initializes the pin of the built-in LED as output
 * and defines the initial state of the LED as given by the parameter
 * @param state: state has the initial state of the built-in LED
 */
void LED_Init ( bool state );

/**
 * @brief Reads the state of the built-in LED and returns its logical value
 * @param : Does not have entry parameters
 * @return the current state of the built-in LED
 */
bool LED_GetState ( void ) ;

/**
 * @brief Turns on the built-in LED
 * @param : Does not have entry parameters
 */
void LED_On ( void ) ;

/**
 * @brief Turns off the built-in LED
 * @param : Does not have entry parameters
 */
void LED_Off ( void ) ;

/**
 * @brief Inverts the state of the built-in LED
 * @param : Does not have entry parameters
 */
void LED_Toggle ( void ) ;

/**
 * @}
 */
/**
 * @}
 */

#endif /* LED_H_ */
