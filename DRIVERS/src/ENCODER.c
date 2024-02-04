/**
 * @file ENCODER.c
 * @brief Contains the API that will deal with the Rotary Encoder Switch
 * @version 1
 * @date 15 Nov 2023
 * @author Grupo 6
 */
#include <stdbool.h>
#include <stdint.h>
#include "ENCODER.h"
#include "timer.h"
#include "SYSTICK.h"
#define ENCODER_SWITCH_STEP (1 << 0)
#define ENCODER_SWITCH_DIRECTION (1 << 1)
#define ENCODER_SWITCHES (ENCODER_SWITCH_STEP | ENCODER_SWITCH_DIRECTION)

// Global variables
static volatile int delta = 0;
static volatile uint32_t last = 0;

static volatile uint32_t lastButtonCheck = 0;
static volatile uint32_t keyDownTicks = 0;
static volatile uint32_t doubleClickTicks = 0;
static volatile ENCODER_ButtonValueType button = BUTTON_NOTPRESSED;

static void RotaryEncoderRITHandler(void) {
    ENCODER_Handler();
}

void ENCODER_Handler(void){
	bool btn = !PIN_Check(SW_PIN);
	uint32_t now = DELAY_GetElapsedMillis(0);
	int current;
	uint32_t diff;
	RIT_Restart();
	current = ReadValues();
	diff = last - current;
	if (diff & ENCODER_SWITCH_STEP) {
		last = current;
		delta += (diff & ENCODER_SWITCH_DIRECTION) - 1;
	}
	if ((now - lastButtonCheck) >= ENCODER_BUTTONINTERVAL) {
			lastButtonCheck = now;
			if ((btn == true)) keyDownTicks++;
			else {
					if (keyDownTicks) {
							if (keyDownTicks > ENCODER_HOLD_TICKS)
									doubleClickTicks = 0;
							else {
								if (doubleClickTicks > 1) {
									if (doubleClickTicks < ENCODER_DCLICK_TICKS) {
										button = BUTTON_DCLICKED;
										doubleClickTicks = 0;

									}
								}
								else
									doubleClickTicks = ENCODER_DCLICK_TICKS;
							}
					}
					keyDownTicks = 0;
			}
			if (doubleClickTicks > 0) {
				doubleClickTicks -= 2;
				if (doubleClickTicks == 0)button = BUTTON_CLICKED;
			}

		}

}


void ENCODER_Init( int rate ){

	RIT_SetHandler(rate, ENCODER_Handler);
	RIT_Start();
	PIN_settype(SW_PIN, ENCODER_MODE_ON);
	PIN_Dir(SW_PIN, ENCODER_DIR );
	PIN_settype(DT_PIN, ENCODER_MODE_ON);
	PIN_Dir(DT_PIN, ENCODER_DIR );
	PIN_settype(CLK_PIN, ENCODER_MODE_ON);
	PIN_Dir(CLK_PIN, ENCODER_DIR );

}


int ENCODER_GetValue(void){


	int val;
	int res = 0;

	val = delta;
	delta = val & 3;

	val >>= 2;

	if(val <0){

		res -=1;
	}
	else if (val > 0){
		res += 1;
	}

	return res;

}



ENCODER_ButtonValueType ENCODER_GetButton(void){
	ENCODER_ButtonValueType temp = button;
	button = 0;
	return temp;
	/*
	bool btn = !PIN_Check(SW_PIN);
	uint32_t now = DELAY_GetElapsedMillis(0);

	//...
	if ((now - lastButtonCheck) >= ENCODER_BUTTONINTERVAL) {
		lastButtonCheck = now;
		if ((btn == true)) keyDownTicks++;
		else {
				if (keyDownTicks) {
						if (keyDownTicks > ENCODER_HOLD_TICKS)
								doubleClickTicks = 0;
						else {
							if (doubleClickTicks > 1) {
								if (doubleClickTicks < ENCODER_DCLICK_TICKS) {
									button = BUTTON_DCLICKED;
									doubleClickTicks = 0;

								}
							}
							else
								doubleClickTicks = ENCODER_DCLICK_TICKS;
						}
				}
				keyDownTicks = 0;
		}
		if (doubleClickTicks > 0) {
			doubleClickTicks -= 2;
			if (doubleClickTicks == 0)button = BUTTON_CLICKED;
		}

	}
*/
}

int ReadValues(void){

    bool clk = PIN_Check(CLK_PIN);

    bool dt = PIN_Check(DT_PIN);

    if((clk == 1) && (dt == 0)){
        return 1;
    }

    if((clk == 1) || (dt == 1)){
        return 2;
    }

    if((clk == 0) && (dt == 1)){
        return 3;
    }

    return 0;
}


