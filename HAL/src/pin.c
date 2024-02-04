/**
 * @file   pin.c
 * @brief Contains the API that will deal with activating and regulating the various pins
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "pin.h"
#define LPC_GPIO_SIZE sizeof(LPC_GPIO_TypeDef)

bool PIN_Check(PinID_typedef id){

	uint32_t port = id / LPC_GPIO_NUM_PINS;
	uint32_t pin = id % LPC_GPIO_NUM_PINS;
	LPC_GPIO_TypeDef *gpio = (LPC_GPIO_TypeDef * ) (LPC_GPIO_BASE + (port * LPC_GPIO_SIZE));

	if(gpio->FIOPIN & (1<<pin)){
		return 1;
	}else{
		return 0;
	}

}

void PIN_Dir(PinID_typedef id, bool dir){
	uint32_t port = id / LPC_GPIO_NUM_PINS;
	uint32_t pin = id % LPC_GPIO_NUM_PINS;
	LPC_GPIO_TypeDef *gpio = (LPC_GPIO_TypeDef * ) (LPC_GPIO_BASE + (port * LPC_GPIO_SIZE));
	gpio->FIODIR |= dir<<pin;

}
void PIN_Set(PinID_typedef id){
	uint32_t port = id / LPC_GPIO_NUM_PINS;
	uint32_t pin = id % LPC_GPIO_NUM_PINS;
	LPC_GPIO_TypeDef *gpio = (LPC_GPIO_TypeDef * ) (LPC_GPIO_BASE + (port * LPC_GPIO_SIZE));
	gpio->FIOSET = 1<<pin;
}
void PIN_Clear(PinID_typedef id){
	uint32_t port = id / LPC_GPIO_NUM_PINS;
	uint32_t pin = id % LPC_GPIO_NUM_PINS;
	LPC_GPIO_TypeDef *gpio = (LPC_GPIO_TypeDef * ) (LPC_GPIO_BASE + (port * LPC_GPIO_SIZE));
	gpio->FIOCLR = 1<<pin;
}



