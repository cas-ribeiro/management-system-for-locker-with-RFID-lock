/**
 * @file modes.c
 * @brief Contains functions for the modes of the project
 * @version 1
 * @date 16 Dec 2023
 * @author Grupo 6
 */


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


int authCardsCount = 0;
int logsCount = 0;


AuthCardsType authCards[MAX_AUTH_CARDS];

LogsType logs[MAX_LOGS];

bool LockerState = 0;

Uid currentAllowedCard;

Uid readCard;

StartupStateRestoreType startup;


typedef enum ModoEnum{
	INITIAL_NORMAL_STATE,
	AUTH_ITEM_INSERT_STATE,
	NON_AUTH_STATE,
	AUTH_ITEM_REMOVAL_STATE,
	EXIT_NORMAL,
	INIT_MAINT_STATE,
	SET_CALENDAR_STATE,
	SET_CLOCK_STATE,
	SHOW_LOGS_STATE,
	CARD_MENU_STATE,
	CARD_ADD_STATE,
	CARD_REMOVE_STATE,
	EXIT_MAINT
}MAN_State_t;

void modoNormal(struct tm *dateTime){


	//loadStartup();

	LCDText_Clear();
	LCDText_Printf ("Modo Normal ");
	int buttonRot = BUTTON_NOTPRESSED;
	MAN_State_t state = INITIAL_NORMAL_STATE;






	while(state!=EXIT_NORMAL){
		switch(state){
			case INITIAL_NORMAL_STATE:
				buttonRot = ENCODER_GetButton();
				if(buttonRot == BUTTON_DCLICKED){
					state = EXIT_NORMAL;
					break;
				}
				LCDText_Clear();

				//DELAY_Milliseconds(1000);
				//DELAY_Stopwatch(4200);
				//LCDText_Printf("Waiting Card...");
				RTC_GetValue(dateTime);
				LCDText_Printf("%02d/%02d  "  , dateTime->tm_mday,dateTime->tm_mon );
				LCDText_Printf(" %02d:%02d" , dateTime->tm_hour, dateTime->tm_min );
				LCDText_Printf("\nState:%s", LockerState? "Occupied":"Empty");


				buttonRot = ENCODER_GetButton();
				if(buttonRot == BUTTON_DCLICKED){
					state = EXIT_NORMAL;
					break;
				}
				while(!PICC_IsNewCardPresent()){
					if(ENCODER_GetButton() == BUTTON_DCLICKED){
						state = EXIT_NORMAL;
						break;
					}

					LCDText_SetCursor(1,0);
					RTC_GetValue(dateTime);
					LCDText_Printf("%02d/%02d  "  , dateTime->tm_mday,dateTime->tm_mon );
					LCDText_Printf(" %02d:%02d" , dateTime->tm_hour, dateTime->tm_min );
					LCDText_Printf("\nState:%s", LockerState? "Occupied":"Empty");

					}
					if (PICC_ReadCardSerial(&readCard)) {
						buttonRot = ENCODER_GetButton();


						if(LockerState == 0){
							if(isAuthorized(readCard)){


								state =  AUTH_ITEM_INSERT_STATE;
							}
							else {

								state =  NON_AUTH_STATE;
							}
						}
						else {



							if(isEqual(readCard)){

								state =  AUTH_ITEM_REMOVAL_STATE;
							}
							else {

								state =  NON_AUTH_STATE;
							}

						}
					}
					else {
						LCDText_Clear();
						LCDText_Printf("Could not\nread Card...");


					}



				break;



			case AUTH_ITEM_INSERT_STATE:


				if(buttonRot == BUTTON_DCLICKED){
					state = EXIT_NORMAL;
				}
				LCDText_Clear();
				LED_Off();
				LockerState = 1;
				int encoderRot=0;
				int currentIndex = 0;
				while (!(ENCODER_GetButton() == BUTTON_CLICKED)) {
					LCDText_Clear();
			        encoderRot = ENCODER_GetValue();
			        currentIndex += encoderRot;
			        if (currentIndex < 0) {
			        	 currentIndex = authCardsCount - 1;
			        } else if (currentIndex >= authCardsCount) {
			        	 currentIndex = 0;
			        }
					for (int i = 0; i < authCards[currentIndex].size; i++) {
						LCDText_Printf("%02X", authCards[currentIndex].uidByte[i]);
					}

			        DELAY_Milliseconds(2000);

				}

		        for (int i = 0; i < authCards[currentIndex].size; ++i) {
		             currentAllowedCard.uidByte[i] = authCards[currentIndex].uidByte[i];
		        }
		        		currentAllowedCard.size = authCards[currentIndex].size;
				LED_On();
				DELAY_Milliseconds(5000);
				addLogEntry(readCard, 1);
				//DELAY_Stopwatch(1000);

				//saveStartupStateToFlash();

				LCDText_Clear();
				state = INITIAL_NORMAL_STATE;



				break;

			case NON_AUTH_STATE:




				if(buttonRot == BUTTON_DCLICKED){
					state = EXIT_NORMAL;
				}
				LCDText_Clear();
				LCDText_Printf("Cartao nao\n");
				LCDText_Printf("esta autorizado");
				DELAY_Milliseconds(2000);
				addLogEntry(readCard, 0);

				//saveStartupStateToFlash();
				state =  INITIAL_NORMAL_STATE;
				break;

			case AUTH_ITEM_REMOVAL_STATE:

				LCDText_Clear();
				LED_Off();
				LockerState = 0;
				for (int i = 0; i < currentAllowedCard.size; i++) {
					LCDText_Printf("%02X", currentAllowedCard.uidByte[i]);
				}
				DELAY_Milliseconds(5000);// 5 s
				LED_On();

				addLogEntry(readCard, 1);

				for(int i = 0; i < currentAllowedCard.size; i++){
					currentAllowedCard.uidByte[i]=0;
				}
				currentAllowedCard.size=0;
				state = INITIAL_NORMAL_STATE;
				//saveStartupStateToFlash();
				break;

			case EXIT_NORMAL:
				break;


			default:
				state = INITIAL_NORMAL_STATE;
				break;
		}
	}

}

