#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"

// register width(need to be written by...)?
// unaligned acces, data type and orders
// may be uninit?
// new clock, can data transfer still happen in the gap?
// alternate trigger mode, slow interleave
// interrupt table in ram?
// circular buffer
// 8 bit mode

/* floorplan
////////////////////////////////////////////
in lowest sample time mode:
setup
      setup dma
      setup timer
      init adc fast interleave, 1.5st, cont
      calibrate adc
      setup anawd
      start adc

anawdint
      disabe anawd
      start timer
timer int
	  disable dma
	  send data
button int
      enable anawd
      enable dma


///////////////////////////////////////////////
in higer sample time modes:

setup
      init adc inject alternate, trigger time x, cont off(?), trigger off timer, interrupt on acd 2 conversion
      setup timer freq=(trigger time x + 12.5)/2
      calibrate adc
      setup anawd
      start adc
anawdint
      if primed
            triggered=1// same var compare 0 is quickest
jeocint
      if triggerd
            move data
            increment pointers / decrement sample count
            //or can we force a dma reqeust from here

button int
      primed=1
////////////////////////////////////


inermediate mode for st=7.5: use dma but on slow interleave: samples wont be evenly spaced!
or other method?
(consider using this mode for st=13.5)

 */

#define n_samples 1000//has to be even
#define n_sample_bytes n_samples*2
#define n_sample_transfers n_samples/2

const uint8_t messages[]={'o','k','!'};
volatile uint8_t samples[n_sample_bytes] __attribute__((aligned (4)));

//prototypes
void main(void);
void wait(uint32_t counts);

void main(void)
{
	// Enalbe periph clocks, does port b clock need to be enabled for adc, and port a?(if needed for rgisters can it be disabled after registers are set)
	RCC->APB2ENR = RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2;

	// pin a9 as altfunc output 50mhz, pina10 as floatin ,rest as floating
	GPIOA->CRH = 0b01000100010001000100010010110100;
	//pb0 as analog input
	GPIOB->CRL = 0b01000100010001000100010001000000;

	// enable usart, enable rxne, enable tx and rx
	USART1->CR1 = 0b0010000000101100;
	//set baud to 9600 (56000000/16/(364+9/16))
	USART1->BRR = 0b0001011011001001;

	//dma , max prio, 32-32, meminc, circular
	DMA1_Channel1->CCR = 0b00000000000000000011101010100001;
	DMA1_Channel1->CMAR = (uint32_t)&samples;
	DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
	DMA1_Channel1->CNDTR = n_sample_bytes/4;

	//adc en
	ADC1->CR2 = 0b00000000000000000000000000000001;
	ADC2->CR2 = 0b00000000000000000000000000000001;
	//conversion on adc8 (pb0)
	ADC1->SQR3 = 0b00000000000000000000000000001000;
	ADC2->SQR3 = 0b00000000000000000000000000001000;
	// anawd,fastinter, anawdint
	ADC1->CR1 = 0b00000000100001110000000001000000;
	ADC2->CR1 = 0b00000000100000000000000001000000;
	//set anawd values
	ADC1->HTR = ADC2->HTR = 0b00000000000000000000011111111111;
	wait(20);
	//start cal, cont, software trig, dma
	ADC1->CR2 = 0b00000000000111100000000100000111;
	ADC2->CR2 = 0b00000000000111100000000100000111;
	wait(20);
	//start conversion
	ADC1->CR2 = 0b00000000010111100000000100000011;

	//enable usart interrupt
	NVIC_EnableIRQ(USART1_IRQn);
	//enable adc interrupt
	NVIC_EnableIRQ(ADC1_2_IRQn);//the compiler doesnt optimize the reg index operation!
	//enable timer interrupt


	while(1)
	{
		//nothing
	}
}

void wait(uint32_t counts){
	while (counts!=0){
		counts--;
	}
}

void ADC1_2_IRQHandler(void){
	// "turn off" anawd, order, can this happen in the time between wdinterrupts
	ADC1->HTR = ADC2->HTR = 0b00000000000000000000111111111111;
	//start timer
	//clear sr?
	ADC1->SR = ADC2->SR = 0;
}


void USART1_IRQHandler(void){
	//check RXNE handler
	if((USART1->SR & 0b0000000000100000) != 0){
		//check character
		if((char)(USART1->DR)=='t'){
			//send loop
			for(uint8_t i=0; i < 3; i++){
				USART1->DR = messages[i];
				// Wait until Tx data register is empty
				while((USART1->SR & USART_FLAG_TXE) == 0)
				{
				}
			}
		}
	}
	USART1->SR = 0;// needed?
}
