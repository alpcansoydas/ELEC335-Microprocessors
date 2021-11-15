/*
 * main.c
 *
 */

#include "stm32g0xx.h"

#define DELAY    1600000

void delay(volatile uint32_t);
void gpio_config(void);
void clock_config(void);
void EXTI_config(void);
void EXTI0_IRQHandler(void);
void read(void);
void number0(void);
void number1(void);
void number2(void);
void number3(void);
void number4(void);
void number5(void);
void number6(void);
void number7(void);
void number8(void);
void number9(void);

int main(void)
{
	clock_config();
	EXTI_config();
	gpio_config();



    while(1)
    {
    //	read();
    }

    return 0;
}
void clock_config(void)
{
    /* Enable GPIOA and GPIOB clock */
    RCC->IOPENR |= (1U << 0);
    RCC->IOPENR |= (1U << 1);
    RCC->APBENR2 = 0x1;
}
void EXTI_config(void)
{
	NVIC_EnableIRQ(EXTI_RTSR1_RT0);
	NVIC_EnableIRQ(EXTI_RTSR1_RT1);
	NVIC_EnableIRQ(EXTI_RTSR1_RT2);
	NVIC_EnableIRQ(EXTI_RTSR1_RT3);
	NVIC_EnableIRQ(EXTI_RTSR1_RT4);
	/*NVIC_EnableIRQ(EXTI_RTSR1_RT5);
	NVIC_EnableIRQ(EXTI_RTSR1_RT6);
	NVIC_EnableIRQ(EXTI_RTSR1_RT7);
	NVIC_EnableIRQ(EXTI_RTSR1_RT8);
	NVIC_EnableIRQ(EXTI_RTSR1_RT9);
	NVIC_EnableIRQ(EXTI_RTSR1_RT10);
*/
    EXTI->RTSR1 = 0x3FF;
}
void gpio_config(void)
{
	/* Setup PA0 as output */
	GPIOA->MODER &= ~(3U << 2*0);
	GPIOA->MODER |= (1U << 2*0);
	/* Setup PA1 as output */
	GPIOA->MODER &= ~(3U << 2*1);
	GPIOA->MODER |= (1U << 2*1);
	/* Setup PA4 as output */
	GPIOA->MODER &= ~(3U << 2*4);
	GPIOA->MODER |= (1U << 2*4);
	/* Setup PA5 as output */
	GPIOA->MODER &= ~(3U << 2*5);
	GPIOA->MODER |= (1U << 2*5);
	/* Setup PA6 as output */
	GPIOA->MODER &= ~(3U << 2*6);
	GPIOA->MODER |= (1U << 2*6);
	/* Setup PA7 as output */
	GPIOA->MODER &= ~(3U << 2*7);
	GPIOA->MODER |= (1U << 2*7);
	/* Setup PA8 as output */
	GPIOA->MODER &= ~(3U << 2*8);
	GPIOA->MODER |= (1U << 2*8);
	/* Setup PA9 as output */
	GPIOA->MODER &= ~(3U << 2*9);
	GPIOA->MODER |= (1U << 2*9);
	/* Setup PA10 as output */
	GPIOA->MODER &= ~(3U << 2*10);
	GPIOA->MODER |= (1U << 2*10);
	/* Setup PA11 as output */
	GPIOA->MODER &= ~(3U << 2*11);
	GPIOA->MODER |= (1U << 2*11);
	/* Setup PA12 as output */
	GPIOA->MODER &= ~(3U << 2*12);
	GPIOA->MODER |= (1U << 2*12);

	/* Setup PB0 as input */
	GPIOB->MODER &= ~(3U << 2*0);
	/* Setup PB1 as input */
	GPIOB->MODER &= ~(3U << 2*1);
	/* Setup PB2 as input */
	GPIOB->MODER &= ~(3U << 2*2);
	/* Setup PB3 as input */
	GPIOB->MODER &= ~(3U << 2*3);
	/* Setup PB4 as output */
	GPIOB->MODER &= ~(3U << 2*4);
	GPIOB->MODER |= (1U << 2*4);
	/* Setup PB5 as output */
	GPIOB->MODER &= ~(3U << 2*5);
	GPIOB->MODER |= (1U << 2*5);
	/* Setup PB6 as output */
	GPIOB->MODER &= ~(3U << 2*6);
	GPIOB->MODER |= (1U << 2*6);
	/* Setup PB7 as output */
	GPIOB->MODER &= ~(3U << 2*7);
	GPIOB->MODER |= (1U << 2*7);
}

