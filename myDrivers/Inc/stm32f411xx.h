/*
 * stm32f411xx.h
 *
 *  Created on: 8 Mar 2023
 *      Author: Oğuz Kaan ATAY
 *      atay.oguzkaan@gmail.com
 *
 */

#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_

#include<stdint.h>   // Bu kütüphaneyi dahil etme sebebimiz uint32_t tanımlamalarını kullanabilmek
#include<string.h>	 // memset tarzı hazır fonksiyonları kullanabilmek için gerekli kütüphane
#include <stddef.h>

/**
 *
 *	MICRO PROCECSSOR DEFINES
 */
#define NVIC_ISER0      		((uint32_t*)(0xE000E100UL))

//*****************************************************************************************************

#define __IO volatile

#define SET_BIT(REG,BIT) 		((REG) |= (BIT))  // Uygun registera biti yaz
#define CLEAR_BIT(REG,BIT)      ((REG)&= ~(BIT))  // Uygun bitin not'ı ile and kullanarak temizliyor
#define READ_BIT(REG,BIT)		((REG) & (BIT) )  // Uygun biti okumak için
#define UNUSED(x)				(void)x			  // Kullanılmayan değişkenler için macro

/**
 *
 *	IRQ Numbers of MCU == Vector Table
 */
typedef enum
{
	EXTI0_IRQNumber = 6,
	EXTI1_IRQNumber = 7,
	EXTI2_IRQNumber = 8,
	EXTI3_IRQNumber = 9,
	EXTI4_IRQNumber = 10,

	SPI1_IRQNumber = 35,
	SPI2_IRQNumber = 36,
	SPI3_IRQNumber = 51,
	SPI4_IRQNumber = 84,
	SPI5_IRQNumber = 85,

	USART1_IRQNumber =37,
	USART2_IRQNumber =38


}IRQNumber_TypeDef_t;


typedef enum
{
	DISABLE = 0x0U,
	ENABLE = !DISABLE

}FunctionalState_t;


/*
 * Memory Base Address (Adres tanımlamaları kısmı)
 */

#define FLASH_BASE_ADDR						(0x08000000UL)		/* Flash Base Address (up to  512 KB) 						  */
#define SRAM_BASE_ADDR						(0x20000000UL) 	    /* SRAM Base Address 128 KB , There is only one SRAM 		  */



/*
 * Peripheral Base Address (Çevresel birim tanımlamaları)
 */

#define PERIPH_BASE_ADDR 					(0x40000000UL) 		                 /* Base address for ALL peripherals  						    */

#define APB1_BASE_ADDR 						 PERIPH_BASE_ADDR    		         /* APB1 Bus Domain Base Address                                */
#define APB2_BASE_ADDR 						(PERIPH_BASE_ADDR + 0x00010000UL)    /* APB2 Bus Base Address                                       */
#define AHB1_BASE_ADDR 						(PERIPH_BASE_ADDR + 0x00020000UL)    /* AHB1 Bus Base Address                                       */
#define AHB2_BASE_ADDR 						(PERIPH_BASE_ADDR + 0x10000000UL)    /* AHB1 Bus Base Address                                       */


/*
 * APB1 Peripherals Base Address (APB1 hattı çevresel birimleri)
 */

#define TIM2_BASE_ADDR 						(APB1_BASE_ADDR + 0x0000UL)     /* Timer 2 Base Address                              */
#define TIM3_BASE_ADDR						(APB1_BASE_ADDR + 0x0400UL)		/* Timer 3 Base Address                              */
#define TIM4_BASE_ADDR						(APB1_BASE_ADDR + 0x0800UL)		/* Timer 4 Base Address                              */
#define TIM5_BASE_ADDR						(APB1_BASE_ADDR + 0x0C00UL)		/* Timer 5 Base Address                              */

#define SPI2_BASE_ADDR						(APB1_BASE_ADDR + 0x3800UL)		/* SPI 2 Base Address                                */
#define SPI3_BASE_ADDR						(APB1_BASE_ADDR + 0x3C00UL)		/* SPI 3 Base Address                                */

