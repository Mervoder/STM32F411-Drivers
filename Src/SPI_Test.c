/*
 * SPI_Test.c
 *
 *  Created on: 7 Nis 2023
 *      Author: Oğuz Kaan
 */

#include "stm32f411xx.h"



SPI_HandleTypeDef_t SPI_HandleStructure ;
GPIO_InitTypeDef_t GPIO_Pin_Struct ;


static void SPI_GPIO_Config();
static void SPI_Config();

int main(void)
{


	SPI_GPIO_Config();
	SPI_Config();

/********LOOP**********/
	for(;;)

	{

	}

}





static void SPI_GPIO_Config()
{
	memset(&GPIO_Pin_Struct, 0 , sizeof(GPIO_Pin_Struct));

	RCC_GPIOA_CLK_ENABLE();
	RCC_SPI1_CLK_ENABLE();

	GPIO_Pin_Struct.pinNumber = GPIO_PIN_5 | GPIO_PIN_7  ; // PA5= SCK and PA7 = MOSI
	GPIO_Pin_Struct.Mode = GPIO_MODE_AF;
	GPIO_Pin_Struct.Otype = GPIO_OTYPE_PP;
	GPIO_Pin_Struct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_Pin_Struct.Speed = GPIO_SPEED_HIGH;
	GPIO_Pin_Struct.Alternate = GPIO_AF5;

	GPIO_Init(GPIOA,&GPIO_Pin_Struct);

	memset(&GPIO_Pin_Struct, 0 , sizeof(GPIO_Pin_Struct));

}



static void SPI_Config()
{


	SPI_HandleStructure.Instance = SPI1;

	SPI_HandleStructure.Init.BaudRate = SPI_BAUDRATE_DIV8;
	SPI_HandleStructure.Init.BusConfig = SPI_BUS_FullDuplex;
	SPI_HandleStructure.Init.DFF_Format = SPI_DFF_8BITS;
	SPI_HandleStructure.Init.CPOL = SPI_CPOL_HIGH;
	SPI_HandleStructure.Init.Mode = SPI_MODE_MASTER;
	SPI_HandleStructure.Init.FrameFormat = SPI_FrameFormat_MSB;
	SPI_HandleStructure.Init.CPHA = SPI_CPHA_FIRST;
	SPI_HandleStructure.Init.SSM_Cmd = SPI_SSM_ENABLE;


	SPI_Init(&SPI_HandleStructure);
	NVIC_EnableInterrupt(SPI1_IRQNumber);

	SPI_PeriphCmd(&SPI_HandleStructure, ENABLE);


}

