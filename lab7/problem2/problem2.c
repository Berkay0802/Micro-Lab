#include "bsp.h"
#include "time.h"
#include "math.h"
#include "stm32g0xx.h"



static volatile  uint32_t tick = 0;

void BSP_led_init(void) {

	 /* Enable GPIOA clock */  /* Enable GPIOB clock */
	     RCC->IOPENR |= (3U << 0);

	     /* Setup PA7 as output */
	         GPIOA->MODER &= ~(3U << 2*7);
	         GPIOA->MODER |= (1U << 2*7);

	         /* Clear led*/
	         GPIOA->BRR |= (1U << 7);


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
    tick = s;
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


void EXTI4_15_IRQHandler () {

	Counter++;
	EXTI->RPR1 |= (1U << 6);

}


void clearSSD(void) {

	/* Set all output connected to SSD (clear SSD)*/
	GPIOA->BRR |= (0x1A72);

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

	/*
			GPIOA->ODR |= (0x1);


			GPIOA->BRR |= (0x1);
	*/



		}
}



void setSSD(int x , int y) { // x is the number led(0 , 1)  Y is digit (SSD1 , SSD2)


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


void BSP_System_init() {

	__disable_irq();
	SystemCoreClockUpdate();
	BSP_led_init();
	SysTick_Config(SystemCoreClock / 1000);
	BSP_UART_init(9600);
    __enable_irq();
}


void init_adc() {
RCC->APBENR2 |= (10 << 20); //enable rcc for adc
RCC->IOPENR = (10 << 1); //enable GPIOB
//1/PB1 pin for adc in analog mode (by default)
ADC1->CR=0;
//1/reset adc cr
ADC1->CFGR1 = 0;
//1/reset adc cfgri
ADC1 ->CR |= (10 << 28); // Enable adc voltage regulator
delay(500);
//delay >20 us
//enable calibration, wait until completion
ADC1->CR |= (1U << 31); //1/calibration enable
while( !(ADC1->ISR & (1 << 11)));//Wait until EOCAL=1.
//enable end of cal. or sequence interrupts
//II ADC1->IER != (1U << 3); //end of conversion sequence interrupt
ADC1->IER |= (1U << 11); //end of calibration interrupt
//1/ select resolution [conf. bit sample (6,8,10,12)]
ADC1 ->CFGR1 |= (2U << 3);// ; 8bit
//1/conf. single/continuous;
ADC1->CFGR1 &= -(10 << 13);//cont=0;
ADC1->CFGR1 &= -(10 << 16);//discen =8; single
//1/select sampling time from SMPR
ADC1->SMPR = (0 << 0);//SMP1
// ADC1->SMPR |= (10 << 4);//SMP2
//1/select tim trgo
ADC1->CFGR1 != (3U << 6); //TGRO (extsel); 0xb011=3U for TIM3_TRGO
ADC1->CFGR1 |= (1U << 10); //Choose detect at rising edge (exten); 01
//enable channels (for the Anx pins)
ADC1->CFGR1 |= (9U << 26);//analog input channel 9; PB1
ADC1->CHSELR |= (1U << 9);//analog input channel 9; PB1
//Clear the ADRDY bit in ADC_ISR register by programming this bit to 1.
ADC1->ISR |= (1 << 0);
//enable adc and wait until it is ready
ADC1->CR |= (1 << 0);
while( !(ADC1->ISR & (1 << 0)));
//Start conversion
ADC1->CR |= (10 << 2);
NVIC_SetPriority_(ADC1_IRQn, 2); //Set priority to 2
}
