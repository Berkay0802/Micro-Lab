#include "stm32g0xx.h"
#include "bsp.h"

void led_init(void) {

	  /* Enable GPIOA clock */  /* Enable GPIOB clock */
	     RCC->IOPENR |= (3U << 0);
	  /* setup PA(0,1,4,5,6,8,9,11,12) for seven segment A,B,C,D,E,F,G,DH for bits in MODER */
	     GPIOA->MODER &= ~(0x3CF3F0F);
	     GPIOA->MODER |= (0x1451505);
	  /* setup PB(0,1,2,8) for seven segment D4,D3,D2,D1 for in MODER */
	     GPIOB->MODER &= ~(0x3003F);
	     GPIOB->MODER |= (0x10015);
}

// initialize on board connected to A7
void button_init() {
	 RCC->IOPENR |= (3U << 0);
	 GPIOA->MODER &= ~(3U << 2*7);
}

int button_read(){

	int b = ((GPIOA->IDR >> 7) & 0x0001);

	if (b) return 0;
	else return 1;
}

void delay_ms(volatile uint32_t s) {
    for(; s>0; s--);
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

void on_SSD1() {/* turn on SSD 1(LEFT).*/
	 /* turn on ODR*/
	GPIOB->ODR |= (0x100);
}
void off_SSD1() {/* turn off SSD 1(LEFT).*/
	 /* turn on ODR*/
	GPIOB->BRR |= (0x100);
}
void on_SSD2() {/* turn on SSD 2.*/
	 /* turn on ODR*/
	GPIOB->ODR |= (0x4);
}
void off_SSD2() {/* turn off SSD 2.*/
	 /* turn on ODR*/
	GPIOB->BRR |= (0x4);
}
void on_SSD3() {/* turn on SSD 3.*/
	 /* turn on ODR*/
	GPIOB->ODR |= (0x1);
}
void off_SSD3() {/* turn off SSD 3.*/
	 /* turn on ODR*/
	GPIOB->BRR |= (0x1);
}
void on_SSD4() {/* turn on SSD 4.*/
	 /* turn on ODR*/
	GPIOB->ODR |= (0x2);
}
void off_SSD4() {/* turn off SSD 4.*/
	 /* turn on ODR*/
	GPIOB->BRR |= (0x2);
}
void number_0() {
	 /* turn on led connected to A,B,C,D,E,F in ODR*/
	GPIOA->ODR |= (0x1A70);
	/* turn off led connected to G in ODR*/
	GPIOA->BRR |= (0x2);
}
void number_1() {
	 /* turn on led connected to B,C in ODR*/
	GPIOA->ODR |= (0x840);
	/* turn off led connected to A,D,E,F,G in ODR*/
	GPIOA->BRR |= (0x1232);
}
void number_2() {
	 /* turn on led connected to A,B,D,E,G in ODR*/
	GPIOA->ODR |= (0x1262);
	/* turn off led connected to C,F in ODR*/
	GPIOA->BRR |= (0x810);
}
void number_3() {
	 /* turn on led connected to A,B,C,D,G in ODR*/
	GPIOA->ODR |= (0x1A42);
	/* turn off led connected to E,F in ODR*/
	GPIOA->BRR |= (0x30);
}
void number_4() {
	 /* turn on led connected to B,C,G,F in ODR*/
	GPIOA->ODR |= (0x852);
	/* turn off led connected to A,D,E in ODR*/
	GPIOA->BRR |= (0x1220);
}
void number_5() {
	 /* turn on led connected to A,C,D,F,G in ODR*/
	GPIOA->ODR |= (0x1A12);
	/* turn off led connected to B,E in ODR*/
	GPIOA->BRR |= (0x60);
}
void number_6() {
	 /* turn on led connected to A,B,C,D,E,F,G in ODR*/
	GPIOA->ODR |= (0x1A32);
	/* turn off led connected to B in ODR*/
	GPIOA->BRR |= (0x40);
}
void number_7() {
	 /* turn on led connected to A,B,C in ODR*/
	GPIOA->ODR |= (0xA40);
	/* turn off led connected to D,E,F,G in ODR*/
	GPIOA->BRR |= (0x1032);
}
void number_8() {
	 /* turn on led connected to all in ODR*/
	GPIOA->ODR |= (0x1A72);

}
void number_9() {
	 /* turn on led connected to A,B,C,D,F,G in ODR*/
	GPIOA->ODR |= (0x1A52);
	/* turn off led connected to E in ODR*/
	GPIOA->BRR |= (0x20);
}

void turn_on_DH(){
	GPIOA->ODR |= (0x1);
}
void turn_off_DH(){
	GPIOA->BRR |= (0x1);
}


void zero_to_ten_SSD4(){
	        off_SSD1();
			off_SSD2();
			off_SSD3();
			on_SSD4();
			number_0();
			delay(1600);/*about 0.001 sec*/
			number_1();
			delay(1600);/*about 0.001 sec*/
			number_2();
			delay(1600);/*about 0.001 sec*/
			number_3();
			delay(1600);/*about 0.001 sec*/
			number_4();
			delay(1600);/*about 0.001 sec*/
			number_5();
			delay(1600);/*about 0.001 sec*/
			number_6();
			delay(1600);/*about 0.001 sec*/
			number_7();
			delay(1600);/*about 0.001 sec*/
			number_8();
			delay(1600);/*about 0.001 sec*/
			number_9();
			delay(1600);/*about 0.001 sec*/
			//number_0();
}
void fonksiyon(){
off_SSD1();
off_SSD2();
on_SSD3();
off_SSD4();
number_0();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_1();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_2();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_3();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_4();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_5();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_6();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_7();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_8();
delay(16000);
zero_to_ten_SSD4();
on_SSD3();
off_SSD4();
number_9();
delay(16000);
zero_to_ten_SSD4();

}
void fonksiyon2(){
	                off_SSD1();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_0();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_1();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_2();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_3();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_4();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_5();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_6();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_7();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_8();
		            delay(160000);
		            fonksiyon();
		            on_SSD2();
		            off_SSD3();
		            off_SSD4();
		            number_9();
		            delay(160000);
		            fonksiyon();

}
void fonksiyon3(){
	                    on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_0();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_1();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_2();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_3();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_4();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_5();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_6();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_7();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_8();
			            delay(1600000);
			            fonksiyon2();
			            on_SSD1();
			            off_SSD2();
			            off_SSD3();
			            off_SSD4();
			            number_9();
			            delay(1600000);
			            fonksiyon2();

}
