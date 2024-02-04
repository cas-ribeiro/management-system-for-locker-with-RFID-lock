/**
 * @file DELAY.c
 * @brief Contains the API that will deal with the various clocks and timer functionalities
 * @version 1
 * @date 4 Oct 2023
 * @author Grupo 6
 */
#include "DELAY.h"
#include "timer.h"

#include "SYSTICK.h"
#define SYSTICK_FREQ (SystemCoreClock / 1000)

int DELAY_Init(void)
{
	return SYSTICK_Init(SYSTICK_FREQ);
}

void DELAY_Milliseconds(uint32_t millis)
{
	uint32_t start = SYSTICK_GetValue();
	while ((SYSTICK_GetValue() - start) < millis) {
		__WFI();
	}
}

uint32_t DELAY_GetElapsedMillis(uint32_t start)
{
return SYSTICK_GetValue() - start;
}


void DELAY_StopwatchInit ( void ) {

	return TIMER_StopwatchInit();

}

void DELAY_Stopwatch ( uint32_t waitUs ) {

	return TIMER_Stopwatch(waitUs);
}
