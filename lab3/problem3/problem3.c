/*
 * main.c
 *
 * author: Berkay Türk
 *
 * description: connect two leds and two buttons and turn on/off high priority interrupt.
 */

#include "stm32g0xx.h"

#define LEDDELAY    16000000

int main(void);
void delay(volatile uint32_t);

void EXTI2_3_IRQHandler () {

	/* Setup for PB3 interrupt  */
	  GPIOA->BRR |= (1U << 11);  /* Turn off LED PA11 */
	  GPIOA->ODR |= (1U << 7);   /* Turn on LED PA7 */
	  delay(LEDDELAY);           /* Delay about 10 second*/
	  GPIOA->BRR |= (1U << 7);   /* Turn off LED PA7 */
	  GPIOA->ODR |= (1U << 11);  /* Turn on LED PA11 */

	  EXTI->RPR1 |= (1U << 3);

}

void EXTI4_15_IRQHandler () {

	/* Setup for PA6 interrupt  */
	   GPIOA->BRR |= (1U << 7);  /* Turn off LED PA7 */
	   GPIOA->ODR |= (1U << 11); /* Turn on LED PA11 */
	   delay(LEDDELAY);          /* Delay about 10 second*/
	   GPIOA->BRR |= (1U << 11); /* Turn off LED PA11 */
	   GPIOA->ODR |= (1U << 7);  /* Turn on LED PA7 */

	   EXTI->RPR1 |= (1U << 6);
}

int main(void) {

    /* Enable GPIOA clock */  /* Enable GPIOB clock */
     RCC->IOPENR |= (3U << 0);


    /* Setup PA7 as output */
    GPIOA->MODER &= ~(3U << 2*7);
    GPIOA->MODER |= (1U << 2*7);

    /* Setup PA11 as output */
    GPIOA->MODER &= ~(3U << 2*11);
    GPIOA->MODER |= (1U << 2*11);

    /* Turn on LED */
    GPIOA->ODR |= (1U << 7);  /*PA7 */
    GPIOA->ODR |= (1U << 11);  /*PA11*/


    /* Setup PA6 as input */
    GPIOA->MODER &= ~(3U << 2*6);

    /* Setup PB3 as input*/
    GPIOB->MODER &= ~(3U << 2*3);

/*   First interrupt is at PA6 second one is at PB3 */
   /* PA6 interrupt setup  */

    EXTI->RTSR1 |= (1U << 6);
    EXTI->EXTICR[1] |= (0U<< 8*2);
    EXTI->IMR1 |= (1U << 6);
    NVIC_SetPriority(EXTI4_15_IRQn , 0);
    NVIC_EnableIRQ(EXTI4_15_IRQn);

    /*  PB3 interrupt setup */
     EXTI->RTSR1 |= (1U << 3);
     EXTI->EXTICR[0] |= (1U<< 8*3);
     EXTI->IMR1 |= (1U << 3);
     NVIC_SetPriority(EXTI2_3_IRQn , 1);
     NVIC_EnableIRQ(EXTI2_3_IRQn);

    while(1) {

    }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