#define USART2_BASE_ADDR					(APB1_BASE_ADDR + 0x4400UL)		/* USART 2 Base Address                              */

#define I2C1_BASE_ADDR					    (APB1_BASE_ADDR + 0x5400UL)		/* I2C 1 Base Address                                */
#define I2C2_BASE_ADDR					    (APB1_BASE_ADDR + 0x5800UL)		/* I2C 2 Base Address                                */
#define I2C3_BASE_ADDR					    (APB1_BASE_ADDR + 0x5C00UL)		/* I2C 3 Base Address                                */

#define PWR_BASE_ADDR					    (APB1_BASE_ADDR + 0x7000UL)		/* PWR   Base Address                                */

/*
 * APB2 Peripherals Base Address (APB2 hattı çevresel birimleri)
 */

#define TIM1_BASE_ADDR 						(APB2_BASE_ADDR + 0x0000UL)     /* Timer 1 Base Address                               */
#define TIM9_BASE_ADDR 						(APB2_BASE_ADDR + 0x4000UL)     /* Timer 9 Base Address                               */
#define TIM10_BASE_ADDR 					(APB2_BASE_ADDR + 0x4400UL)     /* Timer 10 Base Address                              */
#define TIM11_BASE_ADDR 					(APB2_BASE_ADDR + 0x4800UL)     /* Timer 11 Base Address                              */

#define USART1_BASE_ADDR 					(APB2_BASE_ADDR + 0x1000UL)     /* Usart 1 Base Address                               */
#define USART6_BASE_ADDR 					(APB2_BASE_ADDR + 0x1400UL)     /* Usart 6 Base Address                               */

#define ADC1_BASE_ADDR 					    (APB2_BASE_ADDR + 0x2000UL)     /* ADC 1 Base Address                                 */

#define SPI1_BASE_ADDR 					    (APB2_BASE_ADDR + 0x3000UL)     /* SPI 1 Base Address                                 */
#define SPI4_BASE_ADDR 					    (APB2_BASE_ADDR + 0x3400UL)     /* SPI 4 Base Address                                 */
#define SPI5_BASE_ADDR 					    (APB2_BASE_ADDR + 0x5000UL)     /* SPI 5 Base Address                                 */

#define SYSCFG_BASE_ADDR                    (APB2_BASE_ADDR + 0x3800UL)     /* System Configration  Base Address                  */
#define EXTI_BASE_ADDR						(APB2_BASE_ADDR + 0x3C00UL)		/* EXTI Base Address                                  */
#define SDIO_BASE_ADDR 					    (APB2_BASE_ADDR + 0x2C00UL)     /* SDIO Base Address                                  */


/*
 * AHB1 Peripherals Base Address (AHB1 hattı çevresel birimleri)
 */

#define GPIOA_BASE_ADDR                     (AHB1_BASE_ADDR + 0x0000UL)     /* GPIO A Base Address                                */
#define GPIOB_BASE_ADDR                     (AHB1_BASE_ADDR + 0x0400UL)     /* GPIO B Base Address                                */
#define GPIOC_BASE_ADDR                     (AHB1_BASE_ADDR + 0x0800UL)     /* GPIO C Base Address                                */
#define GPIOD_BASE_ADDR                     (AHB1_BASE_ADDR + 0x0C00UL)     /* GPIO D Base Address                                */
#define GPIOE_BASE_ADDR                     (AHB1_BASE_ADDR + 0x1000UL)     /* GPIO E Base Address                                */
#define GPIOH_BASE_ADDR                     (AHB1_BASE_ADDR + 0x1C00UL)     /* GPIO H Base Address                                */

#define CRC_BASE_ADDR                       (AHB1_BASE_ADDR + 0x3000UL)     /* CRC Base Address                                   */
#define RCC_BASE_ADDR                       (AHB1_BASE_ADDR + 0x3800UL)     /* RCC Base Address                                   */
#define DMA1_BASE_ADDR                      (AHB1_BASE_ADDR + 0x6000UL)     /* DMA 1 Base Address                                 */
#define DMA2_BASE_ADDR                      (AHB1_BASE_ADDR + 0x6400UL)     /* DMA 2 Base Address                                 */
#define FIR_BASE_ADDR                       (AHB1_BASE_ADDR + 0x3C00UL)     /* Flash Interface Register Base Address              */


