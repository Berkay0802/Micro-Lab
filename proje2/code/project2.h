#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"


/* Common API functions for nucleo */

void delay_ms(uint32_t);
void delay(volatile unsigned int);
void BSP_system_init();


void clearSSD(void);
void SwitchSSD(int );
void setSSD(int , int );

void Keypad_enable();

void EXTI4_15_IRQHandler(void );


void clearRowsKeypad(void);
void setRowsKeypad(void);

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
