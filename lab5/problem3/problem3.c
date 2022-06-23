/*
 * main.c
 *
 * author: Berkay Türk
 *
 * description:implement a PWM signal and drive an LED at at difrent speed
 * use keypad to set the duty cycle.
 * Pressing 10# will set the duty cycle to 10% and 90# will set the duty cycle to 90%.
 * Any unusal presses should be ignored. (i.e. 9F#)
 *
 */


#include "stm32g0xx.h"
#include "Bsp.h"


#define LEDDELAY    1600000U



void EXTI0_1_IRQHandler(void) {

	clearRowsKeypad();


}


void EXTI2_3_IRQHandler(void) {

	clearRowsKeypad();

}


void EXTI4_15_IRQHandler(void) {

	clearRowsKeypad();

	GPIOA->ODR ^= (1U << 9);  // PB9
	if((GPIOA->IDR >> 0) & 1 ){
		//#
	}

	GPIOA->ODR ^= (1U << 9);

	GPIOA->ODR ^= (1U << 5);  // PB5
	if((GPIOA->IDR >> 0) & 1 ){
		//9
	}

	 GPIOA->ODR ^= (1U << 5);

	 GPIOA->ODR ^= (1U << 4);  // PB4
	 if((GPIOA->IDR >> 0) & 1 ){
	    //1
	}

	 GPIOA->ODR ^= (1U << 4);

	 GPIOA->ODR ^= (1U << 3);  // PB3
	 if((GPIOA->IDR >> 0) & 1 ){
		//9
	}


  }


void TIM1_BRK_UP_TRG_COM_IRQHandler(void){

	init_timer1();
	BSP_led_toggle();
	TIM1->SR &= ~(1U << 0);
}

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


	BSP_System_init();

    while(1) {


    	TIM1_BRK_UP_TRG_COM_IRQHandler();
    	 _print(0, "Hello\n",6);
    	  delay_ms(10000);

    }

    return 0;
}
