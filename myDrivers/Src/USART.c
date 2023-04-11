/*
 * USART.c
 *
 *  Created on: 31 Mar 2023
 *      Author: Oğuz Kaan
 */


#include<USART.h>


static void closeUSART_ISR_TX(USART_HandleTypeDef_t *USART_Handle)
{
	USART_Handle->TxBufferSize = 0;
	USART_Handle->pTxBuffer = NULL;
	USART_Handle->TxStatus = USART_BUS_FREE;

	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_TxEIE);


}


static void closeUSART_ISR_RX (USART_HandleTypeDef_t *USART_Handle)
{
	USART_Handle->RxBufferSize =0;
	USART_Handle->pRxBuffer = NULL;
	USART_Handle->RxStatus = USART_BUS_FREE;


	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_RxNEIE);
}



static void USART_SendWith_IT( USART_HandleTypeDef_t *USART_Handle )
{

	if((USART_Handle->Init.WordLength  == USART_WORDLENGTH_9BITS)  && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{

		uint16_t *p16BitsData = (uint16_t*)( USART_Handle->pTxBuffer ) ;

		USART_Handle->Instance->DR = (uint16_t)(*p16BitsData & (uint16_t)(0x01FF) );

		USART_Handle->pTxBuffer += sizeof(uint16_t);
		USART_Handle->TxBufferSize -=2;

	}
	else
	{
		USART_Handle->Instance->DR = (uint8_t)(*(USART_Handle->pTxBuffer ) & (uint8_t)(0x00FF));

		USART_Handle->pTxBuffer ++;
		USART_Handle->TxBufferSize --;
	}
	if(USART_Handle->TxBufferSize == 0)
	{
		closeUSART_ISR_TX(USART_Handle);
	}

}


static void USART_ReceiveWith_IT(USART_HandleTypeDef_t *USART_Handle)
{
	uint16_t *p16BitsBuffer;
	uint8_t *p8BitsBuffer;



	if((USART_Handle->Init.WordLength  == USART_WORDLENGTH_9BITS)  && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		p16BitsBuffer = (uint16_t*)USART_Handle->pRxBuffer;

		p8BitsBuffer = NULL;

	}
	else
	{
		p8BitsBuffer = (uint8_t*)USART_Handle->pRxBuffer;

		p16BitsBuffer = NULL;

	}

	if( p8BitsBuffer == NULL )
	{
		*p16BitsBuffer = (uint16_t)(USART_Handle->Instance->DR & 0x01FFU);

		USART_Handle->pRxBuffer += sizeof(uint16_t);
		USART_Handle->RxBufferSize -=2;
	}
	else
	{
		if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity != USART_PARITY_NONE) )
		{
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);

			USART_Handle->pRxBuffer ++;
			USART_Handle->RxBufferSize --;
		}
		else if((USART_Handle->Init.WordLength == USART_WORDLENGTH_8BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE))
		{
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
			USART_Handle->pRxBuffer ++;
			USART_Handle->RxBufferSize --;
		}
		else
		{
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR & 0x07FU);
			USART_Handle->pRxBuffer ++;
			USART_Handle->RxBufferSize --;
		}
	}

	if( USART_Handle->RxBufferSize == 0)
	{
		closeUSART_ISR_RX(USART_Handle);
	}

}



/**************************************************************************
 * @brief   USART_Init configures USART Peripheral
 *
 * @param	USART_HandleTypeDef_t = User Config Structure
 *
 * @retval  Void
 *
 * */
