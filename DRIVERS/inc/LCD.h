/**
 * @file LCD.h
 * @brief contains the basic API for the Liquid Crystal Display peripheral
 * @version 1
 * @date 18 Oct 2023
 * @author Grupo 6
 */
#include <stdbool.h>
#include <stdint.h>

#ifndef LCD_H_
#define LCD_H_

#define LCD_Cursor 0b10000000 // define a posição do cursor
#define LCDText_LINES		0x28	/*!< LCD number of lines   */
#define LCDText_COLUMNS		16	/*!< LCD number of columns */
#define LCD_DIR 1
#define LCD_MODE_ON 0
#define RS_CMD 0 // para escrever comandos RS deve estar a 0
#define RS_DATA 1 // para escrever comandos RS deve estar a 1
//consoante a montagem enunciada  a seguir
#define RS_PIN 11
#define E_PIN 10
#define D4_PIN 64 //32*2 +0
#define D5_PIN 65
#define D6_PIN 66
#define D7_PIN 67 //32*2 +3

//comandos do lcd codificados em binário
#define LCD_Clear 0b00000001
#define LCD_Reset 0b0011
#define LCD_4bit 0b0010
#define LCD_EntryMode 0x28
#define LCD_DisplayON 0x08
#define LCD_DisplayConfig 0x06
#define LCD_AllOn 0b00001111
/* Montagem do LCD ao micro
 * DB0.. DB3  | Not connected
 * DB4 .. DB7 | P2.0 .. P2.3
 * E          | P0.10
 * RS         | P0.11
 * WR         |GND
 */


/**
 * @addtogroup DRIVERS
* @brief This package provides driver functions.
* @{
 */
/** @defgroup LCD LCD
* @brief Provides the core capabilities for the LCD.
* @{
* */
/**
 * @brief Writes a nibble into the LCD
 * @param rs: bit that decides if what is being written is a command or data
 * @param value: what's being written
 * @return none
 */
static void LCDText_WriteNibble(bool rs, uint8_t value);

/**
 * @brief Writes a byte into the LCD
 * @param rs: bit that decides if what is being written is a command or data
 * @param value: what's being written
 * @return none
 */
static void LCDText_WriteByte(int rs, unsigned char value);

/**
 * @brief Writes Data into the LCD
 * @param v: what's being written
 * @return none
 */
static void LCDText_WriteData(uint8_t v);

/**
 * @brief Writes a command into the LCD
 * @param v: what's being written
 * @return none
 */
static void LCDText_WriteCMD(uint8_t v);

/**
 * @brief Initializes the API for the LCD
 * @param: does not have any entry parameters
 * @return none
 * @note this function must be used before any other LCD function
 */
void LCDText_Init(void);


/**
 * @brief Writes a char into the LCD
 * @param ch: char to be written into the LCD
 * @return none
 */
void LCDText_WriteChar(char ch ) ;

/**
 * @brief Writes a string into the LCD
 * @param str: string to be written into the LCD
 * @return none
 */
void LCDText_WriteString (char *str ) ;

/**
 * @brief Locates the cursor
 * @param row: row to locate the cursor
 * @param column: column to locate the cursor
 * @return none
 */
void LCDText_SetCursor ( int row , int column ) ;

/**
 * @brief Clears the LCD
 * @param: does not have any entry parameters
 * @return none
 */
void LCDText_Clear(void) ;

/**
 * @brief Printf like the one in the C library
 * @param fmt : phrase to print
 * @param ... : variables that will be printed its value
 * @return none
 */
void LCDText_Printf (char *fmt , ...) ;
/**
 * @}
 */
/**
 * @}
 */

#endif /* LCD_H_ */
