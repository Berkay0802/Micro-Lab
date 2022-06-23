/*
 * problem1.c
 * main.c
 * author: Berkay Türk 171024024
 *
 * description: implementing a knock counter
 *   G031K8 Nucleo board.
 */

#include "stm32g0xx.h"
#include "bsp.h"
#include "stdio.h"

#define LEDDELAY 1600000U

int Counter = 0;
int main(void) {

	BSP_System_init();


	/*   First interrupt is at PA6 */

	    EXTI->RTSR1 |= (1U << 6);
	    EXTI->EXTICR[1] |= (0U<< 8*2);
	    EXTI->IMR1 |= (1U << 6);
	    NVIC_SetPriority(EXTI4_15_IRQn , 0);
	    NVIC_EnableIRQ(EXTI4_15_IRQn);

	    // trap
for(;;){

	setSSD(Counter , 0);

  }
    return 0;
}
