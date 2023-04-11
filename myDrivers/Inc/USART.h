/*
 * USART.h
 *
 *  Created on: 31 Mar 2023
 *      Author: Oğuz Kaan
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include<stm32f411xx.h>




/*
 * @def_group UART_MODE
 * */
#define USART_MODE_Tx				((uint32_t)(0x00000008))
#define USART_MODE_Rx				((uint32_t)(0x00000004))
#define USART_MODE_Tx_Rx			((uint32_t)(0x0000000C))

/*
 * @def_group USART_WordLength
 * */
#define USART_WORDLENGTH_8BITS		((uint32_t)(0x00000000))
#define USART_WORDLENGTH_9BITS		((uint32_t)(0x00001000)) // 0x0001 0000 0000 0000

/*
 * @def_group USART_ParityModes
 * */
#define USART_PARITY_NONE			((uint32_t)(0x00000000))
#define USART_PARITY_Even			((uint32_t)(0x00000400))
#define USART_PARITY_Odd			((uint32_t)(0x00000600))

/*
 *  @def_group USART_StopBits
 * */
#define USART_STOPBIT_ONE			((uint32_t)(0x00000000))
#define USART_STOPBIT_HALF			((uint32_t)(0x00001000)) // 0001 0000 0000 0000
#define USART_STOPBIT_TWO			((uint32_t)(0x00002000))
#define USART_STOPBIT_ONEHALF		((uint32_t)(0x00003000))

/*
 *  @def_group USART_BaudRate
 * */
#define USART_BAUD_16				((uint32_t)(0x00000000))
#define USART_BAUD_8				((uint32_t)(0x00008000))

/*
 *  @def_group USART_HardWareFlowControl
 * */
#define USART_HW_NONE				((uint32_t)(0x00000000))
#define USART_HW_CTS				((uint32_t)(0x00000200))
#define USART_HW_RTS				((uint32_t)(0x00000100))
#define USART_HW_CTS_RTS			((uint32_t)(0x00000300))


/*
 *  @def_group USART_OverSampling
 * */
#define USART_OVERSAMPLE_8			((uint32_t)(0x00008000))
#define USART_OVERSAMPLE_16			((uint32_t)(0x00000000))



typedef enum
{
	USART_FLAG_RESET = 0x0U,
	USART_FLAG_SET	= !USART_FLAG_RESET


}USART_FlagStatus_t;


typedef enum
{
	USART_BUS_FREE = 0x0U,
	USART_BUS_Tx =  0x1U,
	USART_BUS_Rx = 0x2U

}USART_BusState_t;


#define __USART_DIV_VALUE_16(__CLOCK__ , __BAUDRATE__)			( ( 25U *(uint32_t)(__CLOCK__ )) / ( 4U *(uint32_t)(__BAUDRATE__) ) )
#define __USART_DIV_VALUE_8(__CLOCK__ , __BAUDRATE__)			( ( 25U *(uint32_t)(__CLOCK__ )) / ( 2U *(uint32_t)(__BAUDRATE__) ) )


typedef struct
{
	uint32_t Mode;						/*!< Transmission and Reception modes                         @def_group USART_MODE          		 */
	uint32_t BaudRate;					/*!< BaudRate modes                                           @def_group USART_BaudRate     		 */
	uint32_t WordLength;				/*!< Word Length modes                                        @def_group USART_WordLength  		     */
	uint32_t Parity;					/*!< Even & Odd parity modes                                  @def_group USART_ParityModes 		     */
	uint32_t OverSampling;				/*!< Over Sampling modes                                      @def_group USART_OverSampling 		 */
	uint32_t StopBits;					/*!< STOP Bits modes                                          @def_group USART_StopBits              */
	uint32_t HardWareFlowControl;       /*!< HardWare Flow Control modes                              @def_group USART_HardWareFlowControl   */


}USART_InitTypeDef_t;

typedef struct __USART_HandleTypeDef_t
{
	USART_TypeDef_t *Instance;
	USART_InitTypeDef_t Init;
	uint8_t *pTxBuffer;
	uint16_t TxBufferSize;
	uint8_t TxStatus;

	void (*TxISR_Fuction)( struct __USART_HandleTypeDef_t *USART_Handle );

	uint8_t *pRxBuffer;
	uint16_t RxBufferSize;
	uint8_t RxStatus;

	void (*RxISR_Fuction)( struct __USART_HandleTypeDef_t *USART_Handle );

}USART_HandleTypeDef_t;

void USART_Init(USART_HandleTypeDef_t *USART_Handle);
void USART_TransmitData(USART_HandleTypeDef_t *USART_Handle , uint8_t *pData, uint16_t dataSize);
void USART_TransmitData_IT (USART_HandleTypeDef_t *USART_Handle , uint8_t *pData, uint16_t dataSize);
void USART_ReceiveData(USART_HandleTypeDef_t *USART_Handle , uint8_t *pBuffer , uint16_t sizeOfData);
void USART_ReceiveData_IT (USART_HandleTypeDef_t *USART_Handle , uint8_t *pBuffer , uint16_t dataSize);
void USART_PeriphCMD (USART_HandleTypeDef_t *USART_Handle , FunctionalState_t stateOfUSART);
void USART_InterruptHandler( USART_HandleTypeDef_t *USART_Handle );
USART_FlagStatus_t USART_GetFlagStatus(USART_HandleTypeDef_t *USART_Handle , uint16_t flagName);

#endif /* INC_USART_H_ */