/*void read ()
{

	if(GPIOB->IDR ==0x1 &&GPIOB->ODR==0x10)
		{
		EXTI_RTSR1_RT0_IRQHandler();
		}
	if(GPIOB->IDR ==0x1 &&GPIOB->ODR==0x20)
		{
		EXTI_RTSR1_RT1_IRQHandler();
		}
	if(GPIOB->IDR ==0x1 &&GPIOB->ODR==0x30)
		{
		EXTI_RTSR1_RT2_IRQHandler();
		}
	if(GPIOB->IDR ==0x1 &&GPIOB->ODR==0x40)
		{
		EXTI_RTSR1_RT3_IRQHandler();
		}

	if(GPIOB->IDR ==0x2 &&GPIOB->ODR==0x10)
		{

		}
	if(GPIOB->IDR ==0x2 &&GPIOB->ODR==0x20)
		{

		}
	if(GPIOB->IDR ==0x2 &&GPIOB->ODR==0x30)
		{

		}
	if(GPIOB->IDR ==0x2 &&GPIOB->ODR==0x40)
		{

		}

	if(GPIOB->IDR ==0x3 &&GPIOB->ODR==0x10)
		{

		}
	if(GPIOB->IDR ==0x3 &&GPIOB->ODR==0x20)
		{

		}
	if(GPIOB->IDR ==0x3 &&GPIOB->ODR==0x30)
		{

		}
	if(GPIOB->IDR ==0x3 &&GPIOB->ODR==0x40)
		{

		}

	if(GPIOB->IDR ==0x4 &&GPIOB->ODR==0x10)
		{

		}
	if(GPIOB->IDR ==0x4 &&GPIOB->ODR==0x20)
		{

		}
	if(GPIOB->IDR ==0x4 &&GPIOB->ODR==0x30)
		{

		}
	if(GPIOB->IDR ==0x4 &&GPIOB->ODR==0x40)
		{

		}
}*/
void EXTI_RTSR1_RT0_IRQHandler(void){

	if(EXTI->RPR1 & 0x1)
	{
		if(GPIOB->IDR ==0x1 &&GPIOB->ODR==0x10)
		{
			number0();
			delay(DELAY);
		}

		EXTI->RPR1 = 0x1;
	}

}
void EXTI_RTSR1_RT1_IRQHandler(void){

	if(EXTI->RPR1 & 0x2)
	{
		number1();
		delay(DELAY);
		EXTI->RPR1 = 0x2;
	}
}
void EXTI_RTSR1_RT2_IRQHandler(void){

	if(EXTI->RPR1 & 0x3)
	{
		number2();
		delay(DELAY);
		EXTI->RPR1 = 0x3;
	}
}
void EXTI_RTSR1_RT3_IRQHandler(void){

	if(EXTI->RPR1 & 0x4)
	{
		number2();
		delay(DELAY);
		EXTI->RPR1 = 0x4;
	}
}

 void number0(void)
 {
	 GPIOA->ODR = 0xF3;
 }
 void number1(void)
 {
	 GPIOA->ODR = 0x12;
 }
 void number2(void)
 {
	 GPIOA->ODR = 0x163;
 }
 void number3(void)
 {
	 GPIOA->ODR = 0x133;
 }
 void number4(void)
 {
	 GPIOA->ODR = 0x192;
 }
 void number5(void)
 {
	 GPIOA->ODR = 0x1B1;
 }
 void number6(void)
 {
	 GPIOA->ODR = 0x1F1;
 }
 void number7(void)
 {
	 GPIOA->ODR = 0x13;
 }
 void number8(void)
 {
	 GPIOA->ODR = 0x1F3;
 }
 void number9(void)
 {
	 GPIOA->ODR = 0x1B3;
 }

void delay(volatile uint32_t s)
{
    for(; s>0; s--);
}
