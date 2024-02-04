/**
 * @file RTC.c
 * @brief contains the basic API for the Real Time Clock
 * @version 1
 * @date 25 Oct 2023
 * @author Grupo 6
 */

#include "RTC.h"
#include "rtcHal.h"
#include "pin.h"
#include "pinconfig.h"

void RTC_Init( time_t seconds ) {
	RTC_HalInit (  );

	//Segundos desde 1 janeiro 1970
    if(seconds!=0)
    	time(&seconds);
}

void RTC_GetValue( struct tm *dateTime ) {
	RTC_HalGetValue ( dateTime );
}

void RTC_SetValue( struct tm *dateTime ) {
	RTC_HalSetValue ( dateTime );
}

void RTC_SetSeconds( time_t seconds ){
	time(&seconds);
}

time_t RTC_GetSeconds(void){
	return time(NULL);
}
