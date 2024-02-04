/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */



/*
===============================================================================
| Name        : Trab.c                                                        |
| Author      : Grupo 6                                                       |
| Version     : 1                                                             |
| Copyright   : $(copyright)                                                  |
| Description : main definition                                               |
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdbool.h>
#include <stdio.h>
#include "LED.h"
#include "DELAY.h"
#include "LCD.h"
#include "RTC.h"
#include "ENCODER.h"
#include "flash.h"
#include "mfrc522.h"
#include "DRIVERS_MFRC522.h"
#include "utils.h"
#include "modes.h"

#define LCD_INTERVALO 2000000// 2s em micros





typedef enum ModoEnum {
	NORMAL,
	MANUTENCAO
} MODO_State_t ;

int main(void) {

	DELAY_StopwatchInit ();
	LCDText_Init();
    LED_Init(1);
	RTC_Init(0);
	DELAY_Init();

	ENCODER_Init(5);
	MFRC522_Init();
	struct tm dateTime;



	dateTime.tm_hour = 20; //  20:00:00 pm
	dateTime.tm_min =  48;
	dateTime.tm_sec =  0;
	dateTime.tm_mday = 15;
	dateTime.tm_mon = 11;
	dateTime.tm_year = 2023;

	RTC_SetValue(&dateTime);



	MODO_State_t modo = NORMAL;



    while(1) {
    	switch(modo){
    		case NORMAL:
    			modoNormal(&dateTime);
    			modo = MANUTENCAO;
    			break;
    		case MANUTENCAO:
    			modoManutencao(&dateTime);
    			modo = NORMAL;
    			break;

    	}
    }

    return 0 ;
}