/*
 * AHB2 Peripherals Base Address (AHB2 hattı çevresel birimleri)
 */

#define USB_OTG_FS_BASE_ADDR                (AHB2_BASE_ADDR + 0x0000UL)     /* USB ORG FS Base Address                               */



/*
 * Peripheral Structure Definitions (Çevresel yapı tanımlamaları)
 */


/*
	 Volatile yapısını kısaltmak için bir tanımlama yapıcaz   " __IO  "
	 Volatile olarak tanımlamazsanız optimizasyon sorunu çıkar
     Tekrar tekrar okunacak işler için optimize edilmesi lazım
     Gerçekte bir butondan veri okuyacaksanız kaç kere lazımsa okumanız lazım
	 voltaile koymazsak sadece 1 kere okuyup optimize edicekti ve ikinci basınçları algılamayacaktı                                   */


/**********************************************STRUCTRES********************************************************************************/

typedef struct
{
	volatile uint32_t MODER;              /*!< GPIO MODE Register                                 Address Offset = 0x0000             */
	__IO uint32_t OTYPER;				  /*!< GPIO output type Register                          Address Offset = 0x0004             */
	__IO uint32_t OSPEEDR;				  /*!< GPIO output speed Register                         Address Offset = 0x0008             */
	__IO uint32_t PUPDR;				  /*!< GPIO pull-up/pull-down Register                    Address Offset = 0x000C             */
	__IO uint32_t IDR;                    /*!< GPIO port input data Register                      Address Offset = 0x0010             */
	__IO uint32_t ODR;					  /*!< GPIO port output data Register                     Address Offset = 0x0014             */
	__IO uint32_t BSRR;                   /*!< GPIO port bit set/reset Register                   Address Offset = 0x0018             */
	__IO uint32_t LCKR;                   /*!< GPIO port configuration lock Register              Address Offset = 0x001C             */
	__IO uint32_t AFR[2];			      /*!< GPIO alternate function low/high register Register Address Offset = 0x0020/0x0024      */


}GPIO_TypeDef_t;   // _t struct tanımı olduğunu belirtmek için kullanılır


typedef struct
{
	__IO uint32_t  MEMRMP ;				/*!> Memory remap register register               						Address Offset = 0x00 */
	__IO uint32_t  PMC;					/*!> Peripheral mode configuration register             				Address Offset = 0x04 */
	__IO uint32_t  EXTICR[4];			/*!> External interrupt configuration register                      	Address Offset = 0x08 - 0x14 */
	__IO uint32_t  CMPCR;				/*!> Compensation cell control register             			   		Address Offset = 0x20 */

}SYSCFG_TypeDef_t;


typedef struct
{
	__IO uint32_t IMR;					/*!> Interrupt mask register             					    		Address Offset = 0x00 */
	__IO uint32_t EMR;					/*!> Event mask register             					   		        Address Offset = 0x04 */
	__IO uint32_t RTSR;					/*!> Rising trigger selection register            					   	Address Offset = 0x08 */
	__IO uint32_t FTSR;					/*!> Falling trigger selection register             			   		Address Offset = 0x0C */
	__IO uint32_t SWIER;				/*!> Software interrupt event register           				   		Address Offset = 0x10 */
	__IO uint32_t PR;					/*!> Pending register           					   		            Address Offset = 0x14 */


}EXTI_TypeDef_t;


