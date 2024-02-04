/**
* @file   spi.c
 * @brief Contains the API that will deal with the SPI
 * @version 1
 * @date 29 Nov 2023
 * @author Grupo 6
 */

#include "spi.h"
#include "pin.h"
#include "pinconfig.h"

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

void SPI_Init ( void){

	PIN_settype(MOSI_PIN,THIRD_MODE);
	PIN_settype(MISO_PIN,THIRD_MODE);
	PIN_settype(SCK_PIN,THIRD_MODE);
	PIN_settype(SS_PIN,GPIO_MODE);
	PIN_settype(RST_PIN,GPIO_MODE);

	LPC_SC->PCONP |= 1<<PCSPI;
	LPC_SC->PCLKSEL0 &= ~(3<<PCLK_SPI);
	LPC_SC->PCLKSEL0 |= 1<<PCLK_SPI;

}

void SPI_ConfigTransfer(int bitData, int frequency , int mode){

	unsigned int div=SystemCoreClock/frequency;

	if(div & 0x1)++div;

	if(div<8) div=8;         //O valor da divisão não pode ser menor do que 8 pag 420

	//Página 418
	//CPOL é o bit 4, CPHA é o bit 3
	//Mode 0 -> CPOL=0 e CPHA=0
	//Mode 1 -> CPOL=0 e CPHA=1
	//Mode 2 -> CPOL=1 e CPHA=0
	//Mode 3 -> CPOL=1 e CPHA=1

	LPC_SPI->SPCCR=div;						//Tabela 361 e 365. Contador de 8 bits.(pag 417)

	bitData &= 0x0000000F;					//Máscara dos 4 bits menos significativos
	mode &= 0x00000003;

	LPC_SPI->SPCR = bitData<<BITS;			//Define o número de bits
	LPC_SPI->SPCR |= mode<<CPHA;			//Define o modo 0,1,2,3
	LPC_SPI->SPCR |= 1<<MSTR;				//Master
	LPC_SPI->SPCR |= 1<<BitEnable;			//para colocar os bits de dados



}

unsigned short SPI_Transfer(unsigned short value ) {


	LPC_SPI->SPDR = value;
	while(!(LPC_SPI->SPSR & 1<<SPIF));		//pag 419

	return LPC_SPI->SPDR;

}


