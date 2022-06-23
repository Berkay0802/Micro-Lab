/*
 * main.c
 *
 * author: Berkay Türk
 *
 * description: connect your board to the PC using UART protocol. For this you will need to create an
initialization routine for UART, and create send and receive functions.
 */
#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    1600000U

//Queue rx_queue;

int main(void) {

	BSP_System_init();
 //   queue_init(&rx_queue ,64);

	while(1) {
     _print(0,"Hello\n",6);
     delay_ms(10000);

  }
    return 0;
}