typedef struct
{
	__IO uint32_t CR;					/* RCC clock control register                 							Address Offset = 0x00 */
	__IO uint32_t PLLCFGR;				/* RCC PLL configuration register             							Address Offset = 0x04 */
	__IO uint32_t CFGR;					/* RCC clock configuration register           							Address Offset = 0x08 */
	__IO uint32_t CIR;					/* RCC clock interrupt register               							Address Offset = 0x0C */
	__IO uint32_t AHB1RSTR;				/* RCC AHB1 peripheral reset register         							Address Offset = 0x10 */
	__IO uint32_t AHB2RSTR;				/* RCC AHB2 peripheral reset register         							Address Offset = 0x14 */
	__IO uint32_t RESERVED0[2];
	__IO uint32_t APB1RSTR;				/* RCC APB1 peripheral reset register        			 				Address Offset = 0x20 */
	__IO uint32_t APB2RSTR;				/* RCC APB2 peripheral reset register         							Address Offset = 0x24 */
	__IO uint32_t RESERVED1[2];
	__IO uint32_t AHB1ENR;				/* RCC AHB1 peripheral clock enable register 							Address Offset = 0x30 */
	__IO uint32_t AHB2ENR;				/* RCC AHB2 peripheral clock enable register  							Address Offset = 0x34 */
	__IO uint32_t RESERVED2[2];
	__IO uint32_t APB1ENR;				/* RCC APB1 peripheral clock enable register  							Address Offset = 0x40 */
	__IO uint32_t APB2ENR;				/* RCC APB2 peripheral clock enable register  							Address Offset = 0x44 */
	__IO uint32_t RESERVED3[2];
	__IO uint32_t AHB1LPENR;			/* RCC AHB1 peripheral clock enable in low power mode register  		Address Offset = 0x50 */
	__IO uint32_t AHB2LPENR;			/* RCC AHB2 peripheral clock enable in low power mode register  		Address Offset = 0x54 */
	__IO uint32_t RESERVED4[2];			/* */
	__IO uint32_t APB1LPENR;			/* RCC APB1 peripheral clock enable in low power mode register  		Address Offset = 0x60 */
	__IO uint32_t APB2LPENR;			/* RCC APB1 peripheral clock enable in low power mode register  		Address Offset = 0x64 */
	__IO uint32_t RESERVED5[2];
	__IO uint32_t BDCR;				    /* RCC Backup domain control register  									Address Offset = 0x70 */
	__IO uint32_t CSR;					/* RCC clock control & status register  								Address Offset = 0x74 */
	__IO uint32_t RESERVED6[2];
	__IO uint32_t SSCGR;				/* RCC spread spectrum clock generation register 						Address Offset = 0x80 */
	__IO uint32_t PLLI2SCFGR;			/* RCC PLLI2S configuration register  									Address Offset = 0x84 */
	__IO uint32_t RESERVED7;
	__IO uint32_t DCKCFGR;				/* RCC Dedicated Clocks Configuration Register  						Address Offset = 0x8C */


}RCC_TypeDef_t;


typedef struct
{
	__IO uint32_t CR1;					/*!> SPI control register 1             					    		Address Offset = 0x00 */
	__IO uint32_t CR2;					/*!> SPI control register 2             					    		Address Offset = 0x04 */
	__IO uint32_t SR;					/*!> SPI status register 	             					    		Address Offset = 0x08 */
	__IO uint32_t DR;					/*!> SPI data register            					    				Address Offset = 0x0C */
	__IO uint32_t CRCPR;				/*!> SPI CRC polynomial register         (not used in I2S mode)      	Address Offset = 0x10 */
	__IO uint32_t RXCRCR;				/*!> SPI RX CRC register                 (not used in I2S mode)	    	Address Offset = 0x14 */
	__IO uint32_t TXCRCR;				/*!> SPI TX CRC register             	 (not used in I2S mode)			Address Offset = 0x18 */
	__IO uint32_t I2SCFGR;				/*!> SPI_I2S configuration register        					    		Address Offset = 0x1C */
	__IO uint32_t I2SPR;				/*!> SPI_I2S prescaler register        	   					    		Address Offset = 0x20 */

} SPI_TypeDef_t;


typedef struct
{
	__IO uint32_t SR;					/*!> USART status register             					    			Address Offset = 0x00 */
	__IO uint32_t DR;					/*!> USART data register             					    			Address Offset = 0x04 */
	__IO uint32_t BRR;					/*!> USART baud rate register             				    			Address Offset = 0x08 */
	__IO uint32_t CR1;					/*!> USART control 1 register             				    			Address Offset = 0x0C */
	__IO uint32_t CR2;					/*!> USART control 2 register             				    			Address Offset = 0x10 */
	__IO uint32_t CR3;					/*!> USART control 3 register             				    			Address Offset = 0x14 */
	__IO uint32_t GTPR;					/*!> USART Guard time and prescaler register          	    			Address Offset = 0x18 */

}USART_TypeDef_t;


