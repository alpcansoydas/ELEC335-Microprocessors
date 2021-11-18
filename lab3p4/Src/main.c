/*
 * main.c
 *	Author: Muhammed Cemal Eryigit
 */

#include "stm32g0xx.h"
#define  delayms 1600

volatile uint32_t counter =0;//represent which digit the number is in
volatile uint32_t port1=10;//keep number in variable port1
volatile uint32_t port2=10;//keep number in variable port2
volatile uint32_t port3=10;//keep number in variable port3
volatile uint32_t port4=10;//keep number in variable port4

void delay(volatile uint32_t);
void gpio_config(void);
void clock_config(void);
void EXTI_config(void);
void EXTI0_IRQHandler(void);
void check(void);
void number0(void);//number function
void number1(void);//number function
void number2(void);//number function
void number3(void);//number function
void number4(void);//number function
void number5(void);//number function
void number6(void);//number function
void number7(void);//number function
void number8(void);//number function
void number9(void);//number function

int main(void)
{
	clock_config();
	gpio_config();
	EXTI_config();
    while(1)
    {
    	check();
    }
    return 0;
}

void clock_config(void)
{
    /* Enable GPIOA and GPIOB clock */
    RCC->IOPENR |= (1U << 0);
    RCC->IOPENR |= (1U << 1);
}
void EXTI_config(void)
{
	EXTI->IMR1 |= (15U << 0);//Enable interrupt mask register
    EXTI->FTSR1 = (15U << 0);//Enable Falling trigger register
    EXTI->EXTICR[0] |= (1U << 8*0);//Enable interrupt
    EXTI->EXTICR[0] |= (1U << 8*1);//Enable interrupt
    EXTI->EXTICR[0] |= (1U << 8*2);//Enable interrupt
    EXTI->EXTICR[0] |= (1U << 8*3);//Enable interrupt

    NVIC_EnableIRQ(EXTI0_1_IRQn);//Enable NVIC EXTI0_1_IRQn
    NVIC_EnableIRQ(EXTI2_3_IRQn);//Enable NVIC EXTI2_3_IRQn

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



void EXTI0_1_IRQHandler(void)
{

	if(EXTI->FPR1 & 0x1)	//keypad ABCD column
	{
		EXTI->FPR1 = 0xFF;	//reset Falling trigger flag
	}
	if(EXTI->FPR1 & 0x2)	//keypad 963square column
	{
		//scanning to c2 column (963square)
		GPIOB->ODR |=0x70;
					if(GPIOB->IDR ==(0x7D))
					{
						number3();
						GPIOB->ODR=0x0;
					}
					else
					{
						GPIOB->ODR=0x0;
					}
		GPIOB->ODR |=0xB0;
					if(GPIOB->IDR ==(0xBD))
					{
						number6();
						GPIOB->ODR =0x0;
					}
					else
					{
						GPIOB->ODR =0x0;
					}
		GPIOB->ODR |=0xD0;
					if(GPIOB->IDR ==(0xDD))
					{
						number9();
						GPIOB->ODR=0x0;

					}
					else
					{
						GPIOB->ODR=0x0;
					}
	}
	EXTI->FPR1 = 0xFF;//reset falling trigger flag
}

void EXTI2_3_IRQHandler(void){

	if(EXTI->FPR1 & 0x4) //keypad 2580 column
	{
		//scanning to c3 column (2580)
		GPIOB->ODR |=0x70;
					if(GPIOB->IDR ==(0x7B))
					{
						number2();
						GPIOB->ODR=0x0;
					}
					else
					{
						GPIOB->ODR=0x0;
					}
		GPIOB->ODR |=0xB0;
					if(GPIOB->IDR ==(0xBB))
					{
						number5();
						GPIOB->ODR =0x0;
					}
					else
					{
						GPIOB->ODR =0x0;
					}
		GPIOB->ODR |=0xD0;
					if(GPIOB->IDR ==(0xDB))
					{
						number8();
						GPIOB->ODR=0x0;

					}
					else
					{
						GPIOB->ODR=0x0;

					}
		GPIOB->ODR |=0xE0;
					if(GPIOB->IDR ==(0xEB))
					{
						number0();
						GPIOB->ODR=0x0;
					}
					else
					{
						GPIOB->ODR =0x0;
					}
	}
	if(EXTI->FPR1 & 0x8) //keypad 147* column
	{
		//scanning to c4 column (147*)
		GPIOB->ODR |=0x70;
					if(GPIOB->IDR ==(0x77))
					{
						number1();
						GPIOB->ODR=0x0;
					}
					else
					{
						GPIOB->ODR=0x0;
					}
		GPIOB->ODR |=0xB0;
					if(GPIOB->IDR ==(0xB7))
					{
						number4();
						GPIOB->ODR =0x0;
					}
					else
					{
						GPIOB->ODR =0x0;
					}
		GPIOB->ODR |=0xD0;
					if(GPIOB->IDR ==(0xD7))
					{
						number7();
						GPIOB->ODR=0x0;

					}
					else
					{
						GPIOB->ODR=0x0;
					}
	}
	EXTI->FPR1 = 0xFF;//reset falling trigger flag
}
void check() //output to ssd
{
	for(;;)
		{
			if(port1!=10 && port2==10 && port3==10 && port4==10)
				{
					GPIOA->ODR=port1;
					delay(delayms);
				}
			else if(port1!=10 && port2!=10 && port3==10 && port4==10)
				{
					GPIOA->ODR=port1;
					delay(delayms);
					GPIOA->ODR=port2;
					delay(delayms);
				}
			else if(port1!=10 && port2!=10 && port3!=10 && port4==10)
				{
					GPIOA->ODR=port1;
					delay(delayms);
					GPIOA->ODR=port2;
					delay(delayms);
					GPIOA->ODR=port3;
					delay(delayms);
				}
			else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
				{
					GPIOA->ODR=port1;
					delay(delayms);
					GPIOA->ODR=port2;
					delay(delayms);
					GPIOA->ODR=port3;
					delay(delayms);
					GPIOA->ODR=port4;
					delay(delayms);
				}
		}
}
 void number0(void)
 {

	 if(counter==0)
		 {
			 counter++;
			 GPIOA->ODR &=0x00;
			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
				 {
					 EXTI->FPR1 = 0xFF;

					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0xF3;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				 }
			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
			 	 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0xF3;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
		 }
	 else if(counter==1)
		 {
 			 counter++;
			 if(port1!=10 && port2==10 && port3==10 && port4==10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2=port1;
					 port2|=0x1A00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0xF3;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0xF3;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
		 }
	 else if(counter==2)
		 {
			 counter++;
			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0xF3;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
					 }
			 		}
			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0xF3;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}

	 else if(counter==3)
		 {
			 counter=0;
			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0xF3;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
				 {
					 EXTI->FPR1 = 0xFF;
					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0xF3;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
		 }
 }
 void number1(void)
 {
	 if(counter==0)
		 {
			 counter++;
			 GPIOA->ODR &=0x00;
			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
			 {
				 EXTI->FPR1 = 0xFF;

				 GPIOA->ODR &=0x00;
				 GPIOA->ODR |=0x1C00;
				 GPIOA->ODR |= 0x12;
				 port1=GPIOA->ODR;
				 GPIOA->ODR &=0x00;
			 }
			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
			 {
				 EXTI->FPR1 = 0xFF;

				 port1 &=0x1FF;
				 port2 &=0x1FF;
				 port3 &=0x1FF;
				 port4 &=0x1FF;
				 port4=port3;
				 port3=port2;
				 port2=port1;
				 port2|=0x1A00;
				 port3|=0x1600;
				 port4|=0xE00;
				 GPIOA->ODR &=0x00;
				 GPIOA->ODR |=0x1C00;
				 GPIOA->ODR |= 0x12;
				 port1=GPIOA->ODR;
				 GPIOA->ODR &=0x00;
			}
	 	}
	 	else if(counter==1)
	 		 {
	  			 counter++;
	 			 if(port1!=10 && port2==10 && port3==10 && port4==10)
					 {
						 EXTI->FPR1 = 0xFF;

						 port1 &=0x1FF;
						 port2=port1;
						 port2|=0x1A00;
						 GPIOA->ODR &=0x00;
						 GPIOA->ODR |=0x1C00;
						 GPIOA->ODR |= 0x12;
						 port1=GPIOA->ODR;
						 GPIOA->ODR &=0x00;
					}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
					 {
						 EXTI->FPR1 = 0xFF;

						 port1 &=0x1FF;
						 port2 &=0x1FF;
						 port3 &=0x1FF;
						 port4 &=0x1FF;
						 port4=port3;
						 port3=port2;
						 port2=port1;
						 port2|=0x1A00;
						 port3|=0x1600;
						 port4|=0xE00;
						 GPIOA->ODR &=0x00;
						 GPIOA->ODR |=0x1C00;
						 GPIOA->ODR |= 0x12;
						 port1=GPIOA->ODR;
						 GPIOA->ODR &=0x00;
					}
	 		 }
	 	else if(counter==2)
	 		 {
	 			 counter++;
	 			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
					 {
						 EXTI->FPR1 = 0xFF;

						 port1 &=0x1FF;
						 port2 &=0x1FF;
						 port3=port2;
						 port2=port1;
						 port2|=0x1A00;
						 port3|=0x1600;
						 GPIOA->ODR &=0x00;
						 GPIOA->ODR |=0x1C00;
						 GPIOA->ODR |= 0x12;
						 port1=GPIOA->ODR;
						 GPIOA->ODR &=0x00;
					}
	 		 }
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
					 {
						 EXTI->FPR1 = 0xFF;
						 port1 &=0x1FF;
						 port2 &=0x1FF;
						 port3 &=0x1FF;
						 port4 &=0x1FF;
						 port4=port3;
						 port3=port2;
						 port2=port1;
						 port2|=0x1A00;
						 port3|=0x1600;
						 port4|=0xE00;
						 GPIOA->ODR &=0x00;
						 GPIOA->ODR |=0x1C00;
						 GPIOA->ODR |= 0x12;
						 port1=GPIOA->ODR;
						 GPIOA->ODR &=0x00;
					}

	 	else if(counter==3)
	 		 {
	 			 counter=0;
	 			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
					 {
						 EXTI->FPR1 = 0xFF;

						 port1 &=0x1FF;
						 port2 &=0x1FF;
						 port3 &=0x1FF;
						 port4=port3;
						 port3=port2;
						 port2=port1;
						 port2|=0x1A00;
						 port3|=0x1600;
						 port4|=0xE00;
						 GPIOA->ODR &=0x00;
						 GPIOA->ODR |=0x1C00;
						 GPIOA->ODR |= 0x12;
						 port1=GPIOA->ODR;
						 GPIOA->ODR &=0x00;
					}
				 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
					 {
						 EXTI->FPR1 = 0xFF;
						 port1 &=0x1FF;
						 port2 &=0x1FF;
						 port3 &=0x1FF;
						 port4 &=0x1FF;
						 port4=port3;
						 port3=port2;
						 port2=port1;
						 port2|=0x1A00;
						 port3|=0x1600;
						 port4|=0xE00;
						 GPIOA->ODR &=0x00;
						 GPIOA->ODR |=0x1C00;
						 GPIOA->ODR |= 0x12;
						 port1=GPIOA->ODR;
						 GPIOA->ODR &=0x00;
					}
		 }

 }
 void number2(void)
 {
	 if(counter==0)
		 {
			 counter++;
			 GPIOA->ODR &=0x00;
			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
				 {
					 EXTI->FPR1 = 0xFF;

					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0x163;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				 }
			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0x163;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
	 	}
	 else if(counter==1)
		 {
			 counter++;
			 if(port1!=10 && port2==10 && port3==10 && port4==10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2=port1;
					 port2|=0x1A00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0x163;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
				 {
					 EXTI->FPR1 = 0xFF;
					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0x163;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
		 }
	 else if(counter==2)
		 {
			 counter++;
			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0x163;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
					 }
				}
	 	 	 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
					 {
						 EXTI->FPR1 = 0xFF;
						 port1 &=0x1FF;
						 port2 &=0x1FF;
						 port3 &=0x1FF;
						 port4 &=0x1FF;
						 port4=port3;
						 port3=port2;
						 port2=port1;
						 port2|=0x1A00;
						 port3|=0x1600;
						 port4|=0xE00;
						 GPIOA->ODR &=0x00;
						 GPIOA->ODR |=0x1C00;
						 GPIOA->ODR |= 0x163;
						 port1=GPIOA->ODR;
						 GPIOA->ODR &=0x00;
					}
	  else if(counter==3)
		 {
			 counter=0;
			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
				 {
					 EXTI->FPR1 = 0xFF;

					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0x163;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
	 		else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
				 {
					 EXTI->FPR1 = 0xFF;
					 port1 &=0x1FF;
					 port2 &=0x1FF;
					 port3 &=0x1FF;
					 port4 &=0x1FF;
					 port4=port3;
					 port3=port2;
					 port2=port1;
					 port2|=0x1A00;
					 port3|=0x1600;
					 port4|=0xE00;
					 GPIOA->ODR &=0x00;
					 GPIOA->ODR |=0x1C00;
					 GPIOA->ODR |= 0x163;
					 port1=GPIOA->ODR;
					 GPIOA->ODR &=0x00;
				}
	 	 }

 }
 void number3(void)
 {
	 if(counter==0)
	 		 {
	 			 counter++;
	 			 GPIOA->ODR &=0x00;
	 			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
	 			 {
	 				 EXTI->FPR1 = 0xFF;

	 				 GPIOA->ODR &=0x00;
	 				 GPIOA->ODR |=0x1C00;
	 				 GPIOA->ODR |= 0x133;
	 				 port1=GPIOA->ODR;
	 				 GPIOA->ODR &=0x00;
	 			 }
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
					 {
						 EXTI->FPR1 = 0xFF;

						 port1 &=0x1FF;
						 port2 &=0x1FF;
						 port3 &=0x1FF;
						 port4 &=0x1FF;
						 port4=port3;
						 port3=port2;
						 port2=port1;
						 port2|=0x1A00;
						 port3|=0x1600;
						 port4|=0xE00;
						 GPIOA->ODR &=0x00;
						 GPIOA->ODR |=0x1C00;
						 GPIOA->ODR |= 0x133;
						 port1=GPIOA->ODR;
						 GPIOA->ODR &=0x00;
					}


	 		 }
	 		 else if(counter==1)
	 		 {
	  			 counter++;
	 			 if(port1!=10 && port2==10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x133;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
						 {
							 EXTI->FPR1 = 0xFF;
							 port1 &=0x1FF;
							 port2 &=0x1FF;
							 port3 &=0x1FF;
							 port4 &=0x1FF;
							 port4=port3;
							 port3=port2;
							 port2=port1;
							 port2|=0x1A00;
							 port3|=0x1600;
							 port4|=0xE00;
							 GPIOA->ODR &=0x00;
							 GPIOA->ODR |=0x1C00;
							 GPIOA->ODR |= 0x133;
							 port1=GPIOA->ODR;
							 GPIOA->ODR &=0x00;
						}
	 		 }
	 		 else if(counter==2)
	 		 {
	 			 counter++;
	 			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;


	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x133;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 }
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x133;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}

	 		 else if(counter==3)
	 		 {
	 			 counter=0;
	 			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3 &=0x1FF;
	 			 			 port4=port3;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 port4|=0xE00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x133;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x133;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }

 }
 void number4(void)
 {
	 if(counter==0)
	 		 {
	 			 counter++;
	 			 GPIOA->ODR &=0x00;
	 			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
	 			 {
	 				 EXTI->FPR1 = 0xFF;

	 				 GPIOA->ODR &=0x00;
	 				 GPIOA->ODR |=0x1C00;
	 				 GPIOA->ODR |= 0x192;
	 				 port1=GPIOA->ODR;
	 				 GPIOA->ODR &=0x00;
	 			 }
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 {
	 			 		 			 EXTI->FPR1 = 0xFF;

	 					 			 port1 &=0x1FF;
	 					 			 port2 &=0x1FF;
	 					 			 port3 &=0x1FF;
	 					 			 port4 &=0x1FF;
	 					 			 port4=port3;
	 					 			 port3=port2;
	 					 			 port2=port1;
	 					 			 port2|=0x1A00;
	 					 			 port3|=0x1600;
	 					 			 port4|=0xE00;
	 					 			 GPIOA->ODR &=0x00;
	 					 			 GPIOA->ODR |=0x1C00;
	 					 			 GPIOA->ODR |= 0x192;
	 					 			 port1=GPIOA->ODR;
	 					 			 GPIOA->ODR &=0x00;
	 			 		 		}


	 		 }
	 		 else if(counter==1)
	 		 {
	  			 counter++;
	 			 if(port1!=10 && port2==10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x192;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x192;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }
	 		 else if(counter==2)
	 		 {
	 			 counter++;
	 			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;


	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x192;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 }
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x192;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}

	 		 else if(counter==3)
	 		 {
	 			 counter=0;
	 			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3 &=0x1FF;
	 			 			 port4=port3;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 port4|=0xE00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x192;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x192;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }

 }
 void number5(void)
 {
	 if(counter==0)
	 		 {
	 			 counter++;
	 			 GPIOA->ODR &=0x00;
	 			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
	 			 {
	 				 EXTI->FPR1 = 0xFF;

	 				 GPIOA->ODR &=0x00;
	 				 GPIOA->ODR |=0x1C00;
	 				 GPIOA->ODR |= 0x1B1;
	 				 port1=GPIOA->ODR;
	 				 GPIOA->ODR &=0x00;
	 			 }
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 {
	 			 		 			 EXTI->FPR1 = 0xFF;

	 					 			 port1 &=0x1FF;
	 					 			 port2 &=0x1FF;
	 					 			 port3 &=0x1FF;
	 					 			 port4 &=0x1FF;
	 					 			 port4=port3;
	 					 			 port3=port2;
	 					 			 port2=port1;
	 					 			 port2|=0x1A00;
	 					 			 port3|=0x1600;
	 					 			 port4|=0xE00;
	 					 			 GPIOA->ODR &=0x00;
	 					 			 GPIOA->ODR |=0x1C00;
	 					 			 GPIOA->ODR |= 0x1B1;
	 					 			 port1=GPIOA->ODR;
	 					 			 GPIOA->ODR &=0x00;
	 			 		 		}


	 		 }
	 		 else if(counter==1)
	 		 {
	  			 counter++;
	 			 if(port1!=10 && port2==10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1B1;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1B1;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }
	 		 else if(counter==2)
	 		 {
	 			 counter++;
	 			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;


	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1B1;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 }
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1B1;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}

	 		 else if(counter==3)
	 		 {
	 			 counter=0;
	 			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3 &=0x1FF;
	 			 			 port4=port3;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 port4|=0xE00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1B1;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1B1;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }

 }

 void number6(void)
 {
	 if(counter==0)
	 		 {
	 			 counter++;
	 			 GPIOA->ODR &=0x00;
	 			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
	 			 {
	 				 EXTI->FPR1 = 0xFF;

	 				 GPIOA->ODR &=0x00;
	 				 GPIOA->ODR |=0x1C00;
	 				 GPIOA->ODR |= 0x1F1;
	 				 port1=GPIOA->ODR;
	 				 GPIOA->ODR &=0x00;
	 			 }
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 {
	 			 		 			 EXTI->FPR1 = 0xFF;

	 					 			 port1 &=0x1FF;
	 					 			 port2 &=0x1FF;
	 					 			 port3 &=0x1FF;
	 					 			 port4 &=0x1FF;
	 					 			 port4=port3;
	 					 			 port3=port2;
	 					 			 port2=port1;
	 					 			 port2|=0x1A00;
	 					 			 port3|=0x1600;
	 					 			 port4|=0xE00;
	 					 			 GPIOA->ODR &=0x00;
	 					 			 GPIOA->ODR |=0x1C00;
	 					 			 GPIOA->ODR |= 0x1F1;
	 					 			 port1=GPIOA->ODR;
	 					 			 GPIOA->ODR &=0x00;
	 			 		 		}


	 		 }
	 		 else if(counter==1)
	 		 {
	  			 counter++;
	 			 if(port1!=10 && port2==10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1F1;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1F1;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }
	 		 else if(counter==2)
	 		 {
	 			 counter++;
	 			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;


	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1F1;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 }
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1F1;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}

	 		 else if(counter==3)
	 		 {
	 			 counter=0;
	 			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3 &=0x1FF;
	 			 			 port4=port3;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 port4|=0xE00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1F1;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1F1;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }

 }
 void number7(void)
 {
	 if(counter==0)
	 		 {
	 			 counter++;
	 			 GPIOA->ODR &=0x00;
	 			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
	 			 {
	 				 EXTI->FPR1 = 0xFF;

	 				 GPIOA->ODR &=0x00;
	 				 GPIOA->ODR |=0x1C00;
	 				 GPIOA->ODR |= 0x13;
	 				 port1=GPIOA->ODR;
	 				 GPIOA->ODR &=0x00;
	 			 }
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 {
	 			 		 			 EXTI->FPR1 = 0xFF;

	 					 			 port1 &=0x1FF;
	 					 			 port2 &=0x1FF;
	 					 			 port3 &=0x1FF;
	 					 			 port4 &=0x1FF;
	 					 			 port4=port3;
	 					 			 port3=port2;
	 					 			 port2=port1;
	 					 			 port2|=0x1A00;
	 					 			 port3|=0x1600;
	 					 			 port4|=0xE00;
	 					 			 GPIOA->ODR &=0x00;
	 					 			 GPIOA->ODR |=0x1C00;
	 					 			 GPIOA->ODR |= 0x13;
	 					 			 port1=GPIOA->ODR;
	 					 			 GPIOA->ODR &=0x00;
	 			 		 		}


	 		 }
	 		 else if(counter==1)
	 		 {
	  			 counter++;
	 			 if(port1!=10 && port2==10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x13;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x13;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }
	 		 else if(counter==2)
	 		 {
	 			 counter++;
	 			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;


	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x13;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 }
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x13;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}

	 		 else if(counter==3)
	 		 {
	 			 counter=0;
	 			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3 &=0x1FF;
	 			 			 port4=port3;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 port4|=0xE00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x13;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x13;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }
 }
 void number8(void)
 {
	 if(counter==0)
	 		 {
	 			 counter++;
	 			 GPIOA->ODR &=0x00;
	 			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
	 			 {
	 				 EXTI->FPR1 = 0xFF;

	 				 GPIOA->ODR &=0x00;
	 				 GPIOA->ODR |=0x1C00;
	 				 GPIOA->ODR |= 0x1F3;
	 				 port1=GPIOA->ODR;
	 				 GPIOA->ODR &=0x00;
	 			 }
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 {
	 			 		 			 EXTI->FPR1 = 0xFF;

	 					 			 port1 &=0x1FF;
	 					 			 port2 &=0x1FF;
	 					 			 port3 &=0x1FF;
	 					 			 port4 &=0x1FF;
	 					 			 port4=port3;
	 					 			 port3=port2;
	 					 			 port2=port1;
	 					 			 port2|=0x1A00;
	 					 			 port3|=0x1600;
	 					 			 port4|=0xE00;
	 					 			 GPIOA->ODR &=0x00;
	 					 			 GPIOA->ODR |=0x1C00;
	 					 			 GPIOA->ODR |= 0x1F3;
	 					 			 port1=GPIOA->ODR;
	 					 			 GPIOA->ODR &=0x00;
	 			 		 		}


	 		 }
	 		 else if(counter==1)
	 		 {
	  			 counter++;
	 			 if(port1!=10 && port2==10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1F3;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1F3;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }
	 		 else if(counter==2)
	 		 {
	 			 counter++;
	 			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;


	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1F3;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 }
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1F3;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}

	 		 else if(counter==3)
	 		 {
	 			 counter=0;
	 			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3 &=0x1FF;
	 			 			 port4=port3;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 port4|=0xE00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1F3;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1F3;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }

 }
 void number9(void)
 {
	 if(counter==0)
	 		 {
	 			 counter++;
	 			 GPIOA->ODR &=0x00;
	 			 if((port1==10) && (port2==10) && (port3==10) && (port4==10))
	 			 {
	 				 EXTI->FPR1 = 0xFF;

	 				 GPIOA->ODR &=0x00;
	 				 GPIOA->ODR |=0x1C00;
	 				 GPIOA->ODR |= 0x1B3;
	 				 port1=GPIOA->ODR;
	 				 GPIOA->ODR &=0x00;
	 			 }
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 {
	 			 		 			 EXTI->FPR1 = 0xFF;

	 					 			 port1 &=0x1FF;
	 					 			 port2 &=0x1FF;
	 					 			 port3 &=0x1FF;
	 					 			 port4 &=0x1FF;
	 					 			 port4=port3;
	 					 			 port3=port2;
	 					 			 port2=port1;
	 					 			 port2|=0x1A00;
	 					 			 port3|=0x1600;
	 					 			 port4|=0xE00;
	 					 			 GPIOA->ODR &=0x00;
	 					 			 GPIOA->ODR |=0x1C00;
	 					 			 GPIOA->ODR |= 0x1B3;
	 					 			 port1=GPIOA->ODR;
	 					 			 GPIOA->ODR &=0x00;
	 			 		 		}


	 		 }
	 		 else if(counter==1)
	 		 {
	  			 counter++;
	 			 if(port1!=10 && port2==10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1B3;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1B3;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }
	 		 else if(counter==2)
	 		 {
	 			 counter++;
	 			 if(port1!=10 && port2!=10 && port3==10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;


	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1B3;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 }
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1B3;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}

	 		 else if(counter==3)
	 		 {
	 			 counter=0;
	 			 if(port1!=10 && port2!=10 && port3!=10 && port4==10)
	 			 		 {
	 			 			 EXTI->FPR1 = 0xFF;

	 			 			 port1 &=0x1FF;
	 			 			 port2 &=0x1FF;
	 			 			 port3 &=0x1FF;
	 			 			 port4=port3;
	 			 			 port3=port2;
	 			 			 port2=port1;
	 			 			 port2|=0x1A00;
	 			 			 port3|=0x1600;
	 			 			 port4|=0xE00;
	 			 			 GPIOA->ODR &=0x00;
	 			 			 GPIOA->ODR |=0x1C00;
	 			 			 GPIOA->ODR |= 0x1B3;
	 			 			 port1=GPIOA->ODR;
	 			 			 GPIOA->ODR &=0x00;
	 			 		}
	 			 else if(port1!=10 && port2!=10 && port3!=10 && port4!=10)
	 			 		 		 		 {
	 			 		 		 			 EXTI->FPR1 = 0xFF;
	 							 			 port1 &=0x1FF;
	 							 			 port2 &=0x1FF;
	 							 			 port3 &=0x1FF;
	 							 			 port4 &=0x1FF;
	 							 			 port4=port3;
	 							 			 port3=port2;
	 							 			 port2=port1;
	 							 			 port2|=0x1A00;
	 							 			 port3|=0x1600;
	 							 			 port4|=0xE00;
	 							 			 GPIOA->ODR &=0x00;
	 							 			 GPIOA->ODR |=0x1C00;
	 							 			 GPIOA->ODR |= 0x1B3;
	 							 			 port1=GPIOA->ODR;
	 							 			 GPIOA->ODR &=0x00;
	 			 		 		 		}
	 		 }

 }

void delay(volatile uint32_t s)
{
    for(; s>0; s--);
}
