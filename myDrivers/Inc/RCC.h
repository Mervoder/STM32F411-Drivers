/*
 * RCC.h
 *
 *  Created on: 10 Mar 2023
 *      Author: Oğuz Kaan
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include"stm32f411xx.h"
/*
 *
 * RCC AHB1 Peripheral Macro Definitions
 *
 *
 * */

#define RCC_GPIOA_CLK_ENABLE()			do { uint32_t temp_Value = 0;											\
																												\
											SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);							\
											temp_Value = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);	        \
											UNUSED(temp_Value);													\
																												\
											}while(0)


#define RCC_GPIOB_CLK_ENABLE()  			RCC->AHB1ENR |= (0x1 << 1)
/*do{ uint32_t dummy=0; \
											SET_BIT(RCC->AHB1ENR , RCC_AHB1ENR_GPIOBEN);\
											dummy= READ_BIT(RCC->AHB1ENR , RCC_AHB1ENR_GPIOBEN);\
											UNUSED(dummy);\
											}while(0)*/


#define RCC_GPIOC_CLK_ENABLE()  			RCC->AHB1ENR |= (0x1 << 2)
/*do{ uint32_t dummy=0; \
											SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);\
											dummy= READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);\
											UNUSED(dummy);\
											}while(0)
*/

#define RCC_GPIOD_CLK_ENABLE()  			RCC->AHB1ENR |= (0x1 << 3) /*do{ uint32_t dummy=0; \
											SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
											dummy= READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
											UNUSED(dummy);\
											}while(0)*/


#define RCC_GPIOE_CLK_ENABLE()  			RCC->AHB1ENR |= (0x1 << 4) /*do{ uint32_t dummy=0; \
											SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
											dummy = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);\
											UNUSED(dummy);\
											}while(0)*/


#define RCC_GPIOH_CLK_ENABLE()  			RCC->AHB1ENR |= (0x1 << 7) /*do{ uint32_t dummy=0; \
											SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);\
											dummy= READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN );\
											UNUSED(dummy);\
											}while(0)
*/


#define RCC_SYSCFG_CLK_ENABLE()				RCC->APB2ENR |= (0x1 << 14)
/*do { uint32_t dummy	= 0;		\
												SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SYSCFG_Pos);					\
											dummy =	READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SYSCFG_Pos);					\
											UNUSED(dummy);						\
																	\
												}while(0)*/




#define RCC_ALL_GPIO_CLK_ENABLE()				RCC->AHB1ENR |= (0x9F <<0)

#define RCC_GPIOA_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN)

#define RCC_GPIOB_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN)

#define RCC_GPIOC_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN)

#define RCC_GPIOD_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN)

#define RCC_GPIOE_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN)

#define RCC_GPIOH_CLK_DISABLE()					CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN)


/*
 *
 * RCC APB1 Peripherals Clock Control Macro Definitions
 *
 * */

#define RCC_SPI2_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
													SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);					\
													dummy = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);	\
													UNUSED(dummy);			\
																	\
												}while(0)

#define RCC_SPI2_CLK_DISABLE()					CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN)


#define RCC_SPI3_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
													SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);					\
													dummy = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);	\
													UNUSED(dummy);			\
																	\
												}while(0)

#define RCC_SPI3_CLK_DISABLE()					CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN)


#define RCC_USART2_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
												SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);								\
												dummy = READ_BIT(RCC->APB2ENR ,RCC_APB1ENR_USART2EN);								\
												UNUSED(dummy);								\
																				\
												}while(0)

#define RCC_USART2_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR , RCC_APB1ENR_USART2EN )


#define RCC_I2C1_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
												SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);								\
												dummy = READ_BIT(RCC->APB2ENR ,RCC_APB1ENR_I2C1EN);								\
												UNUSED(dummy);								\
																				\
												}while(0)

#define RCC_I2C1_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR , RCC_APB1ENR_I2C1EN )



#define RCC_I2C2_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
												SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C2EN);								\
												dummy = READ_BIT(RCC->APB2ENR ,RCC_APB1ENR_I2C2EN);								\
												UNUSED(dummy);								\
																				\
												}while(0)

#define RCC_I2C2_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR , RCC_APB1ENR_I2C2EN )


#define RCC_I2C3_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
												SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);								\
												dummy = READ_BIT(RCC->APB2ENR ,RCC_APB1ENR_I2C3EN);								\
												UNUSED(dummy);								\
																				\
												}while(0)

#define RCC_I2C3_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR , RCC_APB1ENR_I2C3EN )


/*
 *
 * RCC APB2 Peripherals Clock Control Macro Definitions
 *
 * */

#define RCC_SPI1_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
												SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);								\
												dummy = READ_BIT(RCC->APB2ENR ,RCC_APB2ENR_SPI1EN);								\
												UNUSED(dummy);								\
																				\
												}while(0)

#define RCC_SPI1_CLK_DISABLE()					CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN)


#define RCC_SPI4_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
													SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);					\
													dummy = READ_BIT(RCC->APB2ENR , RCC_APB2ENR_SPI4EN);	\
													UNUSED(dummy);			\
																	\
												}while(0)

#define RCC_SPI4_CLK_DISABLE()					CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN)


#define RCC_SPI5_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
													SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);					\
													dummy = READ_BIT(RCC->APB2ENR , RCC_APB2ENR_SPI5EN);	\
													UNUSED(dummy);			\
																	\
												}while(0)


#define RCC_SPI5_CLK_DISABLE()					CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN)



#define RCC_USART1_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
												SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);								\
												dummy = READ_BIT(RCC->APB2ENR ,RCC_APB2ENR_USART1EN);								\
												UNUSED(dummy);								\
																				\
												}while(0)

#define RCC_USART1_CLK_DISABLE()				CLEAR_BIT(RCC.APB2_BASE_ADDR , RCC_APB2ENR_USART1EN)



#define RCC_USART6_CLK_ENABLE()					do { uint32_t dummy	= 0;		\
												SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART6EN);								\
												dummy = READ_BIT(RCC->APB2ENR ,RCC_APB2ENR_USART6EN);								\
												UNUSED(dummy);								\
																				\
												}while(0)

#define RCC_USART6_CLK_DISABLE()				CLEAR_BIT(RCC.APB2_BASE_ADDR , RCC_APB2ENR_USART6EN)


uint32_t RCC_GetSystemClock(void);
uint32_t RCC_GetHClock(void);
uint32_t RCC_GetPClock1(void);
uint32_t RCC_GetPClock2(void);

#endif /* INC_RCC_H_ */
