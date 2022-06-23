/*
 * problem1.c
 * main.c
 * author: Berkay Türk 171024024
 *
 * description: piano(tone play)
 *   G031K8 Nucleo board.
 */


#include "stm32g0xx.h"

#include "bsp.h"


#define LEDDELAY    1600000U


void init_timer1() {

	RCC->APBENR1 |= (1U << 1); // enable TIM3 module clock

	TIM3->CCR3 = 0; // Zero out the control register just in case
	TIM3->CR1 |= (1 << 7); // ARPE
	TIM3->CNT = 0; // Zero out counter
    TIM3->CCMR2 |= (111 << 16); // PWM Mode1
    TIM3->CCER |= (00 << 0); // capture / compare output

    /// 1  second interrupt
	TIM3->PSC = 999;
	TIM3->ARR = 1600;

	TIM3->DIER |= (1 << 0);  // update interrupt enable
	TIM3->CR1  |= (1 << 0);  // TIM1 Enable

    NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
    NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

}


/*
pulse_length = ((TIM_Period + 1) * DutyCycle);

where DutyCycle is in percent, between 0 and 100%

25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399

Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
*/


int main(void) {
	BSP_led_init();
	clearSSD();

	Keypad_enable();

       return 0;
}



