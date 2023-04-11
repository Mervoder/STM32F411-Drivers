/*
 * EXTI.h
 *
 *  Created on: 18 Mar 2023
 *      Author: Oğuz Kaan
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include"stm32f411xx.h"


/*
 * @def_group 	Port_Values
 *
 */
#define EXTI_PortSource_GPIOA			( (uint8_t)(0x00) )
#define EXTI_PortSource_GPIOB			( (uint8_t)(0x01) )
#define EXTI_PortSource_GPIOC			( (uint8_t)(0x02) )
#define EXTI_PortSource_GPIOD			( (uint8_t)(0x03) )
#define EXTI_PortSource_GPIOE			( (uint8_t)(0x04) )
#define EXTI_PortSource_GPIOH			( (uint8_t)(0x07) )

/*
 * @def_group EXTI Line_Values
 *
 */
#define EXTI_LineSource_0				( (uint8_t)(0x00) )
#define EXTI_LineSource_1				( (uint8_t)(0x01) )
#define EXTI_LineSource_2				( (uint8_t)(0x02) )
#define EXTI_LineSource_3				( (uint8_t)(0x03) )
#define EXTI_LineSource_4				( (uint8_t)(0x04) )
#define EXTI_LineSource_5				( (uint8_t)(0x05) )
#define EXTI_LineSource_6				( (uint8_t)(0x06) )
#define EXTI_LineSource_7				( (uint8_t)(0x07) )
#define EXTI_LineSource_8				( (uint8_t)(0x08) )
#define EXTI_LineSource_9				( (uint8_t)(0x09) )
#define EXTI_LineSource_10				( (uint8_t)(0x0A) )
#define EXTI_LineSource_11				( (uint8_t)(0x0B) )
#define EXTI_LineSource_12				( (uint8_t)(0x0C) )
#define EXTI_LineSource_13				( (uint8_t)(0x0D) )
#define EXTI_LineSource_14				( (uint8_t)(0x0E) )
#define EXTI_LineSource_15				( (uint8_t)(0x0F) )


/*
 * @def_group EXTI Mode Numbers
 *
 */
#define EXTI_MODE_Inerrupt 				(0x00U)
#define EXTI_MODe_EVENT					(0x04U)

/*
 * @def_group EXTI Trigger Values
 *
 */
#define EXTI_Trigger_RisingEdge 		(0x08U)
#define EXTI_Trigger_FallingEdge 		(0x0CU)
#define EXTI_Trigger_RFEdge 			(0x10U)

typedef struct
{
	uint8_t	EXTI_LineNumber;			 /*!< EXTI Line number for valid GPIO pin 	@def_group  EXTI Line_Values */
	uint8_t TriggerSelection;			/*!<  EXTI Trigger Selection values  		@def_group EXTI Trigger Values */
	uint8_t EXTI_Mode;					/*!<  EXTI Mode numbers 				    @def_group EXTI Mode Numbers */
	FunctionalState_t EXTI_LineCmd;		/*!< Mask or Unmask the line number									 */

}EXTI_InitTypeDef_t;


void EXTI_Init(EXTI_InitTypeDef_t * EXTI_InitStruct);

void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource);

void NVIC_EnableInterrupt(IRQNumber_TypeDef_t IRQNumber);






#endif /* INC_EXTI_H_ */
