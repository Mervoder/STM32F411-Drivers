/*
 * USART_Test.c
 *
 *  Created on: 7 Nis 2023
 *      Author: Oğuz Kaan
 */

#include "stm32f411xx.h"

static void GPIO_Config(void);
static void USART_Config(void);

USART_HandleTypeDef_t USART_Handle;


void USART1_IRQHandler()
{

	USART_InterruptHandler(&USART_Handle);

}

int main(void)
{

 	char msgToSend [20] = "2";
 	char receiveData [20];

	GPIO_Config();
	USART_Config();

	USART_TransmitData_IT(&USART_Handle, (uint8_t*)msgToSend, strlen(msgToSend));
	USART_ReceiveData_IT(&USART_Handle, (uint8_t*) receiveData, 10);

	// Polling method
	//USART_ReceiveData(&USART_Handle, (uint8_t*)msgToSend, 12 );
	//USART_TransmitData(&USART_Handle, (uint8_t*)msgToSend, strlen(msgToSend));

	while(1);

}


static void USART_Config(void)
{
	RCC_USART1_CLK_ENABLE();

	USART_Handle.Instance  = USART1;

	USART_Handle.Init.BaudRate = 115200;
	USART_Handle.Init.HardWareFlowControl = USART_HW_NONE;
	USART_Handle.Init.Mode = USART_MODE_Tx_Rx;
	USART_Handle.Init.OverSampling = USART_OVERSAMPLE_16;
	USART_Handle.Init.Parity = USART_PARITY_NONE;
	USART_Handle.Init.StopBits = USART_STOPBIT_ONE;
	USART_Handle.Init.WordLength = USART_WORDLENGTH_8BITS;

	USART_Init(&USART_Handle);

	NVIC_EnableInterrupt(USART1_IRQNumber);

	USART_PeriphCMD(&USART_Handle, ENABLE);

}

static void GPIO_Config(void)
{
	GPIO_InitTypeDef_t GPIO_InitStruct = {0};

	RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.pinNumber = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_VEHIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7;

	GPIO_Init(GPIOA, &GPIO_InitStruct);



}
