#include "stm32f10x.h"
#include "init.h"
#include "sysConfig.h"
#include "photoResistor.h"
#include "ultraSonic.h"
 
 void photoResistor(void)
 {
		while(1)	//
		{
		//range from 2.7V to 2.9V
		//Check if the voltage measured by the photoresistor is within a certain range (between 2.7V and 2.9V) using the read_adc_value() function.
		if ((read_adc_value() >= 0xD16) && (read_adc_value() <= 0xDDE))
		{
			led1ON();	//If the voltage is within the specified range, turn on the first LED and turn off the others.
			led2OFF();
			led3OFF();
			led4OFF();
			
		}
		//range from 2.9V to 3.1V
		if ((read_adc_value() > 0xDDE) && (read_adc_value() <= 0xEA6))
		{
			led1OFF();	//Repeat steps 2-3 for three more voltage ranges, each corresponding to a different LED.
			led2ON();
			led3OFF();
			led4OFF();
		}
		//range from 3.1V to 3.35V
		if ((read_adc_value() > 0xEA6) && (read_adc_value() <= 0xF6E))
		{
			led1OFF();
			led2OFF();
			led3ON();
			led4OFF();
		}
		//range from 3.35V to 3.7V
		if ((read_adc_value() > 0xF6E) && (read_adc_value() <= 0x103d))
		{
			led1OFF();
			led2OFF();
			led3OFF();
			led4ON();
		//If the voltage is not within any of the specified ranges, turn off all the LEDs.
		}
	}
}