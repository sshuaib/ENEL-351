#include "stdint.h"
#include "stm32f10x.h"

void delay(uint32_t delay);	// A delay loop which blocks while a value is decremented to 0
void gpioInit(void);		// intializing and configuring all LEDs

void analogConfig(void);	//configures ADC 
int read_adc_value(void);	//reads the analog input

void led1ON(void);	//simple turn on/off output functions
void led1OFF(void);
void led2ON(void);
void led2OFF(void);
void led3ON(void);
void led3OFF(void);
void led4ON(void);
void led4OFF(void);

void solderedLEDON(void);
void solderedLEDOFF(void);

void buzzerON(void);
void buzzerOFF(void);

void rightmotorforwardON(void);	//IN1 of motor driver
void rightmotorforwardOFF(void);
void rightmotorbackON(void);	//IN2 of motor driver
void rightmotorbackOFF(void);
	
void leftmotorforwardON(void);
void leftmotorforwardOFF(void);
void leftmotorbackON(void);	//IN3 of motor driver
void leftmotorbackOFF(void);	//IN4 of motor driver

#define NUC_GREEN_ON	0x00000020;
#define NUC_GREEN_OFF	0x00200000;
