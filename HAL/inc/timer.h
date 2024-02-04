/**
 * @file   timer.h
 * @brief API that will deal with timers
 * @version 2
 * @date 15 Nov 2023
 * @author: Grupo 6
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>
/**
 * @addtogroup HAL
* @brief This package provides hardware abstraction layer functions.
* @{
 */

/** @defgroup TIMER TIMER
* @brief Provides the core capabilities for system timer functions.
* @{
* */


#define RIT_CTRL_ENABLE_CLEAR 2 // página 513
#define RIT_CTRL_ENABLE_DEBUG 4 // pagina 513
#define RIT_CTRL_ENABLE 8
#define CLKPWR_PCONP_PCRIT 16
#define CLKPWR_PCLKSEL_RIT 26
#define CLKPWR_PCLKSEL_SPEED 1

typedef void (*RIT_HandlerType)(void);

/**
 * @brief Enables the RIT clock
 * @param position: Receives the position of the bit that activated the RIT clock
 * @return the current state of the built-in LED
 */

void RIT_ClockEnable(int position);

/**
 * @brief Powers up the RIT clock and gives it a given speed
 * @param position: Position of the bit to power up the RIT clock
 * @param speed: (1,2,3,4) to decide which of the 4 possible speeds it powers the RIT clock
 * @return the speed at which the clock is running in Hz
 */
uint32_t RITPWR_GetPClk(int position, int speed);
/**
 * @brief Sets the handler that the RIT interrupts will run
 * @param rateMillis: Rate at which it interrupts
 * @param handler: A RIT_HandlerType that will be the handler which runs in every interruption
 */

void RIT_SetHandler(int rateMillis, RIT_HandlerType handler);

/**
 * @brief Starts the in-built RIT
 * @param : Does not have entry parameters
 * @return the current state of the RIT
 */

bool RIT_Start(void);

/**
 * @brief Stops the in-built RIT
 * @param : Does not have entry parameters
 */

void RIT_Stop(void);

/**
 * @brief Restarts the in-built RIT
 * @param : Does not have entry parameters
 */
void RIT_Restart(void);

/**
 * @brief Handles the RIT interruptions
 * @param : Does not have entry parameters

 */

void RIT_IRQHandler(void);

/**
 * @brief Initializes Timer0 in a microseconds resolution
 * @param : Does not have entry parameters

 */

void TIMER_StopwatchInit ( void);
/**
 * @brief Waits the microseconds passed through parameter
 * @param waitUs: Number of microseconds supposed to wait
 */
void TIMER_Stopwatch ( uint32_t waitUs );

/**
 * @}
 */
/**
 * @}
 */

#endif /* TIMER_H_ */
