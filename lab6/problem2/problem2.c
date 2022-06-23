#include "stm32g0xx.h"
#include "bsp.h"


static volatile  uint32_t tick = 0;

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


void USART_ISR(void) {

	uint8_t data = USART2->RDR;
	// RXNE is automatically cleared when read
}

/*
void UART_ISR(){
	uint8_t c = UART->DR;
	queue_enqueue(&rx_queue , c);
}*/

void USART2_IRQHandler(void){

	uint8_t data = (uint8_t)USART2->RDR;

	printChar(data);

}

void printChar(uint8_t c) {

	USART2->TDR = (uint16_t)c;
	while (!(USART2->ISR & (1 << 6)));
}

void _print(int fd , char *buf , int len) {

	(void)fd;
	for(int i=0; i<len; ++i) {
		printChar(buf[i]);
	}
}


void BSP_UART_init(uint32_t baud){

	/* setup PA2 as AF1 */
	RCC->IOPENR |= (1U << 0);
	RCC->APBENR1 |= (1U << 17);
   /*setup PA2 as AF1 */
	GPIOA->MODER &= ~(3U << 2*2);
	GPIOA->MODER |= (2 << 2*2);
   // choose Af1from mux
	GPIOA->AFR[0] &= ~(0xFU << 4*2);
	GPIOA->AFR[0] |= (1 << 4*2);
    // setup PA3 as AF1
	GPIOA->MODER &= ~(3U << 2*3);
	GPIOA->MODER |= (2 << 2*3);

   // Choose AF1 from mux
	GPIOA->AFR[0] &= ~(0xFU << 4*3);
	GPIOA->AFR[0] |= (1 << 4*3);

	USART2->CR1 = 0;
	USART2->CR1 |= (1 << 3);
	USART2->CR1 |= (1 << 2);
	USART2->CR1 |= (1 << 5);

	USART2->BRR =(uint16_t)(SystemCoreClock / baud);

	USART2->CR1 |= (1 << 0);

	NVIC_SetPriority(USART2_IRQn, 1);
	NVIC_EnableIRQ(USART2_IRQn);

}

void BSP_System_init() {

	__disable_irq();
	SystemCoreClockUpdate();
	BSP_led_init();
	SysTick_Config(SystemCoreClock / 1000);
	BSP_UART_init(9600);
    __enable_irq();
}
