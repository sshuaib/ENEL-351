#include "stm32f10x.h"
#include "init.h"
#include "sysConfig.h"
#include "photoResistor.h"
#include "ultraSonic.h"

int main()
{
	 clockInitial();
	 gpioInit();
	 ultraSonicInit();
	 analogConfig();
	 //photoResistor(); //commenting this out will result in only the Ultrasonic and Motor functions activating
	 findDistance();	//commenting this out will result in only the Photoresistor function activating
}


