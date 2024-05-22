#include "stm32f10x.h"
#include "init.h"
#include "sysConfig.h"
#include "photoResistor.h"
#include "ultraSonic.h"

void sleep_us(uint16_t sleep_time_us)
{
	if(sleep_time_us <= 1){ sleep_time_us = 2;}	//workaround for inputs of 0 and 1
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable TIM2 clock
	TIM2->PSC	= 24 - 1;	// Set counter clk to 1 MHz, function has 1 us resolution
	TIM2->ARR = sleep_time_us - 1;
	TIM2->EGR |= TIM_EGR_UG;
	TIM2->SR &= ~TIM_SR_UIF;
	TIM2->CR1 |= TIM_CR1_DIR | TIM_CR1_OPM | TIM_CR1_CEN; //Enable down counting and one pulse mode
	while ((TIM2->SR & TIM_SR_UIF) != TIM_SR_UIF); // wait for completion
	//TIM2->CR1 &= ~TIM_CR1_CEN;
//	TIM2->SR = 0;
//	TIM2->CR1 = 1;
//	while ((TIM2->SR & 1) == 0);
//	TIM2->CR1 = 0;
}	

void sleep_ms(uint16_t sleep_time_ms)
{
	if(sleep_time_ms <= 1){ sleep_time_ms = 2;}	//workaround for inputs of 0 and 1
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable TIM2 clock
	TIM2->PSC	= 24000 - 1;	// Set counter clk to 1 KHz, function has 1 ms resolution
	TIM2->ARR = sleep_time_ms - 1;
	TIM2->EGR |= TIM_EGR_UG;
	TIM2->SR &= ~TIM_SR_UIF;
	TIM2->CR1 |= TIM_CR1_DIR | TIM_CR1_OPM | TIM_CR1_CEN;
	while ((TIM2->SR & TIM_SR_UIF) != TIM_SR_UIF);
	//TIM2->CR1 &= ~TIM_CR1_CEN;
}	

void ultraSonicInit(void)
{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		
		GPIOC->CRH |=  GPIO_CRH_MODE10_0 |  GPIO_CRH_MODE10_1;	//configuring TRIG pin
		GPIOC->CRH &= ~GPIO_CRH_CNF10_0 &~ GPIO_CRH_CNF10_1;
			
		GPIOC->CRH &= ~GPIO_CRH_MODE11_0 &~ GPIO_CRH_MODE11_1 & ~GPIO_CRH_CNF11_0;	//configuring ECHO pin
		GPIOC->CRH |= GPIO_CRH_CNF11_1;
}

uint32_t findDistance(void)
{
	while(1)	//Enter an infinite while loop that continuously measures the distance and updates the behavior of the robot.
	{
	int distance = 10;	//Set a threshold distance of 40 cm (stored in the "distance" variable).

	GPIOC->ODR |= GPIO_ODR_ODR10;	//setting the TRIG pin high (ON)
	sleep_us(10);	//Wait for 10 microseconds using the sleep_us() function.
	
	GPIOC->ODR &= ~GPIO_ODR_ODR10;	//setting ECHO pin low (OFF)

	int counter = 0;
	while((GPIOC->IDR & GPIO_IDR_IDR11) == 0)	//Enter a while loop that waits for the ECHO pin of the ultrasonic sensor (connected to pin PC11) to go high.
	{
	}	
	while ((GPIOC->IDR & GPIO_IDR_IDR11) == GPIO_IDR_IDR11)	//Enter a second while loop that increments a counter for every microsecond that the ECHO pin stays high.
	{
		counter++;
	}

	float range = 0;
	range	= counter/47;	//Compute the distance in centimeters by dividing the counter by 47 (a conversion factor determined empirically).
	counter = 0;	//Reset the counter and wait for 100 milliseconds using the sleep_ms() function.
	sleep_ms(100);

	if (range <= distance)	//If the measured distance is less than or equal to the threshold distance, turn on a buzzer, turn off a soldered LED, and set the motors to drive backwards.
		{
			buzzerON();	// buzzer on
			solderedLEDOFF();
			rightmotorforwardOFF();
			rightmotorbackON();
			//delay(100);
			leftmotorforwardOFF();
			leftmotorbackON();
		}
	else	//If the measured distance is greater than the threshold distance, turn off the buzzer, turn on the soldered LED, and set the motors to drive forwards.
		{
			buzzerOFF();	//buzzer off
			solderedLEDON();	
			rightmotorforwardON();
			rightmotorbackOFF();
			leftmotorforwardON();
			leftmotorbackOFF();
		}
	}
}
