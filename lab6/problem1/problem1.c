#include "bsp.h"
#include "time.h"
#include "math.h"
#include "stm32g0xx.h"


static volatile  uint32_t tick = 0;
int t=0;

void BSP_led_init(void) {

	 /* Enable GPIOA clock */  /* Enable GPIOB clock */
	     RCC->IOPENR |= (3U << 0);

	 /* setup PA(0,1,4,5,6,8,9,11,12) for seven segment A,B,C,D,E,F,G,DH for bits in MODER */
	     GPIOA->MODER &= ~(0x3CF3F0F);
	     GPIOA->MODER |= (0x1451505);
	 /* setup PB(0,1,2,8) for seven segment D4,D3,D2,D1 for in MODER */
	     GPIOB->MODER &= ~(0x3003F);
	     GPIOB->MODER |= (0x10015);

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

void SysTick_Handler(void) {

	if(tick > 0){

		--tick;
	}

}



void EXTI4_15_IRQHandler(void) {   //INTERRUPT function
	clearSSD();

	if((EXTI->RPR1 >>6) & 1  ){/* Interrupt from PB6 */

	clearRowsKeypad();

	GPIOB->ODR ^= (1U << 9);  // PB9
	if((GPIOB->IDR >> 6) & 1 ){//'1'

		for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
		    setSSD(0 , 3);//0
	        delay(1600);//delay ms
	        setSSD(4 , 2);//4
	        delay(1600);//delay ms
	        setSSD(4 , 1);//4
	        delay(1600);//delay ms
	        setSSD(0 , 0);//0
	        delay(1600);//delay ms
		       if(retTime == 0)
		         break;
		  }
		     clearSSD();
		}
	}


	GPIOB->ODR ^= (1U << 9);

	GPIOB->ODR ^= (1U << 5);  // PB5
	if((GPIOB->IDR >> 6) & 1 ){//'4'
		for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
		    setSSD(0 , 3);//0
	        delay(1600);//delay ms
	        setSSD(4 , 2);//4
	        delay(1600);//delay ms
	        setSSD(8 , 1);//8
	        delay(1600);//delay ms
	        setSSD(0 , 0);//0
	        delay(1600);//delay ms
		       if(retTime == 0)
		         break;
		  }
		     clearSSD();

	}

	 GPIOB->ODR ^= (1U << 5);

	 GPIOB->ODR ^= (1U << 4);  // PB4
	 if((GPIOB->IDR >> 6) & 1 ){//'7'
			if(t==0){//First interrupt
				for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
				    setSSD(0 , 3);//0
			        delay(1600);//delay ms
			        setSSD(5 , 2);//5
			        delay(1600);//delay ms
			        setSSD(2 , 1);//2
			        delay(1600);//delay ms
			        setSSD(0 , 0);//0
			        delay(1600);//delay ms
				       if(retTime == 0)
				         break;
				  }
				     clearSSD();

	}

	 GPIOB->ODR ^= (1U << 4);

	 GPIOB->ODR ^= (1U << 3);  // PB3
	 if((GPIOB->IDR >> 6) & 1 ){//* 'E'
			for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
			    setSSD(0 , 3);//0
		        delay(1600);//delay ms
		        setSSD(5 , 2);//5
		        delay(1600);//delay ms
		        setSSD(6 , 1);//6
		        delay(1600);//delay ms
		        setSSD(0 , 0);//0
		        delay(1600);//delay ms
			       if(retTime == 0)
			         break;
			  }
			     clearSSD();

	}
	 GPIOB->ODR ^= (1U << 3);

	  EXTI->RPR1 |= (1U << 6);//Clear interrupt flag
	  setRowsKeypad();

}
	if((EXTI->RPR1 >>7) & 1 ){/* Interrupt from PB7 */

	clearRowsKeypad();

	GPIOB->ODR ^= (1U << 9);  // PB9
	if((GPIOB->IDR >> 7) & 1 ){//'2'
		for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
		    setSSD(0 , 3);//0
	        delay(1600);//delay ms
	        setSSD(6 , 2);//6
	        delay(1600);//delay ms
	        setSSD(0 , 1);//0
	        delay(1600);//delay ms
	        setSSD(0 , 0);//0
	        delay(1600);//delay ms
		       if(retTime == 0)
		         break;
		  }
		     clearSSD();

	}

	GPIOB->ODR ^= (1U << 9);

	GPIOB->ODR ^= (1U << 5);  // PB5
	if((GPIOB->IDR >> 7) & 1 ){//'5'
		for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
		    setSSD(0 , 3);//0
	        delay(1600);//delay ms
	        setSSD(6 , 2);//6
	        delay(1600);//delay ms
	        setSSD(4 , 1);//4
	        delay(1600);//delay ms
	        setSSD(0 , 0);//0
	        delay(1600);//delay ms
		       if(retTime == 0)
		         break;
		  }
		     clearSSD();

	}

	 GPIOB->ODR ^= (1U << 5);

	 GPIOB->ODR ^= (1U << 4);  // PB4
	 if((GPIOB->IDR >> 7) & 1 ){//'8'
			for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
			    setSSD(0 , 3);//0
		        delay(1600);//delay ms
		        setSSD(6 , 2);//6
		        delay(1600);//delay ms
		        setSSD(8 , 1);//8
		        delay(1600);//delay ms
		        setSSD(0 , 0);//0
		        delay(1600);//delay ms
			       if(retTime == 0)
			         break;
			  }
			     clearSSD();

	}

	 GPIOB->ODR ^= (1U << 4);

	 GPIOB->ODR ^= (1U << 3);  // PB3
	 if((GPIOB->IDR >> 7) & 1 ){//'0'
			for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
			    setSSD(0 , 3);//0
		        delay(1600);//delay ms
		        setSSD(7 , 2);//7
		        delay(1600);//delay ms
		        setSSD(2 , 1);//2
		        delay(1600);//delay ms
		        setSSD(0 , 0);//0
		        delay(1600);//delay ms
			       if(retTime == 0)
			         break;
			  }
			     clearSSD();

	}
	 GPIOB->ODR ^= (1U << 3);

	 EXTI->RPR1 |= (1U << 7); //Clear interrupt flag
		  setRowsKeypad();
	 }


	if((EXTI->RPR1 >> 15) & 1 ){/* Interrupt from PA15 */

	clearRowsKeypad();

	GPIOB->ODR ^= (1U << 9);  // PB9
	if((GPIOA->IDR >> 15) & 1 ){//'3'
		for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
		    setSSD(0 , 3);//0
	        delay(1600);//delay ms
	        setSSD(7 , 2);//7
	        delay(1600);//delay ms
	        setSSD(6 , 1);//6
	        delay(1600);//delay ms
	        setSSD(0 , 0);//0
	        delay(1600);//delay ms
		       if(retTime == 0)
		         break;
		  }
		     clearSSD();


	}

	GPIOB->ODR ^= (1U << 9);

	GPIOB->ODR ^= (1U << 5);  // PB5
	if((GPIOA->IDR >> 15) & 1 ){//'6'
		for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
		    setSSD(0 , 3);//0
	        delay(1600);//delay ms
	        setSSD(8 , 2);//8
	        delay(1600);//delay ms
	        setSSD(0 , 1);//0
	        delay(1600);//delay ms
	        setSSD(0 , 0);//0
	        delay(1600);//delay ms
		       if(retTime == 0)
		         break;
		  }
		     clearSSD();

	}

	 GPIOB->ODR ^= (1U << 5);

	 GPIOB->ODR ^= (1U << 4);  // PB4
	 if((GPIOA->IDR >> 15) & 1 ){//'9'
			for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
			    setSSD(0 , 3);//0
		        delay(1600);//delay ms
		        setSSD(8 , 2);//8
		        delay(1600);//delay ms
		        setSSD(4 , 1);//4
		        delay(1600);//delay ms
		        setSSD(0 , 0);//0
		        delay(1600);//delay ms
			       if(retTime == 0)
			         break;
			  }
			     clearSSD();


	}

	 GPIOB->ODR ^= (1U << 4);

	 GPIOB->ODR ^= (1U << 3);  // PB3
	 if((GPIOA->IDR >> 15) & 1 ){//#  'silence'
			for (unsigned int retTime = time(0) + 2000; time(0) < retTime; retTime--){   // Loop until it arrives.
			    setSSD(0 , 3);//0
		        delay(1600);//delay ms
		        setSSD(0 , 2);//0
		        delay(1600);//delay ms
		        setSSD(0 , 1);//0
		        delay(1600);//delay ms
		        setSSD(0 , 0);//0
		        delay(1600);//delay ms
			       if(retTime == 0)
			         break;
			  }
			     clearSSD();


	}
	 GPIOB->ODR ^= (1U << 3);

	 EXTI->RPR1 |= (1U << 15);//Clear interrupt flag
		  setRowsKeypad();
	 }


	if((EXTI->RPR1 >> 10) & 1 ){/* Interrupt from PA10 */

	clearRowsKeypad();

	GPIOB->ODR ^= (1U << 9);  // PB9
	if((GPIOA->IDR >> 10) & 1 ){//A nothing


	}

	GPIOB->ODR ^= (1U << 9);

	GPIOB->ODR ^= (1U << 5);  // PB5
	if((GPIOA->IDR >> 10) & 1 ){//B nothing


	}

	 GPIOB->ODR ^= (1U << 5);

	 GPIOB->ODR ^= (1U << 4);  // PB4
	 if((GPIOA->IDR >> 10) & 1 ){//C nothing



	}

	 GPIOB->ODR ^= (1U << 4);

	 GPIOB->ODR ^= (1U << 3);  // PB3
	 if((GPIOA->IDR >> 10) & 1 ){//D nothing


	}
	 GPIOB->ODR ^= (1U << 3);

	 EXTI->RPR1 |= (1U << 10);//Clear interrupt flag
		  setRowsKeypad();
	 }

 delay(800000);//wait 1 sec because interrups go same


  }