typedef struct
{
	__IO uint32_t CR1;					/*!> I2C Control register 1             					    	    Address Offset = 0x00 */
	__IO uint32_t CR2;					/*!> I2C Control register 2             					    	    Address Offset = 0x04 */
	__IO uint32_t OAR1;					/*!> I2C Own address register 1             				    	    Address Offset = 0x08 */
	__IO uint32_t OAR2;					/*!> I2C Own address register 2             				    	    Address Offset = 0x0C */
	__IO uint32_t DR;					/*!> I2C DATA register 			             				    	    Address Offset = 0x10 */
	__IO uint32_t SR1;					/*!> I2C Status register 1   		          				    	    Address Offset = 0x14 */
	__IO uint32_t SR2;					/*!> I2C Status register 2		             				    	    Address Offset = 0x18 */
	__IO uint32_t CCR;					/*!> I2C Clock control register              				    	    Address Offset = 0x1C */
	__IO uint32_t TRISE;				/*!> I2C TRISE register      		        				    	    Address Offset = 0x20 */
	__IO uint32_t FLTR;					/*!> I2C FLTR  register             		 				    	    Address Offset = 0x24 */


}I2C_TypeDef_t;

/*********************************** TYPE CAST ****************************************************************************************************/

#define GPIOA					((GPIO_TypeDef_t *)(GPIOA_BASE_ADDR)   )          /* Pointer kullanarak burdaki base adreslerini cast ediyoruz    */
#define GPIOB					((GPIO_TypeDef_t *)(GPIOB_BASE_ADDR)   )          /* bu sayede oluşturduğumuz structure yapısı içinde gezebiliriz */
#define GPIOC					((GPIO_TypeDef_t *)(GPIOC_BASE_ADDR)   )
#define GPIOD					((GPIO_TypeDef_t *)(GPIOD_BASE_ADDR)   )
#define GPIOE					((GPIO_TypeDef_t *)(GPIOE_BASE_ADDR)   )
#define GPIOH					((GPIO_TypeDef_t *)(GPIOH_BASE_ADDR)   )

#define SYSCFG 					((SYSCFG_TypeDef_t *)(SYSCFG_BASE_ADDR))

#define RCC 					((RCC_TypeDef_t *)(RCC_BASE_ADDR)      )

#define EXTI					((EXTI_TypeDef_t *)(EXTI_BASE_ADDR)    )

#define SPI1					((SPI_TypeDef_t*) (SPI1_BASE_ADDR)     )
#define SPI2					((SPI_TypeDef_t*) (SPI2_BASE_ADDR)     )
#define SPI3					((SPI_TypeDef_t*) (SPI3_BASE_ADDR)     )
#define SPI4					((SPI_TypeDef_t*) (SPI4_BASE_ADDR)     )
#define SPI5					((SPI_TypeDef_t*) (SPI5_BASE_ADDR)     )

#define I2C1					((I2C_TypeDef_t*)  (I2C1_BASE_ADDR)    )
#define I2C2					((I2C_TypeDef_t*)  (I2C2_BASE_ADDR)    )
#define I2C3					((I2C_TypeDef_t*)  (I2C3_BASE_ADDR)    )

/***************************************************************************************************************************************************/

/*
 * Bit Definitions (Bit tanımlamaları)
 * */

/**************AHB1*******************************************************/

#define RCC_AHB1ENR_GPIOAEN_POS		    (0U)							// RCC AHB1 register GPIOAEN Bit Position
#define RCC_AHB1ENR_GPIOAEN_Msk		    (0x1 << RCC_AHB1ENR_GPIOAEN_POS)// RCC AHB1 register GPIOAEN Bit Mask
#define RCC_AHB1ENR_GPIOAEN			    RCC_AHB1ENR_GPIOAEN_Msk			// RCC AHB1 register GPIOAEN Macro

