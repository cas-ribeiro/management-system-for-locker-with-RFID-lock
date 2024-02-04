/**
 * @file ENCODER.h
 * @brief Contains the API that will deal with the Rotary Encoder Switch
 * @version 1
 * @date 15 Nov 2023
 * @author Grupo 6
 */

#ifndef ENCODER_H_
#define ENCODER_H_


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "pin.h"
#include "pinconfig.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>
/* Montagem do ENCODER ao micro
 * CLK | P0.03
 * SW  | P2.13
 * DT  | P0.02
 */
/**
 * @addtogroup DRIVERS
* @brief This package provides driver functions.
* @{
 */

/** @defgroup ENCODER ENCODER
* @brief Provides the core capabilities for the Rotary Encoder Switch.
* @{
* */

//Switch do encoder
#define SW_PIN 77  //(2*32)+13

//DT do encoder
#define DT_PIN 2

//CLK do encoder
#define CLK_PIN 3

#define ENCODER_MODE_ON 0 // modo para os pinos como GPIO
#define ENCODER_DIR 0 // direção dos pinos
#define ENCODER_BUTTONINTERVAL 4  // ajustar
#define ENCODER_HOLD_TICKS 500  // ajustar
#define ENCODER_DCLICK_TICKS 200  // ajustar

typedef void (*ENCODER_HandlerType)(void);

typedef enum ButtonEnum {
BUTTON_NOTPRESSED, // Nao pressionado
BUTTON_CLICKED, // Pressionado e libertado num intervalo de tempo curto
BUTTON_DCLICKED // Pressionado e libertado num intervalo de tempo curto duas vezes
} ENCODER_ButtonValueType;

/**
 * @brief Interruption Handler to give the RIT
 * @param : Does not have entry parameters
 * @return none
 */
static void RotaryEncoderRITHandler(void);

/**
 * @brief Initializes the ENCODER
 * @param rate: rate at which the encoder is going to work at
 * @return none
 */
void ENCODER_Init( int rate ) ;

/**
 * @brief Reads the state of the built-in LED and returns its logical value
 * @param : Does not have entry parameters
 * @return the current state of the built-in LED
 * @note this function must be used before any other ENCODER function
 */
int ENCODER_GetValue(void) ;

/**
 * @brief Reads the state of the click of the button
 * @param : Does not have entry parameters
 * @return value of the button when it was called
 */
ENCODER_ButtonValueType ENCODER_GetButton(void) ;

/**
 * @brief Function that handles the ENCODER during interruptions
 * @param : Does not have entry parameters
 * @return none
 */
void ENCODER_Handler(void);

/**
 * @brief Reads the state of the two bits that determine rotation
 * @param : Does not have entry parameters
 * @return the value of those 2 bits
 */
int ReadValues(void);

/**
 * @}
 */
/**
 * @}
 */

#endif /* ENCODER_H_ */
