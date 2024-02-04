/**
 * @file   pin.h
 * @brief Contains the API that will deal with activating and regulating the various pins
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */

#ifndef PIN_H_
#define PIN_H_

#include <stdbool.h>

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

/**
 * @defgroup HAL HAL
* @brief This package provides hardware abstraction layer functions.
* @{
 */

/** @defgroup PINS PINS
* @brief Provides the core capabilities for GPIO.
* @{
* */
typedef enum{
	Port0 = 0, //GPIO0
	Port1 = 1,
	Port2 = 2,
	Port3 = 3
}Port_typedef;

typedef enum{
	gpio0_0 = (0*32 + 0),
	gpio0_1 = (0*32 + 1),
	gpio0_2 = (0*32 + 2),
	gpio0_3 = (0*32 + 3),
	gpio0_4 = (0*32 + 4),
	gpio0_5 = (0*32 + 5),
	gpio0_6 = (0*32 + 6),
	gpio0_7 = (0*32 + 7),
	gpio0_8 = (0*32 + 8),
	gpio0_9 = (0*32 + 9),
	gpio0_10 = (0*32 + 10),
	gpio0_11 = (0*32 + 11),
	gpio0_12 = (0*32 + 12),
	gpio0_13 = (0*32 + 13),
	gpio0_14 = (0*32 + 14),
	gpio0_15 = (0*32 + 15),
	gpio0_16 = (0*32 + 16),
	gpio0_17 = (0*32 + 17),
	gpio0_18 = (0*32 + 18),
	gpio0_19 = (0*32 + 19),
	gpio0_20 = (0*32 + 20),
	gpio0_21 = (0*32 + 21),
	gpio0_22 = (0*32 + 22),
	gpio0_23 = (0*32 + 23),
	gpio0_24 = (0*32 + 24),
	gpio0_25 = (0*32 + 25),
	gpio0_26 = (0*32 + 26),
	gpio0_27 = (0*32 + 27),
	gpio0_28 = (0*32 + 28),
	gpio0_29 = (0*32 + 29),
	gpio0_30 = (0*32 + 30),
	gpio0_31 = (0*32 + 31),
	gpio1_0 = (1*32 + 0),
	gpio1_1 = (1*32 + 1),
	gpio1_2 = (1*32 + 2),
	gpio1_3 = (1*32 + 3),
	gpio1_4 = (1*32 + 4),
	gpio1_5 = (1*32 + 5),
	gpio1_6 = (1*32 + 6),
	gpio1_7 = (1*32 + 7),
	gpio1_8 = (1*32 + 8),
	gpio1_9 = (1*32 + 9),
	gpio1_10 = (1*32 + 10),
	gpio1_11 = (1*32 + 11),
	gpio1_12 = (1*32 + 12),
	gpio1_13 = (1*32 + 13),
	gpio1_14 = (1*32 + 14),
	gpio1_15 = (1*32 + 15),
	gpio1_16 = (1*32 + 16),
	gpio1_17 = (1*32 + 17),
	gpio1_18 = (1*32 + 18),
	gpio1_19 = (1*32 + 19),
	gpio1_20 = (1*32 + 20),
	gpio1_21 = (1*32 + 21),
	gpio1_22 = (1*32 + 22),
	gpio1_23 = (1*32 + 23),
	gpio1_24 = (1*32 + 24),
	gpio1_25 = (1*32 + 25),
	gpio1_26 = (1*32 + 26),
	gpio1_27 = (1*32 + 27),
	gpio1_28 = (1*32 + 28),
	gpio1_29 = (1*32 + 29),
	gpio1_30 = (1*32 + 30),
	gpio1_31 = (1*32 + 31),
	gpio2_0 = (2*32 + 0),
	gpio2_1 = (2*32 + 1),
	gpio2_2 = (2*32 + 2),
	gpio2_3 = (2*32 + 3),
	gpio2_4 = (2*32 + 4),
	gpio2_5 = (2*32 + 5),
	gpio2_6 = (2*32 + 6),
	gpio2_7 = (2*32 + 7),
	gpio2_8 = (2*32 + 8),
	gpio2_9 = (2*32 + 9),
	gpio2_10 = (2*32 + 10),
	gpio2_11 = (2*32 + 11),
	gpio2_12 = (2*32 + 12),
	gpio2_13 = (2*32 + 13),
	gpio2_14 = (2*32 + 14),
	gpio2_15 = (2*32 + 15),
	gpio2_16 = (2*32 + 16),
	gpio2_17 = (2*32 + 17),
	gpio2_18 = (2*32 + 18),
	gpio2_19 = (2*32 + 19),
	gpio2_20 = (2*32 + 20),
	gpio2_21 = (2*32 + 21),
	gpio2_22 = (2*32 + 22),
	gpio2_23 = (2*32 + 23),
	gpio2_24 = (2*32 + 24),
	gpio2_25 = (2*32 + 25),
	gpio2_26 = (2*32 + 26),
	gpio2_27 = (2*32 + 27),
	gpio2_28 = (2*32 + 28),
	gpio2_29 = (2*32 + 29),
	gpio2_30 = (2*32 + 30),
	gpio2_31 = (2*32 + 31)
}PinID_typedef;

typedef enum{
	o00 = 0,
	o01 = 1,
	o10 = 2,
	o11 = 3
}PinMode_typedef;


#define OUT 1
#define IN 0
#define LPC_GPIO_NUM_PINS 32
/**
 * @brief Reads the state of the pin which its Id was given
 * @param id: Pin which is to be checked
 * @return the current state of the Pin given by parameter
 */
bool PIN_Check(PinID_typedef id);
/**
 * @brief Sets the Direction of a pin which its Id was given, the Dir is also given
 * @param id: Pin which we wish to change direction
 * @param dir: Direction to be put in given Pin
 */
void PIN_Dir(PinID_typedef id, bool dir);
/**
 * @brief Sets the Set of given pin to 1
 * @param id: Pin which we wish to Set
 */
void PIN_Set(PinID_typedef id);
/**
 * @brief Sets the Reset of given pin to 1
 * @param id: pin which we wish to Reset
 */
void PIN_Clear(PinID_typedef id);



/**
 * @}
 */
/**
 * @}
 */
#endif /* PIN_H_ */
