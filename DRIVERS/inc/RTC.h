/**
 * @file RTC.h
 * @brief contains the basic API for the Real Time Clock
 * @version 1
 * @date 25 Oct 2023
 * @author Grupo 6
 */


#ifndef RTC_H_
#define RTC_H_
#include <stdlib.h>
#include <time.h>
#include "rtcHal.h"
/**
 * @addtogroup DRIVERS
* @brief This package provides driver functions.
* @{
 */

/** @defgroup RTC RTC
* @brief Provides the core capabilities for the built-in Real Time Clock.
* @{
* */

/**
 * @brief Initializes the API for the RTC.
 * @param seconds: seconds since 1/1/1970, 00:00:00 UTC
 */
void RTC_Init( time_t seconds ) ;


/**
 * @brief Reads RTC's current value in the form of a date
 * @param dateTime: pointer to the structure where the value of the date is stored
 */
void RTC_GetValue( struct tm *dateTime ) ;


/**
 * @brief Updates the RTC to the new values passed to it in the form of a date
 * @param  dateTime: pointer to a structure containing the date with which to update the clock
 */
void RTC_SetValue( struct tm *dateTime ) ;


/**
 * @brief Updates the RTC to the new values passed to it in the form of seconds
 * @param seconds: seconds since 1/1/1970, 00:00:00 UTC
 */
void RTC_SetSeconds( time_t seconds ) ;



/**
 * @brief Reads RTC's current value in the form of seconds since 1/1/1970, 00:00:00 UTC
 * @param : does not have any entry parameters
 * @return seconds: seconds since 1/1/1970, 00:00:00 UTC
 */
time_t RTC_GetSeconds(void) ;


/**
 * @}
 */
/**
 * @}
 */

#endif /* RTC_H_ */
