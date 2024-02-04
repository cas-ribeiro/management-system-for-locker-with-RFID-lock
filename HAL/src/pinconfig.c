/**
 * @file   pinconfig.c
 * @brief Contains the API that will make the configuration of pins
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <pinconfig.h>


#define PORTOFFSET 0x4 //os registos PINSEL são registos de 32 bits

void PIN_settype(PinID_typedef id, int mode){

		uint32_t pinsel = id / LPC_PINSEL_NUM_PINS;
		uint32_t pin = id % LPC_PINSEL_NUM_PINS;
		pin = pin*2; //por causa de cada PIN ocupar 2 bits
		mode = mode & 0x00000003; // instrução para "pintar" os bits todos de 0 exceto os 2 que são importantes
		uint32_t *addr = (uint32_t *)&LPC_PINCON->PINSEL0;
		addr += pinsel;
		int data = *addr;
		data = (data & ~(3 << pin));
		*addr = (data | (mode << pin));
}


