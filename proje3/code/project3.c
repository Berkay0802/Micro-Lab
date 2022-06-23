/*
 * main.c
 *
 * author: Berkay Türk 171024024
 *
 * description: In this project, make a digital voice recorder.
 *   G031K8 Nucleo board.
 */

#include "stm32g0xx.h"
#include "time.h"
#include "stdio.h"
#include "bsp.h"


#define LEDDELAY 1600000U

int main(void) {

	BSP_System_init();
	init_adc() ;
	init_timer1();
    init_I2C();

for(;;){

	Keypad_enable();

  }
    return 0;
}
