/**
 * @file   SYSTICK.c
 * @brief Contains the SYSTICK API
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>
#include "SYSTICK.h"
static volatile uint32_t __tick;

void SysTick_Handler(void)
{
	__tick++;
}

int SYSTICK_Init(uint32_t value)
{
	SystemCoreClockUpdate();
	if (SysTick_Config(value) == 1) return -1;
	return 0;
}

uint32_t SYSTICK_GetValue(void)
{
	return __tick;
}
