/*
 * main.c
 *
 * author: Berkay Türk
 *
 * description:  interrupt and hard fault creating
 */

#include "stm32g0xx.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"

#define LEDDELAY    16000000

int main(void);
void delay(volatile uint32_t);



void EXTI4_15_IRQHandler () {
	int random=0;/*manualy change the random number =0,1,2*/
	 // random=random_number(random);/*not working*/

	   /* Setup for PA6 interrupt  */
	   GPIOA->BRR |= (1U << 7);  /* Turn off LED PA7 */
	   delay(LEDDELAY);          /* Delay about 10 second*/
	   GPIOA->ODR |= (1U << 7);  /* Turn on LED PA7 */


	                if (random == 0) {
	    	    	__asm("ldr r6 , =#0x81000101");  /* Bus error invalid adress*/
	    	    	__asm("ldr r5 , [r6]");
	    	    	}

	    	    	if (random == 1) {/*not working*/
	                    int b=10;
	    	    		int a = b/0; /*divide by zero*/
	    	    	}

	    	    	if (random == 2) {

	    	    	 __asm("ldr r6 , =#0x80000101");   /*Big adress value*/
	    	    	 __asm("ldr r5 , [r6]");
	    	    	}

        EXTI->RPR1 |= (1U << 6);
}

int random_number(int y){/*random int number but is go to HardFault*/

	srand(time(NULL));

   y=rand()%3;/* [0.2]*/

   return y;
   }


void HardFault_Handler() { /*if fault happen come to here*/

	Reset_Handler ();  /* go to reset*/
}

void Reset_Handler() { /*reset the system and close led*/
      /*set stack pointer*/
	__asm("ldr r0 , =_estack");
	__asm("mov sp, r0");

	 GPIOA->BRR |= (1U << 7);/*close led*/
	 main(); /*go to main*/
}
int main(void) {

    /* Enable GPIOA clock */  /* Enable GPIOB clock */
     RCC->IOPENR |= (3U << 0);

    /* Setup PA7 as output */
    GPIOA->MODER &= ~(3U << 2*7);
    GPIOA->MODER |= (1U << 2*7);

    /* Turn on LED */
    GPIOA->ODR |= (1U << 7);  /*PA7 */

    /* Setup PA6 as input */
    GPIOA->MODER &= ~(3U << 2*6);


/*   interrupt is at PA6 interrupt setup  */

    EXTI->RTSR1 |= (1U << 6);
    EXTI->EXTICR[1] |= (0U<< 8*2);
    EXTI->IMR1 |= (1U << 6);
    NVIC_SetPriority(EXTI4_15_IRQn , 0);
    NVIC_EnableIRQ(EXTI4_15_IRQn);


    while(1) {

    }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
