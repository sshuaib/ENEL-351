#include "stm32f10x.h"
#include "init.h"

void delay(uint32_t delay)
{
  	 while (delay--)
	{
		}
}

void gpioInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	//led initializations
	
	GPIOB->CRH &= ~(GPIO_CRL_CNF1 | GPIO_CRH_CNF13 | GPIO_CRH_CNF14 | GPIO_CRH_CNF15); // clear CNF bits
	GPIOB->CRL &= ~(GPIO_CRL_CNF1);
	
	GPIOB->CRL |= GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1;	// set MODE bits
	
	GPIOB->CRH |= GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1 | //photoresistor LEDs
								GPIO_CRH_MODE14_0 | GPIO_CRH_MODE14_1 | 
								GPIO_CRH_MODE15_0 | GPIO_CRH_MODE15_1;
	
	GPIOC->CRH |=  GPIO_CRH_MODE8_0 |  GPIO_CRH_MODE8_1;	//soldered LED
	GPIOC->CRH &= ~GPIO_CRH_CNF8_0 &~ GPIO_CRH_CNF8_1;

	GPIOB->CRH |=  GPIO_CRH_MODE8_0 |  GPIO_CRH_MODE8_1;	//buzzer
	GPIOB->CRH &= ~GPIO_CRH_CNF8_0 &~ GPIO_CRH_CNF8_1;
	
	GPIOA->CRL |=  GPIO_CRL_MODE6_0 |  GPIO_CRL_MODE6_1;	//left motor (forward)
	GPIOA->CRL &= ~GPIO_CRL_CNF6_0 &~ GPIO_CRL_CNF6_1;

	GPIOA->CRL |=  GPIO_CRL_MODE7_0 |  GPIO_CRL_MODE7_1;	//left motor (backward)
	GPIOA->CRL &= ~GPIO_CRL_CNF7_0 &~ GPIO_CRL_CNF7_1;
	
	GPIOB->CRH |=  GPIO_CRH_MODE11_0 |  GPIO_CRH_MODE11_1;	//right motor(forward)
	GPIOB->CRH &= ~GPIO_CRH_CNF11_0 &~ GPIO_CRH_CNF11_1;
			
	GPIOB->CRH |=  GPIO_CRH_MODE12_0 |  GPIO_CRH_MODE12_1;	//right motor(backward)
	GPIOB->CRH &= ~GPIO_CRH_CNF12_0 &~ GPIO_CRH_CNF12_1;

}

void analogConfig(void)	//configure PA0 for analog input by clearing MODE and CNF bits of register
{
	GPIOA->CRL &= ~GPIO_CRL_MODE0_0 &~ GPIO_CRL_MODE0_1 &~ GPIO_CRL_CNF0_0 & ~GPIO_CRL_CNF0_1;
	ADC1->CR2 = 0x00000001;	//sets CR2 of ADC1 to 0x1 to enable ADC and begin conversion
}

int read_adc_value(void){	//reads value from analog sensor 
	int analog;
	ADC1->SQR3 = 0x00000000;	//sets CR3 of ADC1 to 0x0 which configures ADC to read from CH0
	ADC1->CR2 = 0x00000001;	//sets CR2 to 0x1 which enables ADC to start conversion
	
	while((ADC1->SR & 0x02) != 0x02){	//waits till end of conversion which is done by checking status register of ADC1 for EOC
	}
	
	analog = ADC1->DR;
	return analog;	//returns analog value
}

void led1ON(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR1;
	//GPIOA->BSRR = NUC_GREEN_ON;
}

void led1OFF(void)
{
	GPIOB->ODR &= ~ GPIO_ODR_ODR1;
	//GPIOA->BSRR = NUC_GREEN_OFF;
}
void led2ON(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR13;
	//GPIOA->BSRR = NUC_GREEN_ON;
}

void led2OFF(void)
{
	GPIOB->ODR &= ~ GPIO_ODR_ODR13;
	//GPIOA->BSRR = NUC_GREEN_OFF;
}
void led3ON(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR14;
	//GPIOA->BSRR = NUC_GREEN_ON;
}

void led3OFF(void)
{
	GPIOB->ODR &= ~ GPIO_ODR_ODR14;
	//GPIOA->BSRR = NUC_GREEN_OFF;
}
void led4ON(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR15;
	//GPIOA->BSRR = NUC_GREEN_ON;
}

void led4OFF(void)
{
	GPIOB->ODR &= ~ GPIO_ODR_ODR15;
	//GPIOA->BSRR = NUC_GREEN_OFF;
}

void solderedLEDON(void)
{
	GPIOC->ODR |= GPIO_ODR_ODR8;
}

void solderedLEDOFF(void)
{
	GPIOC->ODR &= ~GPIO_ODR_ODR8;
}

void buzzerON(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR8;
}

void buzzerOFF(void)
{
	GPIOB->ODR &= ~GPIO_ODR_ODR8;
}

void rightmotorforwardON(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR11;
}

void rightmotorforwardOFF(void)
{
	GPIOB->ODR &= ~GPIO_ODR_ODR11;
}

void rightmotorbackON(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR12;
}

void rightmotorbackOFF(void)
{
	GPIOB->ODR &= ~GPIO_ODR_ODR12;
}

void leftmotorforwardON(void)
{
	GPIOA->ODR |= GPIO_ODR_ODR6;
}

void leftmotorforwardOFF(void)
{
	GPIOA->ODR &= ~GPIO_ODR_ODR6;
}

void leftmotorbackON(void)
{
	GPIOA->ODR |= GPIO_ODR_ODR7;
}

void leftmotorbackOFF(void)
{
	GPIOA->ODR &= ~GPIO_ODR_ODR7;
}

