/**
 * @file   SYSTICK.h
 * @brief Contains the SYSTICK API
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#ifndef SYSTICK_H_
#define SYSTICK_H_


/**
 * @addtogroup HAL
* @brief This package provides hardware abstraction layer functions.
* @{
 */

/** @defgroup SYSTICK SYSTICK
* @brief Provides the core capabilities for system timer functions.
* @{
* */

/**
* @brief Interruption Handler for SYSTICK
* @param : Does not have parameters of entry
*/
void SysTick_Handler(void);
/**
* @brief Initialises the systick API for 1 ms resolution.
* @param value: receices the value in ms of time to count
* @return 0 if initialisation successed; -1 if fails.
* @note This function must be called prior to any other SYSTICK
* functions, and use the SYSTICK resource.
*/

int SYSTICK_Init(uint32_t value);
/**
* @brief Get current value of ticks
* @return Returns the current tick value in milliseconds.
*/
uint32_t SYSTICK_GetValue(void);


/**
 * @}
 */
/**
 * @}
 */

#endif /* SYSTICK_H_ */