#define RCC_AHB1ENR_GPIOBEN_POS			(1U)
#define RCC_AHB1ENR_GPIOBEN_Msk			(0x1<< RCC_AHB1ENR_GPIOBEN_POS)
#define RCC_AHB1ENR_GPIOBEN			    RCC_AHB1ENR_GPIOBEN_Msk 		// RCC AHB1 register GPIOBEN Macro

#define RCC_AHB1ENR_GPIOCEN_POS			(2U)
#define RCC_AHB1ENR_GPIOCEN_Msk			(0x1<< RCC_AHB1ENR_GPIOCEN_POS)
#define RCC_AHB1ENR_GPIOCEN				RCC_AHB1ENR_GPIOCEN_Msk			// RCC AHB1 register GPIOCEN Macro

#define RCC_AHB1ENR_GPIODEN_POS			(3U)
#define RCC_AHB1ENR_GPIODEN_Msk			(0x1<< RCC_AHB1ENR_GPIODEN_POS)
#define RCC_AHB1ENR_GPIODEN				RCC_AHB1ENR_GPIODEN_Msk			// RCC AHB1 register GPIODEN Macro

#define RCC_AHB1ENR_GPIOEEN				(0x1<< 4)						// RCC AHB1 register GPIOEEN Macro
#define RCC_AHB1ENR_GPIOHEN				(0x1<< 7)						// RCC AHB1 register GPIOHEN Macro

/**************APB1*******************************************************/

#define RCC_APB1ENR_SPI2EN_Pos			(14U)				    		// RCC APB1 SPI2 Position
#define RCC_APB1ENR_SPI2EN_Msk			(0x1U <<RCC_APB1ENR_SPI2EN_Pos)	// RCC APB1 SPI2 Mask
#define RCC_APB1ENR_SPI2EN   			RCC_APB1ENR_SPI2EN_Msk   		// RCC APB1 SPI2 register Macro

#define RCC_APB1ENR_SPI3EN_Pos			(15U)				    		// RCC APB1 SPI3 Position
#define RCC_APB1ENR_SPI3EN_Msk			(0x1U <<RCC_APB1ENR_SPI3EN_Pos)	// RCC APB1 SPI3 Mask
#define RCC_APB1ENR_SPI3EN  			RCC_APB1ENR_SPI3EN_Msk   		// RCC APB1 SPI3 register Macro

#define RCC_APB1ENR_I2C1EN_Pos			(21U)						    // RCC APB1 I2C1 Position
#define RCC_APB1ENR_I2C1EN_Msk			(0x1U <<RCC_APB1ENR_I2C1EN_Pos) // RCC APB1 I2C1 Mask
#define RCC_APB1ENR_I2C1EN				RCC_APB1ENR_I2C1EN_Msk  	    // RCC APB1 I2C1 register Macro

#define RCC_APB1ENR_I2C2EN_Pos			(22U)							// RCC APB1 I2C2 Position
#define RCC_APB1ENR_I2C2EN_Msk			(0x1U <<RCC_APB1ENR_I2C2EN_Pos) // RCC APB1 I2C2 Mask
#define RCC_APB1ENR_I2C2EN				RCC_APB1ENR_I2C2EN_Msk  	    // RCC APB1 I2C2 register Macro

#define RCC_APB1ENR_I2C3EN_Pos			(23U)							// RCC APB1 I2C3 Position
#define RCC_APB1ENR_I2C3EN_Msk			(0x1U <<RCC_APB1ENR_I2C3EN_Pos) // RCC APB1 I2C3 Mask
#define RCC_APB1ENR_I2C3EN				RCC_APB1ENR_I2C3EN_Msk  	    // RCC APB1 I2C3 register Macro

#define RCC_APB1ENR_USART2EN_Pos		(17U)
#define RCC_APB1ENR_USART2EN_Msk		(0x1U<<RCC_APB1ENR_USART2EN_Pos)
#define RCC_APB1ENR_USART2EN			(RCC_APB1ENR_USART2EN_Msk)

/**************APB2*******************************************************/

#define RCC_APB2ENR_SYSCFG_Pos			(0x1 <<14)						// RCC APB2 register SYSCFG Macro