void modoManutencao(struct tm *dateTime){
	LCDText_Clear();
	LCDText_Printf ("Modo Manutencao ");
	int buttonRot = 0;
	MAN_State_t state = INIT_MAINT_STATE;
	while(state!=EXIT_MAINT){
		switch(state){
			case INIT_MAINT_STATE:
				if(buttonRot == BUTTON_DCLICKED){
					state = EXIT_MAINT;
				}
				LCDText_Clear();
				char maintMenu[5][13] = {"Set Calendar","Set Clock   ","Manage Cards", "Show Logs   ", "Exit        "};
					int i = 0;
					while (!(ENCODER_GetButton() == BUTTON_CLICKED)){
						i += ENCODER_GetValue();
						if ( i < 0) i = 4;
						if (i > 4) i = 0 ;
						LCDText_SetCursor(1,0);
						LCDText_Printf("%s", (char*)maintMenu[i]);

					}
					switch (i){
					case 0:

						state = SET_CALENDAR_STATE;
						break;

					case 1:

						state = SET_CLOCK_STATE;
						break;
					case 2:

						state =  CARD_MENU_STATE;
						break;
					case 3:

						state =  SHOW_LOGS_STATE;
						break;
					case 4:
						state = EXIT_MAINT;
						break;
					}




				break;

			case SET_CALENDAR_STATE:
				if(buttonRot == BUTTON_DCLICKED){
					state = EXIT_MAINT;
				}

				setDate(dateTime);

				state = INIT_MAINT_STATE;

				break;

			case SET_CLOCK_STATE:
				if(buttonRot == BUTTON_DCLICKED){
					state = EXIT_MAINT;
				}

				setClock(dateTime);

				state = INIT_MAINT_STATE;

				break;


			case SHOW_LOGS_STATE:
			    if(buttonRot == BUTTON_DCLICKED){
			        state = EXIT_MAINT;
			    }
			    LCDText_Clear();
			    int index = 0;
			    while (!(ENCODER_GetButton() == BUTTON_CLICKED)){
			        index += ENCODER_GetValue();

					if ( index < 0) index =  logsCount- 1;
					if (index >= logsCount) index = 0 ;


			        if (logs[index].uidByte[0] != 0) {
			        	LCDText_SetCursor(1,0);
			        	LCDText_Printf("%d.", index+1);
			            displayLog(logs[index]);
			            //DELAY_Milliseconds(2000);
			        }
			        //LCDText_Clear();
			    }
			    LCDText_Clear();
			    state = INIT_MAINT_STATE;
			    break;

			case CARD_MENU_STATE:
				if(buttonRot == BUTTON_DCLICKED){
					state = EXIT_MAINT;
				}
				LCDText_Clear();
				char cardMenu[3][12] = {"Add Card   ", "Remove Card", "Back       "};
					int j = 0;
					while (!(ENCODER_GetButton() == BUTTON_CLICKED)){
						j += ENCODER_GetValue();
						if ( j < 0) j = 2;
						if (j > 2) j = 0 ;
						LCDText_SetCursor(1,0);
						LCDText_Printf("%s", (char*)cardMenu[j]);
					}
					LCDText_Clear();
					switch (j){
					case 0:

						state = CARD_ADD_STATE;
						break;
					case 1:

						state = CARD_REMOVE_STATE;
						break;
					case 2:

						state =  INIT_MAINT_STATE;
						break;
					default:

						state = CARD_MENU_STATE;
						break;
					}
				break;

			case CARD_ADD_STATE:

				Uid uid;
				if(ENCODER_GetButton() == BUTTON_DCLICKED){
					state = CARD_MENU_STATE;
					break;
				}
				LCDText_Clear();
			    while (1) {
					if(ENCODER_GetButton() == BUTTON_DCLICKED){
						state = CARD_MENU_STATE;
						break;
					}
			        LCDText_Printf("Waiting Card...");
			        if (!PICC_IsNewCardPresent()) {
			            DELAY_Milliseconds(100);
			            continue;
			        }
			        if (!PICC_ReadCardSerial(&uid)) {
			            DELAY_Milliseconds(100);
			            continue;
			        }
			        LCDText_Clear();
			        LCDText_Printf("Card: ");
			        for (uint8_t i = 0; i < uid.size; i++) {
			            LCDText_Printf("%02X", uid.uidByte[i]);

			        }
			        DELAY_Milliseconds(5000);

			        buttonRot = ENCODER_GetButton();
			        if (buttonRot == BUTTON_CLICKED) {

			        	addCard(uid.uidByte, uid.size);
			            state = CARD_MENU_STATE;
			            break;
			        }


			        //saveStartupStateToFlash();
			        DELAY_Milliseconds(100);
			        LCDText_Clear();
			    }

			    break;

			case CARD_REMOVE_STATE:
				if(ENCODER_GetButton() == BUTTON_DCLICKED){
					state = CARD_MENU_STATE;
					break;
				}
				LCDText_Clear();
				int indexCard= 0;
				int encoderButton;
				int noRemove =0;
				while(!(ENCODER_GetButton() == BUTTON_CLICKED)) {
					LCDText_Clear();

					indexCard += ENCODER_GetValue();

					if(authCardsCount == 0){
						state = CARD_MENU_STATE ;
						break;
					}
			        if (indexCard < 0) {
			            indexCard = authCardsCount - 1;
			        } else if (indexCard >= authCardsCount) {
			            indexCard = 0;
			        }
			        LCDText_Printf("%d.", indexCard+1);
					for (uint8_t i = 0; i < authCards[indexCard].size; i++) {
						LCDText_Printf("%02X", authCards[indexCard].uidByte[i]);
					}
					if(ENCODER_GetButton()== BUTTON_DCLICKED){
						noRemove = 1 ;
						break;
					}
					DELAY_Milliseconds(2000);



				}

				if(!(noRemove)){

				removeCard(indexCard);
				}
				LCDText_Clear();


				//saveStartupStateToFlash();
				state = CARD_MENU_STATE ;
				break;



			case EXIT_MAINT:
				break;

			default:
				state = INIT_MAINT_STATE;
				break;
		}
	}


}


