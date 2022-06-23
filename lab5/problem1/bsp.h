#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"

/* Common API functions for nucleo */

void delay_ms(uint32_t);
void delay(volatile unsigned int);



void _print(int , char * , int );
void BSP_UART_init(uint32_t);
void printChar(uint8_t);
void BSP_System_init();



// LED related functions

void BSP_led_init();
void BSP_led_set();
void BSP_led_clear();
void BSP_led_toggle();



// Button related functions
void BSP_button_init();
int BSP_button_read();


#endif
