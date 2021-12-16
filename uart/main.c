#include "stm32g0xx.h"

#define LEDDELAY    1600000

void printChar(uint8_t c);
void delay(volatile uint32_t);

void GPIO_Config(void){
	RCC->IOPENR |= (1U << 0); //Enable clock for GPIOA
	RCC->APBENR1 |= (1U << 17); //Enable clock for USART2

	GPIOA->MODER &= ~(3U << 2*2);
	GPIOA->MODER |= (2U << 2*2);

	GPIOA->AFR[0] &= ~(0xFU << 4*2);
	GPIOA->AFR[0] |= (1 << 4*2);

	GPIOA->MODER &= ~(0xFU << 2*3);
	GPIOA->MODER |= (2U << 2*3);

	GPIOA->AFR[0] &= ~(0xFU << 4*3);
	GPIOA->AFR[0] |= (1 << 4*3);

}

void printChar(uint8_t c){
	USART2->TDR = (uint16_t) c;
	while(!(USART2->ISR & (1 << 6))); // 6.bit transmission complete
}

void USART2_IRQHandler(void){
	uint8_t data = (uint8_t)USART2->RDR;
    //RXNE is automatically cleared when read
    printChar(data);
}

void USART_Config(uint16_t baud){
	USART2->CR1 = 0;
	USART2->CR1 |= (1U << 2); //USART1 receiver enable
	USART2->CR1 |= (1U << 3); //USART1 transmitter enable
	USART2->CR1 |= (1U << 5); //RX Interrupt enable

	USART2->BRR  = (uint16_t)(SystemCoreClock / baud); //Setting baudrate

	USART2->CR1 |= (1U << 0); //USART2 enable

	NVIC_SetPriority(USART2_IRQn , 1);
	NVIC_EnableIRQ(USART2_IRQn);

}

int main(void) {
	GPIO_Config();
	USART_Config(9600);

    while(1) {

    }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