#define RCC_APB2ENR_SPI1EN_Pos			(12U)							// RCC APB2 SPI1 Position
#define RCC_APB2ENR_SPI1EN_Msk			(0x1U <<RCC_APB2ENR_SPI1EN_Pos) // RCC APB2 SPI1 Mask
#define RCC_APB2ENR_SPI1EN			    RCC_APB2ENR_SPI1EN_Msk			// RCC APB2 SPI1 register Macro

#define RCC_APB2ENR_SPI4EN_Pos			(13U)							// RCC APB2 SPI4 Position
#define RCC_APB2ENR_SPI4EN_Msk			(0x1U <<RCC_APB2ENR_SPI4EN_Pos) // RCC APB2 SPI4 Mask
#define RCC_APB2ENR_SPI4EN				RCC_APB2ENR_SPI2EN_Msk			// RCC APB2 SPI4 register Macro

#define RCC_APB2ENR_SPI5EN_Pos			(20U)							// RCC APB2 SPI5 Position
#define RCC_APB2ENR_SPI5EN_Msk			(0x1U <<RCC_APB2ENR_SPI5EN_Pos) // RCC APB2 SPI5 Mask
#define RCC_APB2ENR_SPI5EN				RCC_APB2ENR_SPI5EN_Msk			// RCC APB2 SPI5 register Macro

#define RCC_APB2ENR_USART1_Pos			(4U)							// RCC APB2 USART1 Position
#define RCC_APB2ENR_USART1_Msk			(0x1U <<RCC_APB2ENR_USART1_Pos) // RCC APB2 USART1 Mask
#define RCC_APB2ENR_USART1EN			(RCC_APB2ENR_USART1_Msk)		// RCC APB2 USART1 register Macro

#define RCC_APB2ENR_USART6_Pos			(5U)							// RCC APB2 USART6 Position
#define RCC_APB2ENR_USART6_Msk			(0x1U <<RCC_APB2ENR_USART6_Pos) // RCC APB2 USART6 Mask
#define RCC_APB2ENR_USART6EN			(RCC_APB2ENR_USART6_Msk)		// RCC APB2 USART6 register Macro


/**************SPI Specific*************************************************/

#define SPI_SR_TxE						(1U)
#define SPI_SR_Busy						(7U)
#define SPI_SR_RxNE						(0U)

#define SPI_CR1_SPE						(6U)
#define SPI_CR1_DFF						(11U)

#define SPI_CR2_TxEIE					(7U)
#define SPI_CR2_RxEIE					(6U)


/**************USART Specific*************************************************/

#define USART2							((USART_TypeDef_t *)(USART2_BASE_ADDR))
#define USART1							((USART_TypeDef_t *)(USART1_BASE_ADDR))
#define USART6							((USART_TypeDef_t *)(USART6_BASE_ADDR))


#define USART_CR1_UE					(13U)
#define USART_CR1_TxEIE					(7U)
#define USART_CR1_RxNEIE				(5U)
#define USART_CR2_STOP					(12U)

#define USART_SR_TxE					(7U)
#define USART_SR_TC						(6U)
#define USART_SR_RxNE					(5U)


/**************I2C Specific*************************************************/

#define I2C_CR1_PE	  					(0U)



/**************FLAG Definitions*************************************************/

#define SPI_TxE_FLAG					(0x1U << SPI_SR_TxE)
#define SPI_Busy_FLAG					(0x1U << SPI_SR_Busy)
#define SPI_RxNE_FLAG					(0x1U << SPI_SR_RxNE)

#define USART_TxE_Flag					(0x1U << USART_SR_TxE)
#define USART_TC_Flag					(0x1U << USART_SR_TC)
#define USART_RxNE_Flag					(0x1 << USART_SR_RxNE)

/**************************INCLUDES********************************************/

#include "RCC.h"														// Main koduna eklemek yerine buraya eklenmiştir.
#include "GPIO.h"
#include "EXTI.h"
#include "SPI.h"
#include "USART.h"
#include "I2C.h"


#endif /* INC_STM32F411XX_H_ */
