/**
 * @file   timer.c
 * @brief API that will deal with timers
 * @version 2
 * @date 15 Nov 2023
 * @author: Grupo 6
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>
#include "timer.h"


#define PRESCALER0 (SystemCoreClock / 1000000)	//100MHz/1000000 = 100 (valor da divisão)

#define CLK0 2		//bit 2 e 3
#define TIMER0_BIT_POS 1
#define MR0I 0 //interrupt no match register 0
#define MR0S 2
#define COUNTER_ENABLE 0
#define COUNTER_RESET 1

static volatile RIT_HandlerType ritHandler;

void RIT_ClockEnable(int position){
	LPC_SC->PCONP|=1<<position;
}

uint32_t RITPWR_GetPClk(int position, int speed){
	LPC_SC->PCLKSEL1 |=(speed<<(position));
	switch (speed){
	case 0:
		return SystemCoreClock/4;
	case 1:
		return SystemCoreClock ;
	case 2:
		return SystemCoreClock/2;
	case 3:
		return SystemCoreClock/8;

	}
	return -1;
}

void RIT_SetHandler(int rateMillis, RIT_HandlerType handler){

	uint32_t clock;
	RIT_ClockEnable(CLKPWR_PCONP_PCRIT);
	clock = RITPWR_GetPClk(CLKPWR_PCLKSEL_RIT,CLKPWR_PCLKSEL_SPEED);
	LPC_RIT->RIMASK = 0;
	LPC_RIT->RICOUNTER = 0;
	LPC_RIT->RICTRL = RIT_CTRL_ENABLE | RIT_CTRL_ENABLE_DEBUG;
	LPC_RIT->RICOMPVAL = ((clock / 1000) * rateMillis) - 1;
	ritHandler = handler;

}

void RIT_IRQHandler(void)
{
	//printf("RIT Interrupt\n");
	if (ritHandler != 0) {
		ritHandler();
	}
	else {
		while(1) {}
	}
}

bool RIT_Start(void){

	if (ritHandler != 0) {
		NVIC_EnableIRQ(RIT_IRQn);
		LPC_RIT->RICTRL |= RIT_CTRL_ENABLE_CLEAR;
	}
	return ritHandler != 0;

}

void RIT_Stop(void){

	LPC_RIT->RICTRL &= ~RIT_CTRL_ENABLE_CLEAR;
	NVIC_DisableIRQ(RIT_IRQn);

}
void RIT_Restart(void){

	LPC_RIT->RICTRL |= RIT_CTRL_ENABLE_CLEAR;

}


void TIMER_StopwatchInit ( void){
	LPC_SC->PCONP |= (1 << TIMER0_BIT_POS);     // bit 1 PCTIM0 power/clock control bit (pag 65)
	LPC_SC->PCLKSEL0 |= 1 << CLK0;				//Clock for timer = CCLK  (pag 58 e 59)
	//CCLK = 100MHz								//bit 3 e 2 da pag 58





	LPC_TIM0->PR = PRESCALER0-1;				// pre-scaller com resolução de 1 micro seg (pag 503)

	LPC_TIM0->MCR |= 1 << MR0I;      			// Interrupt on MR0 (pag 507)
	LPC_TIM0->MCR |= 1 << MR0S;      			// STOP on MR0.



	LPC_TIM0->TCR |= 1 << COUNTER_RESET;      	// Counter reset (pag 505)
	LPC_TIM0->TCR &= ~(1 << COUNTER_RESET);



	}

void TIMER_Stopwatch ( uint32_t waitUs ){

	LPC_TIM0->MR0 = waitUs;      				// Match Registor , multiplos de 1 micro seg  (pag 503)
	LPC_TIM0->TCR = 1 << COUNTER_RESET;     	// Counter reset (pag 505)

	LPC_TIM0->TCR &= ~(1 << COUNTER_RESET);
	//LPC_TIM0->TCR |= 1 << COUNTER_ENABLE;		// Enable timer (pag 505)
    LPC_TIM0->TCR = 1<<COUNTER_ENABLE;
	while (!(LPC_TIM0->IR & 1 << MR0I))
		__NOP();

	LPC_TIM0->IR|= 1 << MR0I;
}
