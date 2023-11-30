/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 1/5/2023					  	  **************/
/********* FILE NAME : STM32F103xx.h				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/


#ifndef INC_STM32F103XX_H_
#define INC_STM32F103XX_H_

/************************	  	BASE MEMORY ADDRESSES		    	************************/
#define FLASH_BASE_ADDRESS      			0x08000000UL
#define SRAM_BASE_ADDRESS   	   			0x20000000UL
#define PERIPHERAL_BASE_ADDRESS 	     	0x40000000UL


/************************     	 CORE PERIPHERALS BASE ADDRESSES	************************/
#define SYSTICK_BASE_ADDRESS				0xE000E010UL

/************************     	AHB  BASE PERIPHERALS ADDRESSES		************************/

/************************     	APB 1 BASE PERIPHERALS ADDRESSES	************************/
#define SPI2_BASE_ADDRESS					0x40003800UL

/************************     	APB 2 BASE PERIPHERALS ADDRESSES	************************/
#define AFIO_BASE_ADDRESS			        0x40010000UL

#define GPIOA_BASE_ADDRESS			        0x40010800UL
#define GPIOB_BASE_ADDRESS                  0x40010C00UL
#define GPIOC_BASE_ADDRESS                  0x40011000UL
#define GPIOD_BASE_ADDRESS                  0x40011400UL
#define GPIOE_BASE_ADDRESS                  0x40011800UL
#define GPIOF_BASE_ADDRESS                  0x40011C00UL
#define GPIOG_BASE_ADDRESS                  0x40012000UL

#define SPI1_BASE_ADDRESS					0x40013000UL

#define ADC1_BASE_ADDRESS                   0x40012400UL
#define ADC2_BASE_ADDRESS                   0x40012800UL
/************************     	GPIO REGISTERS DEFINITION			************************/
typedef struct{
	uint32_t CR[2];
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSSR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_REG_t;

/************************     	GPIO PERIPHERAL DEFINITION			************************/
#define GPIOA					((GPIO_REG_t *)(GPIOA_BASE_ADDRESS))
#define GPIOB					((GPIO_REG_t *)(GPIOB_BASE_ADDRESS))
#define GPIOC                   ((GPIO_REG_t *)(GPIOC_BASE_ADDRESS))
#define GPIOD                   ((GPIO_REG_t *)(GPIOD_BASE_ADDRESS))
#define GPIOE                   ((GPIO_REG_t *)(GPIOE_BASE_ADDRESS))
#define GPIOF                   ((GPIO_REG_t *)(GPIOF_BASE_ADDRESS))
#define GPIOG                   ((GPIO_REG_t *)(GPIOG_BASE_ADDRESS))


/************************     	AFIO REGISTERS DEFINITION			************************/
typedef struct {
	uint32_t EVCR;
	uint32_t MAPR;
	uint32_t EXTICR1;
	uint32_t EXTICR2;
	uint32_t EXTICR3;
	uint32_t EXTICR4;
	uint32_t MAPR2;

}AFIO_REG_t;
/************************     	AFIO PERIPHERAL DEFINITION			************************/
#define AFIO 					((AFIO_REG_t *)(AFIO_BASE_ADDRESS))

/************************     	SYSTICK REGISTERS DEFINITION		************************/

typedef struct{

	volatile uint32_t	CTRL;						/*SysTick control and status register*/
	volatile uint32_t	LOAD;						/*SysTick Reload value register*/
	volatile uint32_t	VAL;						/*SysTick Current value register*/

}SYSTICK_REG_t;

#define SYSTICK 					((SYSTICK_REG_t *)(SYSTICK_BASE_ADDRESS))

/************************     	  SPI REGISTERS DEFINITION			************************/
typedef struct {

	volatile uint32_t 	SPI_CR1;		/*SPI Control Register 1*/
	volatile uint32_t 	SPI_CR2;		/*SPI Control Register 2*/
	volatile uint32_t 	SPI_SR;			/*SPI Status Register */
	volatile uint32_t 	SPI_DR;			/*SPI Data Register*/
	volatile uint32_t 	SPI_CRCPR;		/*SPI CRC Polynomial Register*/
	volatile uint32_t 	SPI_RXCRCR;		/*SPI RX CRC Register*/
	volatile uint32_t 	SPI_TXCRCR;		/*SPI TX CRC Register*/
	volatile uint32_t 	SPI_I2SCFGR;	/*SPI_I2C Configuration Register*/
	volatile uint32_t 	SPI_I2SPR;		/*SPI_I2C Prescaler Register*/

}SPI_REG_t;

#define SPI_1					((SPI_REG_t	*)(SPI1_BASE_ADDRESS))
#define SPI_2            		((SPI_REG_t	*)(SPI2_BASE_ADDRESS))

/************************     	ADC REGISTERS DEFINITION			************************/
typedef struct {
	volatile uint32_t	ADC_SR;
	volatile uint32_t	ADC_CR1;
	volatile uint32_t	ADC_CR2;
	volatile uint32_t	ADC_SMPR[2];
	volatile uint32_t	ADC_JOFR[4];
	volatile uint32_t	ADC_HTR;
	volatile uint32_t	ADC_LTR;
	volatile uint32_t	ADC_SQR[3];
	volatile uint32_t	ADC_JSQR;
	volatile uint32_t	ADC_JDR[4];
	volatile uint32_t	ADC_DR;
}ADC_REG_t;

#define ADC1					((ADC_REG_t * )(ADC1_BASE_ADDRESS))
#define ADC2					((ADC_REG_t * )(ADC2_BASE_ADDRESS))

/************************     	PERIPHERAL REGISTER BITS DEFINITION	************************/

/************************     	ISR DEFINITIONS 					************************/




#endif /* INC_STM32F103XX_H_ */
