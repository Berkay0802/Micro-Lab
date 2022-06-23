/*
 * main.c
 *
 * author: Berkay Türk
 *
 * description: Create a SysTick exception with 1 millisecond interrupt intervals.
 * Then create a delay_ms(..) function.
 */
#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    16000U


void TIM1_BRK_UP_TRG_COM_IRQHandler(void){

	BSP_led_set();
	 delay_ms(LEDDELAY);/*wait 1 millisecond*/
	TIM1->SR &= ~(1U << 0);
}

void init_timer1() {

	RCC->APBENR2 |= (1U << 11); // enable TIM1 module clock

	TIM1->CCR1 = 0; // Zero out the control register just in case
	TIM1->CR1 |= (1 << 7); // ARPE
	TIM1->CNT = 0; // Zero out counter

    /// 1 millisecond interrupt
	TIM1->PSC = 0;
	TIM1->ARR = 16000;

	TIM1->DIER |= (1 << 0);  // update interrupt enable
	TIM1->CR1  |= (1 << 0);  // TIM1 Enable

    NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
    NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

}


int main(void) {

	BSP_system_init();

    init_timer1();
    while(1) {

     BSP_led_set();



  }

    return 0;
}
