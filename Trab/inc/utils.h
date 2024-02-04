/**
 * @file utils.h
 * @brief Contains various useful functions
 * @version 1
 * @date 12 Dez 2023
 * @author Grupo 6
 */

#ifndef UTILS_H
#define UTILS_H
#include <time.h>
#include "mfrc522.h"
#include <stdbool.h>
#include "string.h"

/**
 * @addtogroup APP
* @brief This package contains the application.
* @{
 */

/** @defgroup UTILS UTILS
* @brief Provides utils for the application.
* @{
* */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#define MAX_AUTH_CARDS 5
#define MAX_LOGS 10
// utils.h
#define FLASH_START_ADDRESS 0x00078000
#define FLASH_SECTOR_SIZE 32768  // 32KB
#define AUTH_CARDS_START_ADDRESS (FLASH_START_ADDRESS + 256)
#define STARTUP_STATE_RESTORE_ADDRESS  FLASH_START_ADDRESS
#define LOGS_START_ADDRESS (AUTH_CARDS_START_ADDRESS + 256 * MAX_AUTH_CARDS)
#define SECTOR 29

typedef struct {
	uint8_t    uidByte[10];
	uint8_t    size;
	uint8_t    padding[256 - 11];
} AuthCardsType;

typedef struct {
	uint8_t    uidByte[10];
	uint8_t    size;
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int lockerState;
    int authStatus;
    uint8_t    padding[512 - 34];
} LogsType;

typedef struct {
	uint8_t    allowedCard[10];
	uint8_t    size;
    int lockerState;
    int CardsCount;
	int LogsCount;
    uint8_t    padding[512 - 22];
} StartupStateRestoreType;

/**
 * @brief Useful function to deal with the various calendar days scenarios
 * @param year: year to check its scenarios
 * @param month: month to check its scenarios
 * @return the right number of days for the given month and year
 */
int numDays(int year, int month);

/**
 * @brief Useful function write the Calendar text
 * @param dateTime: time struct that tells the function what to print
 * @return none
 */
void textCalendar(struct tm *dateTime);

/**
 * @brief Useful function write the clock text
 * @param dateTime: time struct that tells the function what to print
 * @return none
 */
void textClock(struct tm *dateTime);

/**
 * @brief Useful function to set the Date
 * @param dateTime: time struct that tells the function current time in the machine
 * @return none
 */
void setDate(struct tm *dateTime );

/**
 * @brief Useful function to set the clock
 * @param dateTime: time struct that tells the function current time in the machine
 * @return none
 */
void setClock(struct tm *dateTime );
/*

AuthCardsType readAuthCardFromFlash(int index);

LogsType readLogsFromFlash(int index);

void writeLogsToFlash(int index, LogsType log);

void addLogToFlash(LogsType newLog);

void rebuildPointers(void);

void loadFromFlash(void);

void saveToFlash(void);

void saveStartupStateToFlash(StartupStateRestoreType startupState);

StartupStateRestoreType loadStartupStateFromFlash(void);

bool isAuth(Uid uid);

void loadStartup(StartupStateRestoreType *startup, bool *LockerState, Uid *currentAllowedCard);

void saveStartup(StartupStateRestoreType *startup, bool *LockerState, Uid *currentAllowedCard);
*/

/**
 * @}
 */
/**
 * @}
 */


#endif /* UTILS_H_ */
