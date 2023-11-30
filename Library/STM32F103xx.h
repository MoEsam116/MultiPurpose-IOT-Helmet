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


#define ADC1_BASE_ADDRESS                   0x40012400UL
#define ADC2_BASE_ADDRESS                   0x40012800UL
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

#endif /* INC_STM32F103XX_H_ */
