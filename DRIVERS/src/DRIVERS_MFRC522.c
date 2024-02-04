/**
 * @file DRIVERS_MFRC522.c
 * @brief contains the basic API to deal with the MFRC522 controller, with the help its own library
 * @version 1
 * @date 02 Dec 2023
 * @author Grupo 6
 */

#include "DRIVERS_MFRC522.h"
#include "mfrc522.h"

void MFRC522_PreInit(void){


	SPI_Init();
	SPI_ConfigTransfer(nBits,Frqncy ,mode );
	PIN_Dir(RST_PIN, OUT);
	PIN_Dir(SS_PIN, OUT);

}


void MFRC522_Reset( bool assert ){

	if(assert){
     PIN_Clear (RST_PIN);
	}else{
	 PIN_Set(RST_PIN);
	}

}



void MFRC522_Select( bool assert ){

	if(assert){
     PIN_Clear (SS_PIN);
	}else{
	 PIN_Set(SS_PIN);
	}

}


uint8_t MFRC522_Transfer( uint8_t value ){

	unsigned short return_value = SPI_Transfer(value);
	return return_value;
}


void MFRC522_WaitMs( uint32_t millis ){

	return DELAY_Stopwatch(millis);

}
