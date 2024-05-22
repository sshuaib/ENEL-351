#include "stdint.h"
#include "stm32f10x.h"

void sleep_us(uint16_t sleep_time_us);
void sleep_ms(uint16_t sleep_time_ms);
void ultraSonicInit(void);
uint32_t findDistance(void);
