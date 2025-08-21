#include<stdint.h>
 
#define GPIOC_MODER (*(volatile unsigned int*)0x40020800)
#define GPIOC_IDR (*(volatile unsigned int*)0x40020810)
#define GPIOC_PUPDR (*(volatile unsigned int*)0x400208C0)
 
#define RCC_AHB1ENR (*(volatile unsigned int*)0x40023830)
#define GPIOA_MODER (*(volatile unsigned int*)0x40020000)
#define GPIOA_ODR (*(volatile unsigned int*)0x40020014)
 
 
int main()
{
	RCC_AHB1ENR |= (1<<0)|(1<<2);
	GPIOC_MODER &= ~(3<<(13*2));
	GPIOC_PUPDR |= (1<<(13*2));
 
 
	GPIOA_MODER &= ~(3<<(5*2));
	GPIOA_MODER |= (1<<(5*2));
 
	while(1)
	{
		if(!(GPIOC_IDR & (1<<13)))
		{
			GPIOA_ODR |= (1<<5);
		}
		else
		{
			GPIOA_ODR &= ~(3<<5);
		}
	}
}