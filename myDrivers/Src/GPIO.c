/*
 * GPIO.c
 *
 *  Created on: 11 Mar 2023
 *      Author: Oğuz Kaan
 */

#include"GPIO.h"


/**************************************************************************
 * @brief   GPIO_Init configures ports and pins
 *
 * @param	GPIOx = GPIO Port Base Address like A or D
 *
 * @param	GPIO_ConfigStruct = User Config Structure
 *
 * @retval  Void
 *
 * */
void GPIO_Init(GPIO_TypeDef_t *GPIOx, GPIO_InitTypeDef_t *GPIO_ConfigStruct )
{
	uint32_t position;
	uint32_t fakePosition =0;
	uint32_t lastPosition =0;

	for(position = 0 ; position <16	; position++)
	{																												// pin number 1
		fakePosition = (0x1 << position);											// 0000 0000 0000 0001			0000 0000 0000 0001
		lastPosition = (uint32_t)(GPIO_ConfigStruct->pinNumber ) & fakePosition;	//

		if(fakePosition == lastPosition)
		{
			/* MODE CONFIG               */
			uint32_t tempValue = GPIOx->MODER;

			tempValue  &= ~(0x3U << (position*2));
			tempValue |=  (GPIO_ConfigStruct->Mode << (position *2));

			GPIOx->MODER = tempValue;
			// ******************************************************

			if(GPIO_ConfigStruct->Mode == GPIO_MODE_OUTPUT || GPIO_ConfigStruct->Mode == GPIO_MODE_AF )
			{
				/* Output Type CONFIG               */
				tempValue = GPIOx->OTYPER;
				tempValue &= ~(0x1U << position); 	//clear bit
				tempValue |= (GPIO_ConfigStruct->Otype  << position);

				GPIOx->OTYPER = tempValue;

				/* Output Speed CONFIG               */
				tempValue = GPIOx->OSPEEDR;
				tempValue &=~(0x3U << (position*2));
				tempValue |= (GPIO_ConfigStruct->Speed << (position*2));
				GPIOx->OSPEEDR = tempValue;

			}

			/* Push Pull CONFIG               */
			tempValue = GPIOx->PUPDR;
			tempValue &=~(0x3U << (position*2));
			tempValue |= (GPIO_ConfigStruct->PuPd << (position*2));
			GPIOx->PUPDR = tempValue;




		if(GPIO_ConfigStruct->Mode == GPIO_MODE_AF)
		{
			uint32_t dummy =0;

			dummy = GPIOx->AFR[position >> 3U];
			dummy &=~(0xFU << ((position & 0x7U )*4) );
			dummy |= (GPIO_ConfigStruct->Alternate << ((position & 0x7U )*4) );
			GPIOx->AFR[position >> 3U] = dummy;


		}

		}

	}

}


/**************************************************************************
 * @brief   GPIO_Write_Pin makes pins HIGH or LOW
 *
 * @param	GPIOx = GPIO Port Base Address like A or D
 *
 * @param   pinNumber = GPIO Pin Numbers 0-15
 *
 * @param   pinState = GPIO_Pin_Set or GPIO_Pin_Reset
 *
 * @retval  Void
 *
 * */

void GPIO_Write_Pin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber, GPIO_PinState_t pinState)
{

	/* Pinleri Set ve Reset etmek için GPIO Pin Set Reset register kısmında 32 bitimiz var.
	 * 0-15 bit set için set olmalı	0x1
	 * 16-31 bit reset için	set olmalı 0x1
	 * bütün yazılan 0x0'lar işlevsiz
	 *  */

	if(pinState == GPIO_Pin_Set )
	{
		GPIOx->BSRR = pinNumber;              // 12 13 pinleri için 0011 0000 0000 0000       // BSRR bit set/reset register
	}
	else
	{
		GPIOx->BSRR = (pinNumber << 16U);	  // 16 bit kadydırılır pin reset
	}
}


/**************************************************************************
 *  @brief	  GPIO_ReadPin reads the pins of GPIOx Port
 *
 *  @param	  GPIOx = GPIO Port Base Address like A or D
 *  @param	  pinNumber = GPIO_PIN_Numbers between 0-15
 *
 *  @retvalue GPIO_PinState_t
 * */

GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{

	GPIO_PinState_t bitStatus = GPIO_Pin_Reset;				// before read makes status reset

	if((GPIOx->IDR & pinNumber ) != GPIO_Pin_Reset ) 	   // IDR (has 16 bits) = GPIO port input data register, read only
	{
		bitStatus = GPIO_Pin_Set;   					  // If condition is true then there is data in register , return bitstatus as high
	}

	return bitStatus;
}

/**************************************************************************
 *  @brief	  GPIO_LockPin Lock the pins configration of GPIOx Port
 *
 *  @param	  GPIOx = GPIO Port Base Address like A or D
 *  @param 	  pinNumber = GPIO_PIN_Numbers between 0-15
 *
 *  @retvalue Void
 * */

void GPIO_LockPin(GPIO_TypeDef_t *GPIOx , uint16_t pinNumber)
{
	/*
	 *  LOCK key write sequence:
		WR LCKR[16] = ‘1’ + LCKR[15:0]
		WR LCKR[16] = ‘0’ + LCKR[15:0]
		WR LCKR[16] = ‘1’ + LCKR[15:0]
		RD LCKR                        */

	uint32_t tempValue = (0x1 << 16U) | pinNumber;		// makes 16th bit "1" and 0-15 bits are my choice 	1000 0000 0000 0000

	GPIOx->LCKR = tempValue;							// LCKR[16] = "1"   ,  LCKR[0:15] = DATA

	GPIOx->LCKR = pinNumber;							// LCKR[16] = "0"   ,  LCKR[0:15] = DATA

	GPIOx->LCKR = tempValue;							// LCKR[16] = "1"   ,  LCKR[0:15] = DATA

	tempValue = GPIOx->LCKR;							// Read Lock Register

}

/**************************************************************************
 *  @brief	  GPIO_TogglePin toggling the pins
 *
 *  @param	  GPIOx = GPIO Port Base Address like A or D
 *  @param 	  pinNumber = GPIO_PIN_Numbers between 0-15
 *
 *  @retvalue Void
 * */
void GPIO_TogglePin(GPIO_TypeDef_t *GPIOx , uint16_t pinNumber)
{

	uint32_t tempODRRegister = GPIOx->ODR;
	GPIOx->BSRR = ((tempODRRegister & pinNumber) << 16U ) | ~(tempODRRegister & pinNumber);		//  read ODR register and save the bits, then compare pinNumber

}


