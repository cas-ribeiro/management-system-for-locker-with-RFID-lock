/**
 * @file rtcHal.c
 * @brief contains the basic API for the Real Time Clock
 * @version 1
 * @date 7 Nov 2023
 * @author Grupo 6
 */

#include "rtcHal.h"
#include <time.h>
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

void RTC_Start(void){
    LPC_RTC->CCR = (1<<SBIT_CLKEN); /* Enable the clock for RTC */
}

void RTC_Stop(void){
    LPC_RTC->CCR = 0;
}

void RTC_HalInit ( void ){
    LPC_SC->PCONP |=(1<<PCRTC); // Enable the power to RTC module
	/* Disable RTC clock, reset clock, Enable RTC calibration */
	LPC_RTC->CCR = ((1<<SBIT_CTCRST) | (1<<SBIT_CCALEN));	//pag 573
	LPC_RTC->CALIBRATION = 0x00;		//Sem calibração
    LPC_RTC->CCR = (1<<SBIT_CLKEN); /* Enable the clock for RTC */
}

void RTC_HalGetValue ( struct tm *dateTime ){

    dateTime->tm_sec     = LPC_RTC->SEC ;	    // Lê os segundos
    dateTime->tm_min     = LPC_RTC->MIN ;	    // Lê os minutos
    dateTime->tm_hour    = LPC_RTC->HOUR;	    // Lê a hora
    dateTime->tm_wday 	 = LPC_RTC->DOW;        // Lê o dia da semana
    dateTime->tm_mday    = LPC_RTC->DOM;	    // Lê o dia do mês
    dateTime->tm_mon     = LPC_RTC->MONTH-1;    // Lê o mês
    dateTime->tm_year    = LPC_RTC->YEAR-1900;  // Lê o ano
}

void RTC_HalSetValue ( struct tm *dateTime ){
	LPC_RTC->SEC   =   dateTime->tm_sec ;       // atualiza os segundos
	LPC_RTC->MIN   =  dateTime->tm_min;	   		// atualiza os minutos
	LPC_RTC->HOUR	=  dateTime->tm_hour;	    // atualiza a hora
	LPC_RTC->DOW	=  dateTime->tm_wday;  		// atualiza o dia da semana
	LPC_RTC->DOM	=  dateTime->tm_mday;	    // atualiza o dia do mês
	LPC_RTC->MONTH =  dateTime->tm_mon+1;	    // atualiza o mês
	LPC_RTC->YEAR  =  dateTime->tm_year+1900;	// atualiza o ano

}
