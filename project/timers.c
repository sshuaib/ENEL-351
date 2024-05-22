#include "stm32f10x.h"
#include "init.h"
#include "sysConfig.h"
#include "photoResistor.h"
#include "ultraSonic.h"

void timer3setup(void){
    // Enable timer 3 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Set PWM mode 1 for CH1 and CH2
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;

    // Enable preload and fast enable for CH1 and CH2
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE | TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE;

    // Enable CH1 and CH2
    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;

    // Set prescaler to divide 24 MHz by 2400 (PSC+1), PSC_CLK = 10000 Hz, 1 count = 0.1 ms
    TIM3->PSC = 0x095F;

    // Set auto-reload value to 100 counts for 10 ms or 100 Hz
    TIM3->ARR = 100;

    // Set duty cycle to 50% for CH1 and CH2
    TIM3->CCR1 = 50;
    TIM3->CCR2 = 50;

    // Enable timer 3
    TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}