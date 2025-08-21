#include "stm32.h"

#define CLOCK_AHB1 (*((volatile unsigned int*)0x40023830))
#define CLOCK_APB2 (*((volatile unsigned int*)0x40023844))

volatile GPIO_t * const GPIOA = (GPIO_t*)0x40020000;
volatile ADC* const ADC1 = (ADC*)0x40012000;

int adc_value = 0;
int main()
{
	CLOCK_AHB1  |= (1<<0);
	CLOCK_APB2 |= (1<<8);
	GPIOA->MODER |=(3<<(2*1));
	GPIOA->MODER |=(1<<(2*5));
	GPIOA->ODR &=~(1<<5);

	ADC1->SMPR2 |= (7<<3);
	ADC1->SQR3 |= (1<<0);
//	ADC1->SQR1 |= (0<<19);
	ADC1->CR2 |= (1<<0);
	while(1)
	{
		ADC1->CR2 |=(1<<30);
		while(!(ADC1->SR & (1<<1)));
		adc_value = ADC1->DR;
		ADC1->SR &= ~(1<<1);
		if(adc_value < 50)
			GPIOA->ODR |=(1<<5);
	}
}