void Keypad_enable(){

/*   Setup Output pins (rows) */

	  GPIOB->MODER &= ~(3U << 2*9);  /// PB9 is output
	  GPIOB->MODER |= (1U << 2*9);


	  GPIOB->MODER &= ~(3U << 2*5);  /// PB5 is output
	  GPIOB->MODER |= (1U << 2*5);


	  GPIOB->MODER &= ~(3U << 2*4);  /// PB4 is output
	  GPIOB->MODER |= (1U << 2*4);


	  GPIOB->MODER &= ~(3U << 2*3);  /// PB3 is output
	  GPIOB->MODER |= (1U << 2*3);


	  /*   Setup Input pins (Columns)   */

	  GPIOB->MODER &= ~(3U << 2*6);  /// PB6 is input
	  GPIOB->PUPDR |= (2U << 2*6);   /// Pull-Down mode


	  GPIOB->MODER &= ~(3U << 2*7);  /// PB7 is input
	  GPIOB->PUPDR |= (2U << 2*7);    /// Pull-Down mode


	  GPIOA->MODER &= ~(3U << 2*15);  /// PA15 is input
	  GPIOA->PUPDR |= (2U << 2*15);    /// Pull-Down mode


	  GPIOA->MODER &= ~(3U << 2*10);  /// PA10 is input
	  GPIOA->PUPDR |= (2U << 2*10);    /// Pull-Down mode


	     /* Setup interrupts for inputs */
	  EXTI->EXTICR[1] |= (1U << 8*2);   // PB6
	  EXTI->EXTICR[1] |= (1U << 8*3);   // PB7
	  EXTI->EXTICR[3] |= (0U << 8*3);   // PA15
	  EXTI->EXTICR[2] |= (0U << 8*2);   // PA10


	  /* RISING Edge*/
	  EXTI->RTSR1 |= (1U << 6);      // 6th pin
	  EXTI->RTSR1 |= (1U << 7);      // 7th pin
	  EXTI->RTSR1 |= (1U << 15);      // 15th pin
	  EXTI->RTSR1 |= (1U << 10);      // 10th pin

	  /* MASK*/
	  EXTI->IMR1 |= (1U << 6);
	  EXTI->IMR1 |= (1U << 7);
	  EXTI->IMR1 |= (1U << 15);
	  EXTI->IMR1 |= (1U << 10);

	  /*NVIC */

	  NVIC_SetPriority(EXTI4_15_IRQn , 0);
	  NVIC_EnableIRQ(EXTI4_15_IRQn);


	     /* Setup all rows*/
    	 GPIOB->ODR |= (1U << 9);   /// PB9
    	 GPIOB->ODR |= (1U << 5);   /// PB5
    	 GPIOB->ODR |= (1U << 4);   /// PB4
    	 GPIOB->ODR |= (1U << 3);   /// PB3


     	 while(1){
             if(t==0){ // start value t=0 must be in
            	 clearSSD();//turn off SSD
              }

    }
}


