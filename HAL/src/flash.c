/*
 * @file   flash.c
 * @brief Contains the API that will deal with non volatile memory (Flash)
 * @version 1
 * @date 22 Nov 2023
 * @author Grupo 6
 */

#include "flash.h"
#include <stddef.h>

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#define ENDERECOIAP				0x1FFF1FF1UL
#define IAPCMD(a, b)			((void (*)())(ENDERECOIAP))(a, b)

void call_iap() {
	IAPCMD(iap_cmd, iap_result);
}

unsigned int FLASH_BlankCheck (unsigned int sector ){




    // Preparar a estrutura de comandos
    iap_cmd[0] = IAP_CMD_BLANK_CHECK_SECTORS;  // preparar o comando de apagar
    iap_cmd[1] = sector;
    iap_cmd[2] = sector;
    //iap_cmd[3] = SystemCoreClock / 1000;  // clock em khz


    call_iap();


    return iap_result[0];

}

unsigned int FLASH_PrepareSector (unsigned int sector ) {



    // Preparar a estrutura de comandos
    iap_cmd[0] = IAP_CMD_PREPARE_SECTORS;  // preparar o comando de apagar
    iap_cmd[1] = sector;
    iap_cmd[2] = sector;
    //iap_cmd[3] = SystemCoreClock / 1000;  // clock em khz


    call_iap();


    return iap_result[0];

}

unsigned int FLASH_EraseSector (unsigned int sector ) {



    // Preparar a estrutura de comandos
    iap_cmd[0] = IAP_CMD_ERASE_SECTORS;  // preparar o comando de apagar
    iap_cmd[1] = sector;
    iap_cmd[2] = sector;
    iap_cmd[3] = SystemCoreClock / 1000UL;  // clock em khz


    call_iap();


    return iap_result[0];

}

unsigned int FLASH_WriteData(void *dstAddr , void *srcAddr , unsigned int size ) {




    // Preparar a estrutura de comandos
    iap_cmd[0] = IAP_CMD_COPY_RAM_TO_FLASH;  // preparar o comando de escrever
    iap_cmd[1] = (unsigned int)dstAddr;
    iap_cmd[2] = (unsigned int)srcAddr;
    iap_cmd[3] = size;
    iap_cmd[4] = SystemCoreClock / 1000UL;


    call_iap();


    return iap_result[0];

}

unsigned int FLASH_VerifyData(void *dstAddr , void *srcAddr , unsigned int size ) {


    // Preparar a estrutura de comandos
    iap_cmd[0] = IAP_CMD_COMPARE;  // preparar para o comando compare
    iap_cmd[1] = (unsigned int)dstAddr;
    iap_cmd[2] = (unsigned int)srcAddr;
    iap_cmd[3] = size;
    iap_cmd[4] = SystemCoreClock / 1000;  // clock em khz


    call_iap();


    return iap_result[0];

}


/*
unsigned int calculate_padded_size(unsigned int size) {
    if (size <= 256) {
        return 256;
    } else if (size <= 512) {
        return 512;
    } else if (size <= 1024) {
        return 1024;
    } else {
        return 4096;
    }
}


void FLASH_padder(void *inputStruct, size_t structSize) {
    unsigned int paddedSize = calculate_padded_size(structSize);


    size_t paddingBytes = paddedSize - structSize;


    if (paddingBytes > 0) {

        unsigned char paddingArray[paddingBytes];


        unsigned char *structBytes = (unsigned char *)inputStruct;
        for (size_t i = 0; i < paddingBytes; ++i) {
            structBytes[structSize + i] = paddingArray[i];
        }
    }
}
*/
