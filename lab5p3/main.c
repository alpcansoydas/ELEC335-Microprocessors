#include "stm32g0xx.h"

void delay(volatile uint32_t s);
volatile uint32_t counter = 0;
uint32_t sample[256] = {
		1000,1025,1049,1074,1098,1122,1147,1171,1195,1219,1243,1267,1290,1314,1337,1360,1383,1405,1428,1450,1471,1493,1514,1535,1556,1576,1596,1615,1634,1653,1672,1690,1707,1724,1741,1757,1773,1788,1803,1818,1831,1845,1858,1870,1882,1893,1904,1914,1924,1933,
		1942,1950,1957,1964,1970,1976,1981,1985,1989,1992,1995,1997,1999,2000,2000,2000,1999,1997,1995,1992,1989,1985,1981,1976,1970,1964,1957,1950,1942,1933,1924,1914,1904,1893,1882,1870,1858,1845,1831,1818,1803,1788,1773,1757,1741,1724,1707,1690,1672,1653,
		1634,1615,1596,1576,1556,1535,1514,1493,1471,1450,1428,1405,1383,1360,1337,1314,1290,1267,1243,1219,1195,1171,1147,1122,1098,1074,1049,1025,1000,975,951,926,902,878,853,829,805,781,757,733,710,686,663,640,617,595,572,550,529,507,
		486,465,444,424,404,385,366,347,328,310,293,276,259,243,227,212,197,182,169,155,142,130,118,107,96,86,76,67,58,50,43,36,30,24,19,15,11,8,5,3,1,0,0,0,1,3,5,8,11,15,
		19,24,30,36,43,50,58,67,76,86,96,107,118,130,142,155,169,182,197,212,227,243,259,276,293,310,328,347,366,385,404,424,444,465,486,507,529,550,572,595,617,640,663,686,710,733,757,781,805,829,
		853,878,902,926,951,975
};

void setFrequency(uint16_t freq){
	TIM3->PSC = ((4000)/freq)-1; //2000=ARR value 8_000_000 is Timer clock and freq is pwm frequency
}

void GPIO_Config(void){
	RCC->IOPENR |= (1U << 1); //Enable clock for port B
	GPIOB->MODER &= ~(3U << 0);
	GPIOB->MODER |= (2U << 2*0); //GPIOB alternate function mode //PB0
	//Alternate function low register AF1 //TIM3_CH3
	GPIOB->AFR[0] |= (1U << 4*0);
}

void TIM3_IRQHandler(){
setFrequency(2000);
TIM3->CCR3 = sample[counter];
if(counter >= 255){
counter = 0;
}
else{
counter++;
}
}


void TIM3_Config(){
	RCC->APBENR1 |= (1U << 1); //Enable TIM1 clock
	TIM3->CR1 |= (0U << 4); //Direction --> Upcounter
	//TIM3->CR1 |= (0U << 6);//Center-aligned mode /Edge-aligned
	TIM3->CR1 |= (3U << 5);//Center aligned mode/Edge-aligned ==> 3U yapınca TRIANGULAR ELDE ETTIK.
	TIM3->CR1 |= (0U << 9); //Clock division=1
	TIM3->CR1 |= (0U << 8); //Clock division=1

	TIM3->DIER |= (1U << 0); //TIM3 interrupt enable

	TIM3->CCMR1 |= (0U << 0);//CC1 channel is configured as output
	TIM3->CCMR1 |= (0U << 1);//CC1 channel is configured as output
	TIM3->CCMR1 |= (6U << 4); //PWM MODE1
	TIM3->CCMR1 |= (0U << 9); //CC2 channel is configured as output
	TIM3->CCMR1 |= (0U << 8); //CC2 channel is configured as output
	TIM3->CCMR1 |= (6U << 12); //PWM MODE for channel2
	/*
	 * Capture/Compare 1&2 output selected
	 * Capture/Compare 1&2 PWM1 selected
	 */
	TIM3->CCMR2 |= (0U << 0); //Capture compare 3 selection
	TIM3->CCMR2 |= (0U << 1); //Capture compare 3 selection
	TIM3->CCMR2 |= (6U << 4); //PWM MODE
	TIM3->CCMR2 |= (0U << 8); //Capture compare 4 selection
	TIM3->CCMR2 |= (0U << 9); //Capture compare 3 selection
	TIM3->CCMR2 |= (6U << 12); //PWM MODE
	/*
	 * Capture/Compare 3&4 output selected
	 * Capture/Compare 3&4 PWM1 selected
	 */
	TIM3->CCER |= (1U << 0); //Capture Compare 1 output enable
	TIM3->CCER |= (1U << 4); //Capture Compare 2 output enable
	TIM3->CCER |= (1U << 8); //Capture Compare 3 output enable
	TIM3->CCER |= (1U << 12); //Capture Compare 4 output enable
	TIM3->ARR = 2000;

	TIM3->CR1 |= (1U << 0); //TIM3 enable

	NVIC_SetPriority(TIM3_IRQn, 2);
	NVIC_EnableIRQ(TIM3_IRQn);
}

int main(void) {

	TIM3_Config();
	GPIO_Config();

    while(1) {}

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

