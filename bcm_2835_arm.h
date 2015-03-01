#ifndef __BCM_2835_ARM_H__
#define __BCM_2835_ARM_H__

#define SIZE_OF_EACH_REGISTER			(32)
#define NUMBER_OF_PINS_PER_REGISTER 	(10)
#define CONTROLLING_BITS_PER_PIN		(3)

typedef enum {
	Function_Mode_Input = 0b000,
	Function_Mode_Output = 0b001,
	Function_Mode_AlternateFunction0 = 0b100,
	Function_Mode_AlternateFunction1 = 0b101,
	Function_Mode_AlternateFunction2 = 0b110,
	Function_Mode_AlternateFunction3 = 0b111,
	Function_Mode_AlternateFunction4 = 0b011,
	Function_Mode_AlternateFunction5 = 0b010,
} Bcm2835GpioFunctionModes_t;


typedef struct {

	//GPIO Function Select registers
	uint32_t GPFSEL[6];
	uint32_t Reserved1;

	//GPIO Pin Output Set registers
	uint32_t GPSET[2];
	uint32_t Reserved2;

	//GPIO Pin Output Clear registers
	uint32_t GPCLR[2];
	uint32_t Reserved3;

	//GPIO Pin Level registers
	uint32_t GPLEV[2];
	uint32_t Reserved4;

	//GPIO Pin Event Detect Status registers
	uint32_t GPEDS[2];
	uint32_t Reserved5;

	//GPIO Pin Rising Edge Detect Enable registers
	uint32_t GPREN[2];
	uint32_t Reserved6;

	//GPIO Pin Falling Edge Detect Enable registers
	uint32_t GPFEN[2];
	uint32_t Reserved7;

	//GPIO Pin High Detect Enable registers
	uint32_t GPHEN[2];
	uint32_t Reserved8;

	//GPIO Pin Low Detect Enable registers
	uint32_t GPLEN[2];
	uint32_t Reserved9;

	//GPIO Pin Async. Rising Edge Detect registers
	uint32_t GPAREN[2];
	uint32_t Reserved10;

	//GPIO Pin Async. Falling Edge Detect registers
	uint32_t GPAFEN[2];
	uint32_t Reserved11;

	//GPIO Pin Pull-up/down Enable register
	uint32_t GPPUD;	

	//GPIO Pin Pull-up/down Enable Clock registers
	uint32_t GPPUDCLK[2];
	uint32_t Reserved12;
} Bcm2835GpioRegisters_t;


#endif