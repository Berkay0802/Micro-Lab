#include "bsp.h"
#include "time.h"
#include "math.h"
#include "stm32g0xx.h"


static volatile  uint32_t tick = 0;
int t=0;

void BSP_led_init(void) {

	 /* Enable GPIOA clock */  /* Enable GPIOB clock */
	     RCC->IOPENR |= (3U << 0);

	     /* Setup PA8 as output */
	         GPIOA->MODER &= ~(3U << 2*8);
	         GPIOA->MODER |= (1U << 2*8);

	         /* Clear led*/
	         GPIOA->BRR |= (1U << 8);

}

// initialize on board connected to A6
void BSP_button_init() {
	 RCC->IOPENR |= (3U << 0);
	 GPIOA->MODER &= ~(3U << 2*6);
}

int BSP_button_read(){

	int b = ((GPIOA->IDR >> 6) & 0x0001);

	if (b) return 0;
	else return 1;
}

void delay(volatile unsigned int s) {
    for(; s>0; s--);
}

void delay_ms(uint32_t s) {
    tick = 0;
    while(tick);
}
void BSP_led_set() {

	GPIOA->ODR |= (1U << 8);
}

void BSP_led_clear() {

	GPIOA->BRR |= (1U << 8);
}


void BSP_button_board() {

	GPIOA->BRR |= (1U << 6);
}


void BSP_led_toggle() {

	GPIOA->ODR ^= (1U << 8);
}

void SysTick_Handler(void) {

	if(tick > 0){

		--tick;
	}

}
