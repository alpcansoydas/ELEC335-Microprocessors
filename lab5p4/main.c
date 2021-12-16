#include "stm32g0xx.h"
#define BUTTON_DELAY	300
volatile uint32_t counter_button = 0;

void delay(volatile uint32_t s);

void setFrequency(uint32_t freq){
	TIM3->PSC = ((4000)/freq)-1; //2000=ARR value 8_000_000 is Timer clock and freq is pwm frequency
}

void setTone(uint8_t tone){
	switch(tone){
	case 1:
		setFrequency(0); //E4
		break;
	case 2:
		setFrequency(440); //A4
		break;
	case 3:
		setFrequency(523); //C5
		break;
	case 4:
		setFrequency(659); //E5
		break;
	case 5:
		setFrequency(784); //G5
		break;
	case 6:
		setFrequency(880); //A5
		break;
	case 7:
		setFrequency(1318); //E6
		break;
	case 8:
		setFrequency(2093); //C7
		break;
	case 9:
		setFrequency(3951); //B7
		break;
	default:
		setFrequency(0);

	}
}
void KeyPad(){
	volatile uint32_t keypad_read = GPIOB->IDR;
	keypad_read &= ~(1U << 0);
	switch(keypad_read){
		case 0x22 :		//1
			setTone(1);
			break;
		case 0x42 : 	//2
			setTone(2);
			break;
		case 0x82 :		//3
			setTone(3);
			break;
		case 0x24 :		//4
			setTone(4);
			break;
		case 0x44 :		//5
			setTone(5);
			break;
		case 0x84 :		//6
			setTone(6);
			break;
		case 0x28 :		//7
			setTone(7);
			break;
		case 0x48 :		//8
			setTone(8);
			break;
		case 0x88 :		//9
			setTone(9);
			break;
	}
}
void EXTI4_15_IRQHandler(){
	if(counter_button >= BUTTON_DELAY)
	{

		KeyPad();
		counter_button = 0;

	}

	EXTI->RPR1 = (0xF << 5);
}
void GPIO_Config(void){
	RCC->IOPENR |= (1U << 1); //Enable clock for port B
	GPIOB->MODER &= ~(3U << 0);
	GPIOB->MODER |= (2U << 2*0); //GPIOB alternate function mode //PB0
	//Alternate function low register AF1 //TIM3_CH3
	GPIOB->AFR[0] |= (1U << 4*0);
	for(uint32_t i=1;i<9;i++){
		if(i<5){
			GPIOB->MODER &= ~(3U << 2*i);
			GPIOB->MODER |= (1U << 2*i);
		}
		else{
			GPIOB->MODER &= ~(3U << 2*i);
			GPIOB->MODER |= (0U << 2*i);
			GPIOB->PUPDR |= (2U << 2*i);
			volatile uint32_t exticr_num;
			if((i <= 3)){
				exticr_num = 0;
			}
			else if((i >= 4) && (i <= 7)){
				exticr_num = 1;
			}
			else if((i >= 8) && (i <= 11)){
				exticr_num = 2;
			}
			else if((i >= 12) && (i <= 15)){
				exticr_num = 3;
			}
			EXTI->EXTICR[exticr_num] |= (1U << 8*(i % 4));
			EXTI->RTSR1 |= (1U << i);
			EXTI->IMR1 |= (1U << i);
			if((i <= 1)){
				NVIC_EnableIRQ(EXTI0_1_IRQn);
			}
			else if((i >= 2) && (i <= 3)){
				NVIC_EnableIRQ(EXTI2_3_IRQn);
			}
			else if((i >= 4) && (i <= 15)){
				NVIC_EnableIRQ(EXTI4_15_IRQn);
			}

		}
	}
}

//void TIM3_IRQHandler(){
//}

void TIM3_Config(){
	RCC->APBENR1 |= (1U << 1); //Enable TIM1 clock
	TIM3->CR1 |= (0U << 4); //Direction --> Upcounter
	//TIM3->CR1 |= (0U << 6);//Center-aligned mode /Edge-aligned
	TIM3->CR1 |= (3U << 5);//Center aligned mode/Edge-aligned ==> 3U yapınca TRIANGULAR ELDE ETTIK.
	TIM3->CR1 |= (0U << 9); //Clock division=1
	TIM3->CR1 |= (0U << 8); //Clock division=1

	//TIM3->DIER |= (1U << 0); //TIM3 interrupt enable

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

	//NVIC_SetPriority(TIM3_IRQn, 2);
	//NVIC_EnableIRQ(TIM3_IRQn);
}

int main(void) {

	TIM3_Config();
	GPIO_Config();
	TIM3->CCR3 = 1000;
	volatile uint32_t keypad_scan[] = {0x01,0x02,0x04,0x8};
	volatile uint8_t counter_keypad = 0;
    while(1) {

    	GPIOB->ODR = 0;
		GPIOB->ODR |= (keypad_scan[counter_keypad] << 1);
		if(counter_keypad >= 3){
			counter_keypad = 0;
		}
		else{
			counter_keypad++;
		}
		if(counter_button <= BUTTON_DELAY){
			counter_button++;
		}

	delay(1000);
    }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
