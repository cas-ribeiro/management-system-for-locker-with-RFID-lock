/**
 * @file rtcHal.h
 * @brief contains the basic API for the Real Time Clock
 * @version 1
 * @date 7 Nov 2023
 * @author Grupo 6
 */


#ifndef RTCHALL_H
#define RTCHALL_H

/**
 * @addtogroup HAL
* @brief This package provides hardware abstraction layer functions.
* @{
 */

/** @defgroup RTCHAL RTCHAL
* @brief Provides the core capabilities for the built-in RTC.
* @{
* */

#include <time.h>
#define SBIT_CTCRST 1
#define SBIT_CCALEN 4
#define SBIT_CLKEN 0
#define PCRTC 9		//página 65

/**
 * @brief Starts the in-built RTC.
 * @param: does not have any entry parameters
 */

void RTC_Start(void);
/**
 * @brief Stops the in-built RTC.
 * @param: does not have any entry parameters
 */

void RTC_Stop(void);

/**
 * @brief Initializes the in-built RTC.
 * @param: does not have any entry parameters
 */

void RTC_HalInit (void );

/**
 * @brief Gets the value of the RTC and puts into the struct given by the parameter.
 * @param *dateTime: Time structure that will serve to store the current time in which we find the RTC
 * @note This function must be called prior to any other RTC functions
 */

void RTC_HalGetValue ( struct tm *dateTime );

/**
 * @brief Sets the value of the RTC given by the entry parameter.
 * @param *dateTime: Time structure that will set the current time of the RTC
 */

void RTC_HalSetValue ( struct tm *dateTime );
/**
 * @}
 */
/**
 * @}
 */
#endif
