/*
 * main.c
 *
 * author: Berkay Türk
 *
 * description: Set up a timer with lowest priority that will be used to toggle on-board LED at 1 second intervals.
 *  Change the blinking speed using an external button.
 *  Each button press should increase the blinking speed by 1 second up to a maximum of 10 seconds.
 */
#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    1600000U
int x=0;/*start value*/
void TIM1_BRK_UP_TRG_COM_IRQHandler(int x){


	BSP_led_toggle();
    init_timer1(x);
	TIM1->SR &= ~(1U << 0);

}

void init_timer1(int x) {

	RCC->APBENR2 |= (1U << 11); // enable TIM1 module clock

	TIM1->CCR1 = 0; // Zero out the control register just in case
	TIM1->CR1 |= (1 << 7); // ARPE
	TIM1->CNT = 0; // Zero out counter

    /// 1  second interrupt
	x=blinky_value(x);
	TIM1->PSC = 999+x;
	TIM1->ARR = 16000;

	TIM1->DIER |= (1 << 0);  // update interrupt enable
	TIM1->CR1  |= (1 << 0);  // TIM1 Enable

    NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
    NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

}

int main(void) {

	   SystemCoreClockUpdate();
	   BSP_button_init();
	   BSP_led_init();
	   init_timer1(x);
	   SysTick_Config(SystemCoreClock / 1000);

    while(1) {



    }

    return 0;
}
