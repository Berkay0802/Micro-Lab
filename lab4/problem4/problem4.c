/*
 * main.c
 *
 * author: Berkay Türk
 *
 * description: Create the Hard Fault Handler and some faults.
 */

#include "stm32g0xx.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define LEDDELAY    1600000

int main(void);
void delay(volatile uint32_t);

int random_number(int y){/*random int number but is go to HardFault*/

	srand(time(NULL));

   y=rand()%3;/* [0.2]*/

   return y;
   }


void HardFault_Handler () { /*if fault happend come to here*/

	Reset_Handler ();  /* go to reset*/
}

void Reset_Handler () { /*reset the system and open leds*/
      /*set stack pointer*/
	__asm("ldr r0 , =_estack");
	__asm("mov sp, r0");

	 GPIOA->ODR |= (1U << 7);/*turn on led*/
	 main();/*go to main*/
}

int main(void) {

    /* Enable GPIOA clock */  /* Enable GPIOB clock */
     RCC->IOPENR |= (3U << 0);

   /*  RCC->IOPENR |= (1U << 1); */

    /* Setup PA7 as output */
    GPIOA->MODER &= ~(3U << 2*7);
    GPIOA->MODER |= (1U << 2*7);

    /* Turn off LED */
    GPIOA->BRR |= (1U << 7);


    /* Setup PA6 as input */
    GPIOA->MODER &= ~(3U << 2*6);

    int random=0;/*manualy change the random number =0,1,2*/

    while(1) {

    	 if((GPIOA->IDR >> 6) & 1 ){/*button press*/

    		 //random= random_number(random); /*not working*/

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
    }

    	 else{/*not press button close led*/
    		 GPIOA->BRR |= (1U << 7);
    	 }
  }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