int isAuthorized(Uid uid) {
    for (int i = 0; i < authCardsCount; i++) {

            bool match = true;
            for (int j = 0; j < uid.size; j++) {
                if (authCards[i].uidByte[j] != uid.uidByte[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {

                return true;
            }

    }

    return false;
}

int isEqual(Uid uid) {

	if(currentAllowedCard.size == 0) return false;
    for (int i = 0; i < currentAllowedCard.size; ++i) {
        if (uid.uidByte[i] != currentAllowedCard.uidByte[i]) {

            return false;
        }
    }

    return true;
}


void addLogEntry(Uid card, int authStatus) {


    struct tm dateTime;
    RTC_GetValue(&dateTime);

    if (logsCount == MAX_LOGS) {
        // If the maximum logs count is reached, shift entries to the left
        for (int i = 0; i < MAX_LOGS - 1; i++) {
            for (int j = 0; j < logs[j].size; j++) {
                logs[i].uidByte[j] = logs[i + 1].uidByte[j];
            }
            logs[i].size = logs[i + 1].size;
            logs[i].day = logs[i + 1].day;
            logs[i].month = logs[i + 1].month;
            logs[i].year = logs[i + 1].year;
            logs[i].hour = logs[i + 1].hour;
            logs[i].minute = logs[i + 1].minute;
            logs[i].authStatus = logs[i + 1].authStatus;
            logs[i].lockerState = logs[i + 1].lockerState;
        }
        for (int j = 0; j < card.size; j++) {
            logs[logsCount-1].uidByte[j] = card.uidByte[j];
        }
        logs[logsCount-1].size = card.size;
        logs[logsCount-1].day = dateTime.tm_mday;
        logs[logsCount-1].month = dateTime.tm_mon;
        logs[logsCount-1].year = dateTime.tm_year;
        logs[logsCount-1].hour = dateTime.tm_hour;
        logs[logsCount-1].minute = dateTime.tm_min;
        logs[logsCount-1].authStatus = authStatus;
        logs[logsCount-1].lockerState = LockerState;

        return;
    }




    for (int i = 0; i < card.size; i++) {
        logs[logsCount].uidByte[i] = card.uidByte[i];
    }

    logs[logsCount].size = card.size;
    logs[logsCount].day = dateTime.tm_mday;
    logs[logsCount].month = dateTime.tm_mon;
    logs[logsCount].year = dateTime.tm_year;
    logs[logsCount].hour = dateTime.tm_hour;
    logs[logsCount].minute = dateTime.tm_min;
    logs[logsCount].authStatus = authStatus;
    logs[logsCount].lockerState = LockerState;


    logsCount++;
}

void displayLog(LogsType log) {


    LCDText_Printf("%02d/%02d %02d:%02d \n", log.day, log.month, log.hour, log.minute);
    //LCDText_Printf("%s", log.authStatus ? "Auth" : "Not Auth");
    LCDText_Printf("%s ", log.lockerState ? "Occ" : "Emp");
    for (int i = 0; i < log.size; i++) {
        LCDText_Printf("%02X", log.uidByte[i]);
    }

}



void removeCard(int selectedIndex) {
    if (selectedIndex >= 0 && selectedIndex < authCardsCount) {

        for (int i = selectedIndex; i < authCardsCount - 1; i++) {
            authCards[i] = authCards[i + 1];
        }


        authCardsCount--;


        for (int i = 0; i < sizeof(AuthCardsType); i++) {
            authCards[authCardsCount].uidByte[i] = 0;
        }
        authCards[authCardsCount].size=0;
    }
}


void addCard(uint8_t  uidByte[10], uint8_t size) {
	LCDText_Clear();
    for (int i = 0; i < authCardsCount; ++i) {

        int match = 1;
        for (int j = 0; j < size; ++j) {
            if (authCards[i].uidByte[j] != uidByte[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
        	LCDText_Printf("Cartao ja\n adicionado");
            return;
        }
    }



    if (authCardsCount < MAX_AUTH_CARDS) {

        for (int i = 0; i < size; ++i) {
            authCards[authCardsCount].uidByte[i] = uidByte[i];
        }

        authCards[authCardsCount].size = size;
        authCardsCount++;
    }else {
    LCDText_Printf("Max number\nof cards");
    }
}


void saveStartup(void){

	startup.lockerState=LockerState;
	startup.size = currentAllowedCard.size;
	for(int i=0; i<currentAllowedCard.size; i++){
		startup.allowedCard[i]= currentAllowedCard.uidByte[i];
	}

}

void saveStartupStateToFlash(void) {
    saveStartup();


    unsigned int dstAligned = (FLASH_START_ADDRESS / 256) * 256;


    unsigned int srcAligned = (unsigned int) &startup;

    unsigned int prepareStatus = FLASH_PrepareSector(SECTOR);
    if (prepareStatus == 0) {

    	unsigned int writeStatus = FLASH_WriteData((void *) dstAligned, (void *) srcAligned, sizeof(StartupStateRestoreType));

    }
}

void loadStartup(void){

	loadStartupStateFromFlash();


	LockerState = startup.lockerState;
	currentAllowedCard.size = startup.size;

	for(int i=0; i<startup.size; i++){
		currentAllowedCard.uidByte[i]=startup.allowedCard[i];
	}
	authCardsCount = startup.CardsCount;
	logsCount = startup.LogsCount;
	//if(LockerState >1 ) LockerState = 0;

}

loadStartupStateFromFlash(void){

    memcpy(&startup, (void *)FLASH_START_ADDRESS, sizeof(StartupStateRestoreType));

}

/*
void saveStartupStateToFlash(void){

    memset(&startup, 0, sizeof(startup));
    for (int i = 0; i < 10; ++i) {
        startup.allowedCard[i] = currentAllowedCard.uidByte[i];
    }
    startup.size = currentAllowedCard.size;
    startup.lockerState = LockerState;

    unsigned int prepareStatus = FLASH_PrepareSector(SECTOR);

    if(prepareStatus ==0){
    FLASH_WriteData((void *)FLASH_START_ADDRESS, (void *)&startup, sizeof(startup));
    }
}

void loadStartupStateFromFlash(void){

    memcpy(&startup, (const void *)FLASH_START_ADDRESS, sizeof(startup));


    memcpy(currentAllowedCard.uidByte, startup.allowedCard, sizeof(startup.allowedCard));
    currentAllowedCard.size = startup.size;
    LockerState = startup.lockerState;

}*/
