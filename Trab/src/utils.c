/**
 * @file utils.c
 * @brief Contains various useful functions for the Project
 * @version 1
 * @date 12 Dez 2023
 * @author Grupo 6
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "ENCODER.h"
#include "LCD.h"
#include "RTC.h"
#include "timer.h"
#include <stdbool.h>
#include "utils.h"
#include "mfrc522.h"
#include "string.h"

//time useful defines and declarations
#define TIMEOUT 20000	//20 segundos
#define BLINK 300		// 0,3seg
#define CURSOR 5		//Inicio do relogio
#define CURSORDATA 0	//Inicio do calendario



enum stateRTC { YEAR, MONTH, DAY, DWEEK, HOUR, MIN, SEC, UPDATE, EXIT};
static volatile int blink;
static volatile bool blinkToggle;
static volatile int cursor;
static volatile int state;


//





int numDays(int year, int month){
	int evenMonth = !(month % 2);

	if (month==2)	{
		//Mês de fevereiro tem 28 dias e soma 1 (condição verdadeira) se for bissexto, soma 0 (condição falsa)
		return 28 + (year%400 == 0 || (year%4 == 0 && year%100 != 0));
	}

	if ((month<=7 && evenMonth) || (month>=8 && !evenMonth)) return 30;

	return 31;
}


void textCalendar(struct tm *dateTime){
	char dweek[7][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

	if(DELAY_GetElapsedMillis(blink)>BLINK){
		blinkToggle=!blinkToggle;
		blink = DELAY_GetElapsedMillis(0);

		if(blinkToggle){
			LCDText_SetCursor ( 2 , CURSORDATA );
			LCDText_Printf (" %04d-%02d-%02d  %s",dateTime->tm_year,dateTime->tm_mon,dateTime->tm_mday, dweek[dateTime->tm_wday]);
		}else{
			LCDText_SetCursor ( 2 , cursor );
			if (state==YEAR || state==DWEEK)
				LCDText_WriteString ( "    ");
			else
				LCDText_WriteString ( "  ");
		}
	}
}


void textClock(struct tm *dateTime){

	if(DELAY_GetElapsedMillis(blink)>BLINK){
		blinkToggle=!blinkToggle;
		blink = DELAY_GetElapsedMillis(0);

		if(blinkToggle){
			LCDText_SetCursor ( 2 , CURSOR);
			LCDText_Printf ("%02d:%02d:%02d",dateTime->tm_hour,dateTime->tm_min,dateTime->tm_sec);
		}else{
			LCDText_SetCursor ( 2 , cursor );
			LCDText_WriteString ( "  ");
		}
	}

}


void setDate(struct tm *dateTime ){

	RTC_Stop();
	int timeout = DELAY_GetElapsedMillis(0);
	state = YEAR;
	int encoderRot;
	blink = DELAY_GetElapsedMillis(0);
	blinkToggle = 0; //false
	ENCODER_GetValue(); // mete os valores a 0 caso haja algum
	RTC_GetValue(dateTime);
	LCDText_Clear();
	LCDText_Printf(" YR   M  D DWEEK");

	while(state!=EXIT){

		switch(state){
		case YEAR:
			encoderRot = ENCODER_GetValue();
			cursor = CURSORDATA;
			textCalendar(dateTime);

			if(encoderRot !=0){
				timeout = DELAY_GetElapsedMillis(0);
				dateTime ->tm_year += encoderRot;
			}

		    if(ENCODER_GetButton() == BUTTON_CLICKED){

		    	state = MONTH;

		    }
			if(TIMEOUT < DELAY_GetElapsedMillis(timeout)){

				state = UPDATE;

			}
			break;
		case MONTH:
			encoderRot = ENCODER_GetValue();
			cursor = CURSORDATA +6;
			textCalendar(dateTime);

			if(encoderRot !=0){
				timeout = DELAY_GetElapsedMillis(0);
				dateTime ->tm_mon += encoderRot;
			}

			if(dateTime->tm_mon>12) dateTime->tm_mon = 1;

			if(dateTime->tm_mon<1) dateTime->tm_mon = 12;

		    if(ENCODER_GetButton() == BUTTON_CLICKED){

		    	state = DAY;

		    }
			if(TIMEOUT < DELAY_GetElapsedMillis(timeout)){

				state = UPDATE;

			}
			break;

		case DAY:
			encoderRot = ENCODER_GetValue();
			cursor = CURSORDATA +9;
			textCalendar(dateTime);

			if(encoderRot !=0){
				timeout = DELAY_GetElapsedMillis(0);
				dateTime ->tm_mday += encoderRot;
			}

			if(dateTime->tm_mday > numDays(dateTime->tm_year, dateTime->tm_mon)) dateTime->tm_mday= 1;

			if(dateTime->tm_mday<1) dateTime->tm_mday = numDays(dateTime->tm_year, dateTime->tm_mon);

		    if(ENCODER_GetButton() == BUTTON_CLICKED){

		    	state = DWEEK;

		    }
			if(TIMEOUT < DELAY_GetElapsedMillis(timeout)){

				state = UPDATE;

			}
			break;


		case DWEEK:

			encoderRot = ENCODER_GetValue();
			cursor = CURSORDATA +13;
			textCalendar(dateTime);

			if(encoderRot !=0){
				timeout = DELAY_GetElapsedMillis(0);
				dateTime ->tm_wday += encoderRot;
			}

			if(dateTime -> tm_wday >6) dateTime-> tm_wday = 0;

			if(dateTime -> tm_wday <0) dateTime-> tm_wday = 6;

		    if(ENCODER_GetButton() == BUTTON_CLICKED){

		    	state = UPDATE;

		    }
			if(TIMEOUT < DELAY_GetElapsedMillis(timeout)){

				state = UPDATE;

			}
			break;


		case UPDATE:

			RTC_SetValue(dateTime);
			RTC_Start();
			LCDText_Clear();

			state = EXIT;
			break;

		default:
			break;

		}




	}



}


void setClock(struct tm *dateTime ){

	RTC_Stop();
	state = HOUR;
	int timeout = DELAY_GetElapsedMillis(0);

	int encoderRot;
	blink = DELAY_GetElapsedMillis(0);
	blinkToggle= 0 ; //false
	RTC_GetValue(dateTime);
	ENCODER_GetValue();

	LCDText_Clear();
	LCDText_Printf ("HH MM SS");


	while(state !=EXIT){

		switch(state){
		case HOUR:

			encoderRot = ENCODER_GetValue();
			cursor = CURSORDATA;

			if(encoderRot !=0){
				timeout = DELAY_GetElapsedMillis(0);
				dateTime ->tm_hour += encoderRot;

				if(dateTime->tm_hour >23) dateTime->tm_hour =0;

				if(dateTime->tm_hour <0) dateTime->tm_hour =23;

			}
			textClock(dateTime);
		    if(ENCODER_GetButton() == BUTTON_CLICKED){

		    	state = MIN;

		    }
			if(TIMEOUT < DELAY_GetElapsedMillis(timeout)){

				state = UPDATE;

			}
			break;

		case MIN:
			encoderRot = ENCODER_GetValue();
			cursor = CURSOR+5;
			if ( encoderRot!=0){
				timeout = DELAY_GetElapsedMillis(0);
				dateTime->tm_min += encoderRot;
				if(dateTime->tm_min > 59)
					dateTime->tm_min = 0;
				if(dateTime->tm_min < 0)
					dateTime->tm_min = 59;
			}

			textClock(dateTime);
			if (ENCODER_GetButton()==BUTTON_CLICKED){
				state = SEC;
			}

			if(TIMEOUT<DELAY_GetElapsedMillis(timeout))
				state = UPDATE;

			break;


		case SEC:
			encoderRot = ENCODER_GetValue();
			cursor = CURSOR+6;
			if ( encoderRot!=0){
				timeout = DELAY_GetElapsedMillis(0);
				dateTime->tm_sec += encoderRot;
				if(dateTime->tm_sec > 59)
					dateTime->tm_sec = 0;
				if(dateTime->tm_sec < 0)
					dateTime->tm_sec = 59;
			}

			textClock(dateTime);

			if (ENCODER_GetButton()==BUTTON_CLICKED ){
				state = UPDATE;
			}

			if(TIMEOUT<DELAY_GetElapsedMillis(timeout))
				state = UPDATE;

			break;

		case UPDATE:
			RTC_SetValue (dateTime ) ;
			RTC_Start();
			LCDText_Clear ();
			state = EXIT;
			break;

		default:
			state = HOUR;
			break;

		}

	}

}
/*
// WRITING AND READING LOGS AND OTHER STRUCTS TO AND FROM FLASH

	AuthCardsType readAuthCardFromFlash(int index){
	    AuthCardsType card;
	    memcpy(&card, (void *)(AUTH_CARDS_START_ADDRESS + index * sizeof(AuthCardsType)), sizeof(AuthCardsType));
	    return card;
	}

	void writeAuthCardToFlash(int index, AuthCardsType card){
		unsigned int prepareStatus =  FLASH_PrepareSector (SECTOR);
		if(prepareStatus ==0){
			unsigned int writeStatus = FLASH_WriteData((void *)(AUTH_CARDS_START_ADDRESS + index * sizeof(AuthCardsType)), &card, sizeof(AuthCardsType));
		}
	}

	void addAuthCardToFlash(AuthCardsType newCard){
	    writeAuthCardToFlash(authCardsCount, newCard);

	}

	LogsType readLogsFromFlash(int index) {
	    LogsType log;
	    memcpy(&log, (void *)(LOGS_START_ADDRESS + index * sizeof(LogsType)), sizeof(LogsType));
	    return log;
	}

	void writeLogsToFlash(int index, LogsType log){
		unsigned int prepareStatus =  FLASH_PrepareSector (SECTOR);
		if(prepareStatus ==0){
			unsigned int writeStatus = FLASH_WriteData((void *)(LOGS_START_ADDRESS + index * sizeof(LogsType)), &log, sizeof(LogsType));

		}
	}

	void addLogToFlash(LogsType newLog){
	    writeLogsToFlash(logsCount, newLog);
	    logsCount++;
	}

	void rebuildPointers(void){
	    for (int i = 0; i < authCardsCount - 1; i++) {
	        AuthCardsType currentCard = readAuthCardFromFlash(i);
	        AuthCardsType nextCard = readAuthCardFromFlash(i + 1);

	        currentCard.next = &nextCard;
	        nextCard.previous = &currentCard;

	        writeAuthCardToFlash(i, currentCard);
	        writeAuthCardToFlash(i + 1, nextCard);
	    }

	    for (int i = 0; i < logsCount - 1; i++) {
	        LogsType currentLog = readLogsFromFlash(i);
	        LogsType nextLog = readLogsFromFlash(i + 1);

	        currentLog.next = &nextLog;
	        nextLog.previous = &currentLog;

	        writeLogsToFlash(i, currentLog);
	        writeLogsToFlash(i + 1, nextLog);
	    }
	}

	void loadFromFlash(void){
	    authCardsCount = 0;
	    while (readAuthCardFromFlash(authCardsCount).uid.size != 0) {
	        authCardsCount++;
	    }

	    logsCount = 0;
	    while (readLogsFromFlash(logsCount).uid.size != 0) {
	        logsCount++;
	    }



	}


	void saveToFlash(void){
	    for (int i = 0; i < authCardsCount; i++) {
	        writeAuthCardToFlash(i, readAuthCardFromFlash(i));
	    }

	    for (int i = 0; i < logsCount; i++) {
	        writeLogsToFlash(i, readLogsFromFlash(i));
	    }
	}


	void saveStartupStateToFlash(){
		unsigned int prepareStatus =  FLASH_PrepareSector (SECTOR);
		if(prepareStatus ==0){
			unsigned int writeStatus = FLASH_WriteData((void *)FLASH_START_ADDRESS, &startup, sizeof(StartupStateRestoreType));
		}
	}


	StartupStateRestoreType loadStartupStateFromFlash(void){
	    StartupStateRestoreType startupState;
	    memcpy(&startupState, (void *)FLASH_START_ADDRESS, sizeof(StartupStateRestoreType));
	    return startupState;
	}

	bool isAuth(Uid uid){
	    for (int i = 0; i < authCardsCount; i++) {
	        AuthCardsType authCard = readAuthCardFromFlash(i);
	        if (memcmp(uid.uidByte, authCard.uid.uidByte, sizeof(uid.uidByte)) == 0) {
	            return true;
	        }
	    }
	    return false;
	}



	//startup load and save functions

	void loadStartup() {


		RTC_SetValue(startup->dateTime);
		*LockerState = startup->lockerState;
		currentAllowedCard->size = startup->uid.size;
		currentAllowedCard->sak = startup->uid.sak;
		for(int i; i<10; i++){
			currentAllowedCard->uidByte[i]=startup->uid.uidByte[i];
		}


	}

	void saveStartup(){

		startup->lockerState=LockerState;
		startup->uid.size = currentAllowedCard->size;
		startup->uid.sak = currentAllowedCard->sak;
		for(int i; i<10; i++){
			startup->uid.uidByte[i]= currentAllowedCard->uidByte[i];
		}

	}

*/
