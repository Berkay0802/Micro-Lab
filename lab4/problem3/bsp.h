#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"

/* Common API functions for nucleo */

void delay_ms(volatile uint32_t s);
void delay(volatile uint32_t s);


// LED related functions
void led_init();
void on_SSD1();
void off_SSD1();
void on_SSD2();
void off_SSD2();
void on_SSD3();
void off_SSD3();
void on_SSD4();
void off_SSD4();

void number_0();
void number_1();
void number_2();
void number_3();
void number_4();
void number_5();
void number_6();
void number_7();
void number_8();
void number_9();

void turn_on_DH();
void turn_off_DH();

// Button related functions
void button_init();
int button_read();

void zero_to_ten_SSD4();
void fonksiyon();
void fonksiyon2();
void fonksiyon3();
#endif
