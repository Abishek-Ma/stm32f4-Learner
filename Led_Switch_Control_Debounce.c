#include<stdint.h>

#define GPIOC_MODER (*(volatile unsigned int*)0x40020800)
#define GPIOC_IDR (*(volatile unsigned int*)0x40020810)
#define GPIOC_PUPDR (*(volatile unsigned int*)0x400208C0)

#define RCC_AHB1ENR (*(volatile unsigned int*)0x40023830)
#define GPIOA_MODER (*(volatile unsigned int*)0x40020000)
#define GPIOA_ODR (*(volatile unsigned int*)0x40020014)

#define SYST_CSR (*(volatile unsigned int*)0xE000E010)
#define SYST_RVR (*(volatile unsigned int*)0xE000E014)
#define SYST_CVR (*(volatile unsigned int*)0xE000E018)

void delay_ms(volatile uint32_t msec)
{
	SYST_RVR = 16000-1;
	SYST_CVR = 0;
	SYST_CSR |= ((1<<0) | (1<<2));

	for(volatile uint32_t i=0;i<msec;i++)
	{
		while((SYST_CSR & (1<<16))==0);
	}

	SYST_CSR=0;
}


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
			GPIOA_ODR ^= (1<<5);
			delay_ms(300);
		}

	}
}
