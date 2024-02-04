/**
 * @file modes.h
 * @brief Provides functions for the modes of the application.
 * @version 1
 * @date 16 Dec 2023
 * @author Grupo 6
 */

#ifndef MODES_H_
#define MODES_H_


/**
 * @defgroup APP APP
* @brief This package contains the application.
* @{
 */

/** @defgroup MODES MODES
* @brief Provides functions for the modes of the application.
* @{
* */


#include "rtc.h"
#include <stdbool.h>
#include <string.h>



/**
 * @brief Function that runs normal mode of the app
 * @param dateTime: time struct that is given so the mode knows what is the current machine time
 * @return none
 */
void modoNormal(struct tm *dateTime);

/**
 * @brief Function that runs maintenance mode of the app
 * @param dateTime: time struct that is given so the mode knows what is the current machine time
 * @return none
 */
void modoManutencao(struct tm *dateTime);

/**
 * @brief Useful function to check if the read card is in the list of the authorized cards
 * @param uid: struct where we keep the data of the read card
 * @return the value of the comparison
 */
int isAuthorized(Uid uid);

/**
 * @brief Useful function to check if the read card is the one authorized to open the locker
 * @param uid: struct where we keep the data of the read card
 * @return the value of the comparison
 */
int isEqual(Uid uid);

/**
 * @brief Function to add a log to the log structs array
 * @param card: Card read that led to the creation of a log
 * @param authStatus: authorized status of the card read
 * @return none
 */
void addLogEntry(Uid card, int authStatus);

/**
 * @brief Displays the log sent by parameter
 * @param log: log to display
 * @return none
 */
void displayLog(LogsType log);

/**
 * @brief Removes a card from the authCards struct array given by the index
 * @param selectedIndex: index of the card to remove
 * @return none
 */
void removeCard(int selectedIndex);

/**
 * @brief Adds a card to the authCards struct
 * @param uidByte: attribute that tells us the identification of the card
 * @param size: size of the uidByte parameter (between 4,7,10)
 * @return none
 */
void addCard(uint8_t  uidByte[10], uint8_t size);

/**
 * @brief Function to write the startup struct to the flash
 * @param : none
 * @return none
 */
void saveStartupStateToFlash(void);

/**
 * @brief Function to load the startup struct from the flash
 * @param: none
 * @return none
 */
void loadStartupStateFromFlash(void);

/**
 * @brief Loads the loaded struct into the correct global variables
 * @param: none
 * @return none
 */
void loadStartup(void);

/**
 * @brief Saves the global variables into the startup struct
 * @param: none
 * @return none
 */
void saveStartup(void);

/**
 * @}
 */
/**
 * @}
 */


#endif /* MODES_H_ */