void clearSSD(void) {//turn off SSD

	/* Set all output connected to SSD (clear SSD)*/
	GPIOA->BRR |= (0x1A73);

}

void SwitchSSD(int x) {


	switch (x)
		{

		case 0:

			 /* turn on led connected to A,B,C,D,E,F in ODR*/
			GPIOA->ODR |= (0x1A70);
			/* turn off led connected to G in ODR*/
			GPIOA->BRR |= (0x2);
			break;

		case 1:
			 /* turn on led connected to B,C in ODR*/
			GPIOA->ODR |= (0x840);
			/* turn off led connected to A,D,E,F,G in ODR*/
			GPIOA->BRR |= (0x1232);
			break;
		case 2:
			 /* turn on led connected to A,B,D,E,G in ODR*/
			GPIOA->ODR |= (0x1262);
			/* turn off led connected to C,F in ODR*/
			GPIOA->BRR |= (0x810);
			break;
		case 3:
			 /* turn on led connected to A,B,C,D,G in ODR*/
			GPIOA->ODR |= (0x1A42);
			/* turn off led connected to E,F in ODR*/
			GPIOA->BRR |= (0x30);
			break;
		case 4:
			 /* turn on led connected to B,C,G,F in ODR*/
			GPIOA->ODR |= (0x852);
			/* turn off led connected to A,D,E in ODR*/
			GPIOA->BRR |= (0x1220);
			break;

		case 5:
			 /* turn on led connected to A,C,D,F,G in ODR*/
			GPIOA->ODR |= (0x1A12);
			/* turn off led connected to B,E in ODR*/
			GPIOA->BRR |= (0x60);
			break;

		case 6:
			 /* turn on led connected to A,B,C,D,E,F,G in ODR*/
			GPIOA->ODR |= (0x1A32);
			/* turn off led connected to B in ODR*/
			GPIOA->BRR |= (0x40);
			break;
		case 7:
			 /* turn on led connected to A,B,C in ODR*/
			GPIOA->ODR |= (0xA40);
			/* turn off led connected to D,E,F,G in ODR*/
			GPIOA->BRR |= (0x1032);
			break;
		case 8:
			 /* turn on led connected to all in ODR*/
			GPIOA->ODR |= (0x1A72);
			break;

		case 9:
			 /* turn on led connected to A,B,C,D,F,G in ODR*/
			GPIOA->ODR |= (0x1A52);
			/* turn off led connected to E in ODR*/
			GPIOA->BRR |= (0x20);
			break;
		case 10://'-'
			 /* turn on led connected to G in ODR*/
			GPIOA->ODR |= (0x2);
			/* turn off led connected to A,B,C,D,E,F in ODR*/
			GPIOA->BRR |= (0x1A70);
            break;
		case 11://'H'
			/* turn on led connected to B,E,F,G in ODR*/
			GPIOA->ODR |= (0x872);
			/* turn off led connected to A,D in ODR*/
			GPIOA->BRR |= (0x1200);
            break;

		case 12://'.'
			GPIOA->ODR |= (0x1);
            break;
     /*
			GPIOA->BRR |= (0x1);//turn off '.'
	*/



		}
}