void USART_Init(USART_HandleTypeDef_t *USART_Handle)
{
	uint32_t tempReg =0;
	uint32_t periphClock =0;
	uint32_t mantissaPart = 0;
	uint32_t fractionPart = 0;
	uint32_t USART_DIV_Val = 0;
	uint32_t tempVal = 0;

	/*****************************CR1*******************************************************/
	/**********OVERSAMPLING  WORDLENGTH  MODE  PARITY  *************************************/

	tempReg = USART_Handle->Instance->CR1;

	tempReg |= (USART_Handle->Init.OverSampling) | (USART_Handle->Init.WordLength) | (USART_Handle->Init.Mode) |(USART_Handle->Init.Parity);

    USART_Handle->Instance->CR1 = tempReg;

    /*****************************CR2******************************************************/
    /**********STOPBITS *******************************************************************/
    tempReg =  USART_Handle->Instance->CR2;

    tempReg &= ~(0x3U << USART_CR2_STOP);

    tempReg |= (USART_Handle->Init.StopBits) ;

    USART_Handle->Instance->CR2 = tempReg;

    /*****************************CR3*******************************************************/
    /**********HARDWAREFLOWCONTROL   *******************************************************/
    tempReg =  USART_Handle->Instance->CR3;

    tempReg |= (USART_Handle->Init.HardWareFlowControl) ;

    USART_Handle->Instance->CR3 = tempReg;


    /**********BAUDRATE CONFIGRATION   *****************************************************/
    if((USART_Handle->Instance = USART1) || (USART_Handle->Instance = USART6) )
    {

    	periphClock = RCC_GetPClock2();


    }
    else
    {
    	periphClock = RCC_GetPClock1();

    }

    if(USART_Handle->Init.OverSampling == USART_OVERSAMPLE_8)
    {

    	USART_DIV_Val = __USART_DIV_VALUE_8(periphClock , USART_Handle->Init.BaudRate);

    	mantissaPart = (USART_DIV_Val / 100U);
    	fractionPart = (USART_DIV_Val) - (mantissaPart * 100U);

    	fractionPart =  ((( (fractionPart * 8U) + 50U ) / 100U ) & (0x07U));


    }
    else
    {

    	USART_DIV_Val = __USART_DIV_VALUE_16(periphClock , USART_Handle->Init.BaudRate);

    	mantissaPart = (USART_DIV_Val / 100U);
    	fractionPart = (USART_DIV_Val) - (mantissaPart * 100U);

    	fractionPart =  (( ((fractionPart * 16U ) + 50U ) / 100U ) & 0x0FU );

    }

    tempVal |= ( mantissaPart << 4U);
    tempVal |= (fractionPart << 0U);

   USART_Handle->Instance->BRR = tempVal;

}



/**************************************************************************
 * @brief   USART_TransmitData Transmits data
 *
 * @param	USART_HandleTypeDef_t = User Config Structure
 *
 * @param	pData = Address of data that will send
 *
 * @param	dataSize = Length of the data that will send in bytes
 *
 * @retval  Void
 *
 * */
void USART_TransmitData(USART_HandleTypeDef_t *USART_Handle , uint8_t *pData, uint16_t dataSize)
{

	// 9 bit = frame no parity 	// 9 bit = frame yes parity
	// 8 bit = frame no parity	// 8 bit = frame yes parity

	uint16_t *data16bits;

	if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS)  && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		// 9 bit = frame no parity
		data16bits = (uint16_t*)pData;

	}
	else
	{
		data16bits = NULL;
	}


	while(dataSize >0)
	{
		//while ((USART_Handle->Instance->SR & (0x1U << 7U)));
		while( !(USART_GetFlagStatus(USART_Handle , USART_TxE_Flag)) ); // flag check

		/* 9 Bits Data No Parity is for ELSE Condition , For Others You Will Be If Condition */
		if(data16bits == NULL )
		{
			USART_Handle->Instance->DR = (uint8_t)(*pData & 0xFFU);
			pData ++;
			dataSize --;


		}
		else
		{
			USART_Handle->Instance->DR =  (uint16_t)(*data16bits & (0x01FFU) ); // 0x1FF 9 Bits are 1
			data16bits ++;
			dataSize -=2;


		}



	}

	while( !(USART_GetFlagStatus(USART_Handle, USART_TC_Flag)) );


}




/**************************************************************************
 * @brief   USART_ReceiveData Receives the data
 *
 * @param 	USART_HandleTypeDef_t = User Config Structure
 *
 * @param	pBuffer = Address of the data to store values
 *
 * @param	sizeOfData = Length of your data in bytes
 *
 * @retval  Void
 *
 * */
void USART_ReceiveData(USART_HandleTypeDef_t *USART_Handle , uint8_t *pBuffer , uint16_t sizeOfData)
{
	uint16_t *p16BitsBuffer;
	uint8_t *p8BitsBuffer;


	if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		p16BitsBuffer = (uint16_t*)pBuffer;
		p8BitsBuffer = NULL;

	}
	else
	{
		p8BitsBuffer = (uint8_t*)pBuffer;
		p16BitsBuffer = NULL;
	}

	while (sizeOfData >0)
	{

		while( !(USART_GetFlagStatus(USART_Handle, USART_RxNE_Flag)) );

			/**************************** 9 Bits Data No Parity ******************************************/
		if(p8BitsBuffer == NULL)
		{
			*p16BitsBuffer = (uint16_t ) ( USART_Handle->Instance->DR & 0x1FFU); // to get 9 bits 0001 1111 1111

			pBuffer ++;
			sizeOfData -=2;
		}
		else
		{
			/**************************** 8 Bits Data 1 Parity ******************************************/
			if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity != USART_PARITY_NONE))
			{
				*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR  & 0x00FFU); // 0000 1111 1111

				pBuffer ++;
				sizeOfData --;
			}
			/**************************** 8 Bits Data No Parity ******************************************/
			else if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_8BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE))
			{
				*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR  & 0x00FFU); // 0000 1111 1111

				pBuffer ++;
				sizeOfData --;
			}
			/**************************** 8 Bits Data 1 Parity ******************************************/
			else
			{
				*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR  & 0x007FU); // 0000 0111 1111

				pBuffer ++;
				sizeOfData --;
			}
		 }

	}

}






