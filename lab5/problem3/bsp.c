#include "Bsp.h"

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


void USART_ISR(void) {

	uint32_t data = USART2->RDR;
	// RXNE is automatically cleared when read
}
/*
void UART_ISR(){
	uint8_t c = UART->DR;
	queue_enqueue(&rx_queue , c);
}
*/
void printChar(uint8_t c) {

	USART2->TDR = (uint16_t) c;
	while (!(USART2->ISR & (1 << 6)));
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


void USART_IRQHandler(void){

	uint8_t data = (uint8_t)USART2->RDR;

	printChar(data);

}

void _print(int fd , char *buf , int len) {

	(void)fd;
	for(int i=0; i<len; ++i) {
		printChar(buf[i]);
	}
}

void BSP_System_init() {

	__disable_irq();
	SystemCoreClockUpdate();
	BSP_led_init();
	SysTick_Config(SystemCoreClock / 1000);
	BSP_UART_init(115200);
    __enable_irq();
}

typedef struct Queue{
	uint8_t *data;

	uint16_t head;

	uint16_t tail;

	uint16_t size;
}Queue;


void uart_tx(uint8_t c) {


}

uint8_t uart_rx(void) {

}


/*
void queue_init(int) {

	typedef struct Queue;

   // queue.data = malloc( 100 * sizeof(uint8_t) );
	queue.head = 0;
	queue.tail = 0;
	queue.size = 64;

}
*/

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
	  GPIOB->MODER |= (2U << 2*6);   /// Pull-Down mode


	  GPIOB->MODER &= ~(3U << 2*7);  /// PB7 is input
	  GPIOB->MODER |= (2U << 2*7);    /// Pull-Down mode


	  GPIOA->MODER &= ~(3U << 2*15);  /// PA15 is input
	  GPIOA->MODER |= (2U << 2*15);    /// Pull-Down mode


	  GPIOA->MODER &= ~(3U << 2*10);  /// PA10 is input
	  GPIOA->MODER |= (2U << 2*10);    /// Pull-Down mode


	  EXTI->EXTICR[2] |= (1U << 8*2);   // PB6
	  EXTI->EXTICR[2] |= (1U << 8*3);   // PB7
	  EXTI->EXTICR[2] |= (0U << 8*3);   // PA15
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

	  NVIC_SetPriority(EXTI0_1_IRQn , 0);
	  NVIC_EnableIRQ(EXTI0_1_IRQn);

	  NVIC_SetPriority(EXTI2_3_IRQn , 0);
	  NVIC_EnableIRQ(EXTI2_3_IRQn);

	  NVIC_SetPriority(EXTI4_15_IRQn , 0);
	  NVIC_EnableIRQ(EXTI4_15_IRQn);



	  GPIOB->ODR |= (1U << 9);   /// PB9
	  GPIOB->ODR |= (1U << 5);   /// PB5
	  GPIOB->ODR |= (1U << 4);   /// PB4
	  GPIOB->ODR |= (1U << 3);   /// PB3

}



void clearRowsKeypad(void){
	     /* Clearing the rows here */
	      GPIOB->ODR &= (1U << 9);   /// PB9
	 	  GPIOB->ODR &= (1U << 5);   /// PB5
	 	  GPIOB->ODR &= (1U << 4);   /// PB4
	 	  GPIOB->ODR &= (1U << 3);   /// PB3
}


void setRowsKeypad(void){
         /* Setting the rows here   */
	 	  GPIOB->ODR |= (1U << 9);   /// PB9
	      GPIOB->ODR |= (1U << 5);   /// PB5
	 	  GPIOB->ODR |= (1U << 4);   /// PB4
	 	  GPIOB->ODR |= (1U << 3);   /// PB3
}

