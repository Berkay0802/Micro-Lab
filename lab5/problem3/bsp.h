#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"


/* Common API functions for nucleo */

void delay_ms(uint32_t);
void delay(volatile unsigned int);
void BSP_system_init();

void uart_tx(uint8_t c);
uint8_t uart_rx(void);

void _print(int , char * , int );
void BSP_UART_init(uint32_t);
void printChar(uint8_t);
void USART_ISR(void);
void BSP_System_init();
void clearRowsKeypad(void);
void setRowsKeypad(void);

void Keypad_enable();

void USART_IRQHandler(void);
void SysTick_Handler(void);

// LED related functions

void BSP_led_init();
void BSP_led_set();
void BSP_led_clear();
void BSP_led_toggle();



// Button related functions
void BSP_button_init();
int BSP_button_read();

#endif
