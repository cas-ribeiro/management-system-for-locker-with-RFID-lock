/**
 * @file DELAY.h
 * @brief Contains the API that will deal with the various clocks and timer functionalities
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */

#ifndef DELAY_H_
#define DELAY_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

/**
 * @defgroup DRIVERS DRIVERS
* @brief This package provides driver functions.
* @{
 */

/** @defgroup DELAY DELAY
* @brief Provides the core capabilities for time functionalities.
* @{
* */

/**
 * @brief Initializes the SYSTICK counter using the SYSTICK API
 * @param : Does not have entry parameters
 * @note This function must be called prior to DELAY_Milliseconds and DELAY_GetElapsedMillis functions
 */
int DELAY_Init(void);
/**
 * @brief Utilizes the SYSTICK API to count a given number of ms given by the user
 * @param  millis : number of milliseconds to count
 */
void DELAY_Milliseconds(uint32_t millis);
/**
 * @brief Utilizes the SYSTICK API to find out the difference between the current counter of ms and the start parameter
 * @param  start : number used to compare with the current timer
 */
uint32_t DELAY_GetElapsedMillis(uint32_t start);

/**
 * @brief Initializes the TIMER0 counter using the timer API
 * @param : Does not have entry parameters
 * @note This function must be called prior to DELAY_Stopwatch function
 */
void DELAY_StopwatchInit ( void );
/**
 * @brief Utilizes TIMER0 to count a given number of microseconds given by the user
 * @param  waitUs : number of microseconds to wait
 */
void DELAY_Stopwatch ( uint32_t waitUs );

/**
 * @}
 */
/**
 * @}
 */

#endif /* DELAY_H_ */
