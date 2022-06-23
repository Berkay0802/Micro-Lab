#include "stm32g0xx.h"
#include "bsp.h"

void BSP_led_init(void) {

	 /* Enable GPIOA clock */  /* Enable GPIOB clock */
	     RCC->IOPENR |= (3U << 0);

	     /* Setup PA7 as output */
	         GPIOA->MODER &= ~(3U << 2*7);
	         GPIOA->MODER |= (1U << 2*7);

	         /* Clear led*/
	         GPIOA->BRR |= (1U << 7);
}

// initialize on board connected to A6
void BSP_button_init() {
	 RCC->IOPENR |= (3U << 0);
	 GPIOA->MODER &= ~(3U << 2*6);
}

int BSP_button_read(){

	int b = ((GPIOA->IDR >> 6) & 0x0001);

	if (b) return 1;
	else return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

void BSP_led_set() {

	GPIOA->ODR |= (1U << 7);
}

void BSP_led_clear() {

	GPIOA->BRR |= (1U << 7);
}


void BSP_button_board() {

	GPIOA->BRR |= (1U << 6);
}


void BSP_led_toggle() {

	GPIOA->ODR ^= (1U << 7);
}


int blinky_value(int x) {



	 /*int y=x;= 16000;about 1 sec*/
	int b = ((GPIOA->IDR >> 6) & 0x0001);

		if (b) {
			x = 999+x ;
		            if(x == 999*9)	{
			         x = 999;
			        return x;
		                       }
		            else {
			            return x;
		                 }
		     return x;
		        }
		else {
			return x;
		}

	}



/*
void BSP_system_init() {

	SystemCoreClockUpdate();
	BSP_led_init();
	BSP_button_init(); // ilk soru icin yok //
	SysTick_Config(SystemCoreClock / 1000);


}

*/


