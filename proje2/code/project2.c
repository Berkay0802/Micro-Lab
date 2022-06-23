/*
 * proje2.c
 * main.c
 * author: Berkay Türk 171024024
 *
 * description: calculator
 *   G031K8 Nucleo board.
 */


#include "stm32g0xx.h"

#include "bsp.h"


#define LEDDELAY    1600000U




int main(void) {
	BSP_led_init();
	clearSSD();

	Keypad_enable();

       return 0;
}



