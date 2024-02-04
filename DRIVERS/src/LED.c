/**
 * @file LED.c
 * @brief Contains the API to work with the in-built LED
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */


#include <stdbool.h>
#include "LED.h"

#include "pin.h"
#include "pinconfig.h"

void LED_Init ( bool state ){

	PIN_settype(LED_PIN, 0);
	PIN_Dir(LED_PIN, LED_DIR);
	if(state){
	PIN_Set(LED_PIN);
	}else{
		  PIN_Clear(LED_PIN);
	}
}

bool LED_GetState ( void ) {

	return PIN_Check(LED_PIN);

}
void LED_On ( void )   {

	PIN_Set(LED_PIN);

}
void LED_Off ( void ) {

	PIN_Clear(LED_PIN);

}
void LED_Toggle ( void ) {

	if(LED_GetState()){
		LED_Off();
	}else{
		LED_On();
	}
}