void setSSD(int x , int y) { // x is the number led(0 , 1)  Y is digit (SSD1 , SSD2)
	//clearSSD();


	if(y == 3){

		      /* turn on SSD 1(LEFT).*/
			 /* turn on ODR*/
			GPIOB->ODR |= (0x100);

		      /* turn off SSD 2.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x4);

		      /* turn off SSD 3.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x1);

		      /* turn off SSD 4.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x2);

			 SwitchSSD(x);
  }



	if(y == 2){

		      /* turn off SSD 1(LEFT).*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x100);

		      /* turn on SSD 2.*/
			 /* turn on ODR*/
			GPIOB->ODR |= (0x4);

		      /* turn off SSD 3.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x1);

		      /* turn off SSD 4.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x2);

			 SwitchSSD(x);
  }




	if(y == 1){

		      /* turn off SSD 1(LEFT).*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x100);

		      /* turn off SSD 2.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x4);

		      /* turn on SSD 3.*/
			 /* turn on ODR*/
			GPIOB->ODR |= (0x1);

		      /* turn off SSD 4.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x2);

			 SwitchSSD(x);
  }



	if(y == 0){

		      /* turn off SSD 1(LEFT).*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x100);

		      /* turn off SSD 2.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x4);

		      /* turn off SSD 3.*/
			 /* turn off ODR*/
			GPIOB->BRR |= (0x1);

		      /* turn on SSD 4.*/
			 /* turn on ODR*/
			GPIOB->ODR |= (0x2);

			 SwitchSSD(x);
  }


}

void clearRowsKeypad(void){
	     /* Clearing the rows here */
	      GPIOB->ODR &= ~(1U << 9);   /// PB9
	 	  GPIOB->ODR &= ~(1U << 5);   /// PB5
	 	  GPIOB->ODR &= ~(1U << 4);   /// PB4
	 	  GPIOB->ODR &= ~(1U << 3);   /// PB3
}


void setRowsKeypad(void){
         /* Setting the rows here   */
	 	  GPIOB->ODR |= (1U << 9);   /// PB9
	      GPIOB->ODR |= (1U << 5);   /// PB5
	 	  GPIOB->ODR |= (1U << 4);   /// PB4
	 	  GPIOB->ODR |= (1U << 3);   /// PB3

}