/**************************************************************************
 * @brief   USART_TransmitData_IT Transmits data by using Interrupt
 *
 * @param	USART_HandleTypeDef_t = User Config Structure
 *
 * @param	pData = Address of data that will send
 *
 * @param	dataSize = Length of the data that will send in bytes
 *
 * @retval  Void
 *
 * */
void USART_TransmitData_IT (USART_HandleTypeDef_t *USART_Handle , uint8_t *pData, uint16_t dataSize)
{

	USART_BusState_t USART_BusState = USART_Handle->TxStatus;

	if(USART_BusState != USART_BUS_Tx)
	{
		USART_Handle->pTxBuffer = (uint8_t *) pData;
		USART_Handle->TxBufferSize = (uint16_t)dataSize;

		USART_Handle->TxStatus = USART_BUS_Tx;

		USART_Handle->TxISR_Fuction = USART_SendWith_IT;

		USART_Handle->Instance->CR1  |= (0x1U << USART_CR1_TxEIE);


	}

}



void USART_ReceiveData_IT (USART_HandleTypeDef_t *USART_Handle , uint8_t *pBuffer , uint16_t dataSize)
{

	USART_BusState_t USART_BusState = USART_Handle->RxStatus;

	if(USART_BusState != USART_BUS_Rx)
	{
		USART_Handle->pRxBuffer = (uint8_t*) pBuffer;
		USART_Handle->RxBufferSize = (uint16_t)dataSize;
		USART_Handle->RxStatus = USART_BUS_Rx;

		USART_Handle->RxISR_Fuction = USART_ReceiveWith_IT;

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_RxNEIE);

	}


}







/**************************************************************************
 * @brief   USART_PeriphCMD ENABLE or DISABLE the USART Peripheral
 *
 * @param	USART_HandleTypeDef_t = User config Structure
 *
 * @param	FunctionalState_t = State Of the USART
 *
 * @retval  Void
 *
 * */
void USART_PeriphCMD (USART_HandleTypeDef_t *USART_Handle , FunctionalState_t stateOfUSART)
{

	if(stateOfUSART == ENABLE )
	{
		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_UE);

	}
	else
	{
		USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_UE);
	}

}



/**************************************************************************
 * @brief   USART_FlagStatus_t, returns flag of SR register
 *
 * @param	USART_HandleTypeDef_t = User Config Structure
 *
 * @param	flagName = Flag name of SR register
 *
 * @retval  USART_FlagStatus_t
 *
 * */
USART_FlagStatus_t USART_GetFlagStatus(USART_HandleTypeDef_t *USART_Handle , uint16_t flagName)
{

		return ((USART_Handle->Instance->SR & flagName ) ? USART_FLAG_SET : USART_FLAG_RESET);
/*	if((USART_Handle->Instance->SR & flagName) == 1)
	{
		return USART_FLAG_SET;
	}
	else
	{
		return USART_FLAG_RESET;
	}*/
}




void USART_InterruptHandler( USART_HandleTypeDef_t *USART_Handle )
{

	uint8_t flagValue = 0;
	uint8_t interruptValue = 0;

	flagValue = (uint8_t)( ( USART_Handle->Instance->SR >> 7U ) & (0x1U) );
	interruptValue = (uint8_t)( ( USART_Handle->Instance->CR1 >> 7U ) & (0x1U) );

	if( flagValue && interruptValue )
	{
		USART_Handle->TxISR_Fuction(USART_Handle);

	}


	flagValue = (uint8_t)( ( USART_Handle->Instance->SR >> 5U ) & (0x1U) );
	interruptValue = (uint8_t)( ( USART_Handle->Instance->CR1 >> 5U ) & (0x1U) );

	if( flagValue && interruptValue )
	{
		USART_Handle->RxISR_Fuction(USART_Handle);

	}


}





