/**
 * @file LCD.c
 * @brief contains the basic API for the Liquid Crystal Display peripheral
 * @version 1
 * @date 18 Oct 2023
 * @author Grupo 6
 */

#include "LCD.h"

#include "pin.h"
#include "pinconfig.h"
#include "DELAY.h"
#include <stdarg.h>


static void LCDText_WriteNibble(bool rs, uint8_t value) {

	value &= 0x0000000F;

	if(rs){
		PIN_Set(RS_PIN);
	}
	else{
		PIN_Clear(RS_PIN);
	}

	PIN_Set(E_PIN);
	//o seguinte troço de código poderia ser optimizado ao fazer uma PIN_Write function
	if ((value & 0b0001)!=0){
		PIN_Set(D4_PIN);
	}else{
		PIN_Clear(D4_PIN);
	}
	if ((value & 0b0010)!=0){
		PIN_Set(D5_PIN);
	}else{
		PIN_Clear(D5_PIN);
	}
	if ((value & 0b0100)!=0){
		PIN_Set(D6_PIN);
	}else{
		PIN_Clear(D6_PIN);
	}
	if ((value & 0b1000)!=0){
		PIN_Set(D7_PIN);
	}else{
		PIN_Clear(D7_PIN);
	}

	PIN_Clear(E_PIN);

}

static void LCDText_WriteByte(int rs, unsigned char value) {

	LCDText_WriteNibble(rs, value >> 4); //escreve os 4 bits mais significativos
	LCDText_WriteNibble(rs, value); //escreve os restantes 4 bits

}

static void LCDText_WriteData(uint8_t v){
	DELAY_Stopwatch(200);
	LCDText_WriteByte(RS_DATA, v);
}

static void  LCDText_WriteCMD(uint8_t v){
	DELAY_Stopwatch(200);
	LCDText_WriteByte(RS_CMD, v);
}


void LCDText_Init(void){

	PIN_settype(RS_PIN, LCD_MODE_ON);
	PIN_Dir(RS_PIN, LCD_DIR );

	PIN_settype(E_PIN, LCD_MODE_ON );
	PIN_Dir(E_PIN, LCD_DIR);

	PIN_settype(D4_PIN, LCD_MODE_ON);
	PIN_Dir(D4_PIN, LCD_DIR );

	PIN_settype(D5_PIN, LCD_MODE_ON);
	PIN_Dir(D5_PIN, LCD_DIR);

	PIN_settype(D6_PIN, LCD_MODE_ON);
	PIN_Dir(D6_PIN, LCD_DIR);

	PIN_settype(D7_PIN, LCD_MODE_ON);
	PIN_Dir(D7_PIN, LCD_DIR);

	DELAY_Stopwatch (16000); //para esperar mais que 15 milisegundos

	LCDText_WriteNibble(RS_CMD , LCD_Reset );
	DELAY_Stopwatch(4200); // para esperar mais que 4,1 milisegundos

	LCDText_WriteNibble(RS_CMD , LCD_Reset );
	DELAY_Stopwatch(200); //para esperar mais que 100 microsegundos

	LCDText_WriteNibble(RS_CMD , LCD_Reset );
	DELAY_Stopwatch(200);//para esperar mais que 100 microsegundos

	LCDText_WriteNibble(RS_CMD , LCD_4bit );
	DELAY_Stopwatch(50); // para esperar mais que 37 micros

	LCDText_WriteCMD(LCD_EntryMode);
	DELAY_Stopwatch(50);// para esperar mais que 37 micros

	LCDText_WriteCMD(LCD_DisplayON);
	DELAY_Stopwatch(50);// para esperar mais que 37 micros

	LCDText_WriteCMD(LCD_DisplayConfig);
	DELAY_Stopwatch(50);// para esperar mais que 37 micros

	LCDText_WriteCMD(LCD_AllOn);
	DELAY_Stopwatch(50);// para esperar mais que 37 micros

	LCDText_Clear();
	DELAY_Stopwatch(50);// para esperar mais que 37 micros
}

void LCDText_WriteChar(char ch ){
	int data = (int) ch;
	LCDText_WriteData(data);

}

void LCDText_WriteString (char *str ) {
	DELAY_Stopwatch(4200);
	for (int i = 0; str[i] != '\0'; i++ ){
		if (str[i] == '\n'){
			LCDText_SetCursor ( 2, 1);
		}
		else {
			LCDText_WriteChar(str[i]);
			DELAY_Stopwatch(4200);
		}
	}
}

void LCDText_SetCursor ( int row , int column ){

	int position;

	position = column-1+(row-1)*LCDText_LINES;
	position |= LCD_Cursor;
	DELAY_Stopwatch(4200);
	LCDText_WriteCMD(position);
	DELAY_Stopwatch(4200);
}

void LCDText_Clear(void){
	DELAY_Stopwatch(4200);
	LCDText_WriteCMD(LCD_Clear);
	DELAY_Stopwatch(4200);
}

void LCDText_Printf (char *fmt , ...){

	va_list ap;
	va_start(ap, fmt);
	char buffer[32];
	vsprintf(buffer, fmt, ap);
	va_end(ap);
	DELAY_Stopwatch(4200);
	LCDText_WriteString (buffer);
	DELAY_Stopwatch(4200);

}
