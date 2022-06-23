/*
 * main.c
 *
 * author: Berkay Türk
 *
 * description: Counter counting from 01 to 10.
 */
#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    16000U

void EXTI4_15_IRQHandler () {
	        /*turn off led PA8*/
			GPIOA->BRR |= (1U << 8);
	        fonksiyon3();
	        on_SSD1();
	        on_SSD2();
			on_SSD3();
			on_SSD4();
			number_9();
			/*turn on led PA8*/
			GPIOA->ODR |= (1U << 8);
			turn_on_DH();
	   EXTI->RPR1 |= (1U << 7);
}



int main(void) {

	    led_init();
	    button_init();
	    /* PA7 interrupt setup  */

	    EXTI->RTSR1 |= (1U << 7);
	    EXTI->EXTICR[1] |= (0U<< 8*3);
	    EXTI->IMR1 |= (1U << 7);
	    NVIC_SetPriority(EXTI4_15_IRQn , 0);
	    NVIC_EnableIRQ(EXTI4_15_IRQn);

    while(1) {


  }

    return 0;
}
