/*
 * problem2.c
 * main.c
 * author: Berkay Türk 171024024
 *
 * description: read and write to sensor data
 *   G031K8 Nucleo board.
 */
#include "stm32g0xx.h"
#include "bsp.h"
#include "stdio.h"

#define MPU6050_ADDRESS 0X68

#define MPU6050_WHO_AM_I 0X75
#define MPU6050_PWR_MGMT_1 0X6B

#define MPU6050_ACCEL_XOUT_H 0X3B
#define MPU6050_ACCEL_XOUT_L 0X3C
#define MPU6050_ACCEL_YOUT_H 0X3D
#define MPU6050_ACCEL_XOUT_L 0X3E

#define MPU6050_GYRO_XOUT_H 0X43
#define MPU6050_GYRO_XOUT_L 0X44


#define LEDDELAY 1600000U


void init_I2C(void);


void I2C1_IRQHandler(void) {

	// only enters when error
}

void init_I2C(void) {

	GPIOB->MODER &= ~(3U << 2*8);
	GPIOB->MODER |= (2 << 2*8);
	GPIOB->OTYPER |= (1U << 8);
	// choose AF from mux
	GPIOB->AFR[1] &= ~(0XFU<< 4*0);
	GPIOB->AFR[1] |= (6 << 4*0);

	// setup PB9 as AF6
	GPIOB->MODER &= ~(3U << 2*9);
	GPIOB->MODER |= (2 << 2*9);
	GPIOB->OTYPER |= (1U << 9);
	// choose AF6 from mux
	GPIOB->AFR[1] &= ~(0XFU<< 4*1);
	GPIOB->AFR[1] |= (6 << 4*1);

    RCC->APBENR1 |= (1U << 21);

    I2C1->CR1 = 0;
    I2C1->CR1 |= (1U << 7); // ERRI

    I2C1->TIMINGR |= (3 << 28); // PRESC
    I2C1->TIMINGR |= (0x13 << 0); // SCLL
    I2C1->TIMINGR |= (0xF << 8); // SCLH
    I2C1->TIMINGR |= (0x2 << 16); // SDADEL
    I2C1->TIMINGR |= (0x4 << 20); // SCLDEL

    I2C1->CR1 = (1U << 0); // PF

    NVIC_SetPriority(I2C1_IRQn, 1);
    NVIC_EnableIRQ(I2C1_IRQn);

}

void read_I2C(uint8_t devAddr , uint8_t regAddr , uint8_t *data , uint32_t num) {

	//  Send address and register to read
	I2C1->CR2 = 0;
	I2C1->CR2 |= ((uint32_t)devAddr << 1); // slave address
	I2C1->CR2 |= (1U << 16); // Number of bytes
	I2C1->CR2 |= (1U << 13); // Generate Start
	while(!(I2C1->ISR & (1 << 1))); // TXIS
	I2C1->TXDR = (uint32_t)regAddr;

	while(!(I2C1->ISR & (1 << 6))); //TC

	// read data (READ OPERATİON)
	I2C1->CR2 = 0;
	I2C1->CR2 |= ((uint32_t)devAddr << 1);
	I2C1->CR2 |= (1U << 10); // READ mode
	I2C1->CR2 |= (num << 16); // Number of bytes
	I2C1->CR2 |= (1U << 15); // NACK
	I2C1->CR2 |= (1U << 25); // AUTOEND
	I2C1->CR2 |= (1U << 13); // Generate Start


	for(int i = 0; i<num; i++) {
	while(!(I2C1->ISR & (1 << 2))); // wait untl RXNE = 1

	}
}
/*
void enableMPU6050(uint16_t regAddr,uint8_t data){

	data[0]=I2C1->TXDR = (uint32_t)regAddr;//regADDRESS
    data[1]=(uint32_t)regAddr;//VALUE for regAddress
	//write 00 to Power management
	data[0]=MPU6050_PWR_MGMT_1;
	data[1]=0;
	write_general(MPU6050_ADDRESS,data,2);
}

void enableEEPROM(uint16_t regAddr,uint8_t data){
	data[0]=I2C1->CR2 | ((uint32_t)devAddr << 1);//regADDRESS high
    data[1]=I2C1->CR2 | ((uint32_t)devAddr << 0);//regAddress low
	data[2]=(uint32_t)regAddr;//value of regADDRESS
    data[3]=(uint32_t)regAddr;//VALUE for regAddress

	//write to address 0x100
	data[0]=1;
	data[0]=0x00;
	data[1]=0;
	write_general(EEPROM_ADDRESS,data,3);

}
*/

void write_I2C(uint8_t devAddr , uint16_t regAddr , uint8_t data) {


	//WRITE OPERATION (Send address and register to read)
	I2C1->CR2 = 0;
	I2C1->CR2 |= ((uint32_t)devAddr << 1);
	I2C1->CR2 |= (3U << 16); // Number of byte
	I2C1->CR2 |= (1U << 25); // AUTOEND
	I2C1->CR2 |= (1U << 13); // Generate Start

	while(!(I2C1->ISR & (1 << 1))); // TXIS
	I2C1->TXDR = (uint32_t)regAddr;

	while(!(I2C1->ISR & (1 << 1))); // TXIS
	I2C1->TXDR = (uint32_t)regAddr;

	while(!(I2C1->ISR & (1 << 1))); // TXIS
    I2C1->TXDR = (uint32_t)data;


}

void write_general(uint8_t devAddr , uint16_t num , uint8_t* data){

	//WRİTE OPERATION (Send address and register to read)
	I2C1->CR2 = 0;
	I2C1->CR2 |= ((uint32_t)devAddr << 1);//slave address
	I2C1->CR2 |= (3U << 16); // Number of byte
	I2C1->CR2 |= (1U << 25); // AUTOEND
	I2C1->CR2 |= (1U << 13); // Generate Start

	for(size_t i=0;i<num;++i){
		while(!(I2C1->ISR & (1 << 1))); // TXIS
		I2C1->TXDR = data[i];
	}
}


int main(void) {

	BSP_System_init();
    init_I2C();
    uint8_t data[10]; // stack , not zero , garbage data

    read_I2C(MPU6050_ADDRESS , MPU6050_WHO_AM_I , data , 1);
    printf("WHOAMI: %x\r\n",data[0]);


    read_I2C(MPU6050_ADDRESS , MPU6050_PWR_MGMT_1 , data , 1);
    printf("PWM MG: %x\r\n",data[0]);


    write_I2C(MPU6050_ADDRESS , MPU6050_PWR_MGMT_1, 0x00);
    delay_ms(1000);


    read_I2C(MPU6050_ADDRESS , MPU6050_PWR_MGMT_1 , data , 1);
    printf("PWM MG: %x\r\n",data[0]);


// trap
for(;;){
  delay_ms(10);
   read_I2C(MPU6050_ADDRESS , MPU6050_ACCEL_XOUT_L,data,2);
    uint32_t b =(uint32_t) data[0] | ((uint32_t)(data[1]) << 8);
   double a = (double)b / 131.0;
   printf("%x\r\n", a );

  }
    return 0;
}


