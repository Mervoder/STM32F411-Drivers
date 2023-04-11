/**
 ******************************************************************************
 * Written by OĞUZ KAAN ATAY
 *                          	atay.oguzkaan@gmail.com
 ******************************************************************************
 */

/*********INCLUDE*************/
#include "stm32f411xx.h"
#include "GPIO.h"

/********Functions Declarations******************/

static void GPIO_Pin_Config();
static void LockControl();
static void GPIO_Button_Interrupt();
static void SPI_GPIO_Config();
static void SPI_Config();

/*********User Configurations Typedef*******************/

SPI_HandleTypeDef_t SPI_HandleStructure ;
GPIO_InitTypeDef_t GPIO_Pin_Struct ;
USART_HandleTypeDef_t USART_Handle;


void EXTI0_IRQHandler()
{
	char  msgToSend[] = "Hello World!";

	if(EXTI->PR & 0x1)				// checking pending register
	{
		EXTI->PR |= (0x1 << 0U);	// reset the pending register


		GPIO_Write_Pin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_Pin_Set);


	    SPI_TransmitData_IT(&SPI_HandleStructure, (uint8_t*)msgToSend, strlen(msgToSend));

}


void SPI1_IRQHandler ()
{

	SPI_InterruptHandler(&SPI_HandleStructure);
}


}

int main(void)
{

	GPIO_Pin_Config();

	GPIO_Button_Interrupt();

	SPI_GPIO_Config();
	SPI_Config();

/********LOOP**********/
	for(;;)

	{

	}

}

/***********************************************FUNCTIONS DEFINITIONS************************************************/

static void GPIO_Pin_Config()
{


	RCC_GPIOD_CLK_ENABLE();  // clock is active
	RCC_GPIOA_CLK_ENABLE();
	RCC_SYSCFG_CLK_ENABLE();

//*****************FOR LED PIN*****************************************
	GPIO_Pin_Struct.pinNumber = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 ;
	GPIO_Pin_Struct.Mode = GPIO_MODE_OUTPUT;
	GPIO_Pin_Struct.Speed = GPIO_SPEED_HIGH;
	GPIO_Pin_Struct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_Pin_Struct.Otype = GPIO_OTYPE_PP;

	GPIO_Init(GPIOD, &GPIO_Pin_Struct); // config

//*****************FOR Button PIN*****************************************
	memset(&GPIO_Pin_Struct, 0 , sizeof(GPIO_Pin_Struct));  // address , int value , size


	GPIO_Pin_Struct.pinNumber = GPIO_PIN_0;
	GPIO_Pin_Struct.Mode = GPIO_MODE_INPUT;
	// output ve alternet mode dışı configre edilemezler 	GPIO_Pin_Struct.Speed = GPIO_SPEED_HIGH;
	GPIO_Pin_Struct.PuPd = GPIO_PUPD_PULLDOWN;
	GPIO_Init(GPIOA, &GPIO_Pin_Struct);

	memset(&GPIO_Pin_Struct, 0 , sizeof(GPIO_Pin_Struct));
//*****************FOR EXTI PIN*****************************************

	//EXTI_LineConfig(EXTI_PortSource_GPIOA, EXTI_LineSource_0);

}

static void LockControl()
{
	RCC_GPIOA_CLK_ENABLE();
	//GPIO_InitTypeDef_t GPIO_Pin_Struct = {0};

	GPIO_Pin_Struct.pinNumber = GPIO_PIN_0;
	GPIO_Pin_Struct.Mode = GPIO_MODE_OUTPUT;
	GPIO_Pin_Struct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Pin_Struct);


}

static void GPIO_Button_Interrupt()
{

	EXTI_InitTypeDef_t EXTI_InitStruct = {0};
	RCC_SYSCFG_CLK_ENABLE();
	EXTI_LineConfig(EXTI_PortSource_GPIOA, EXTI_LineSource_0);

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_LineNumber = EXTI_LineSource_0;
	EXTI_InitStruct.EXTI_Mode = EXTI_MODE_Inerrupt;
	EXTI_InitStruct.TriggerSelection = EXTI_Trigger_RisingEdge;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_EnableInterrupt(EXTI0_IRQNumber);

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


