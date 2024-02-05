/*
 *@file		:	ADC_Private.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Privates for ADC peripheral
 */

#ifndef ADC_INC_ADC_PRIVATE_H_
#define ADC_INC_ADC_PRIVATE_H_


static ERRORS_t ADC_CheckConfigs(ADC_Configs_t * ADC_Configs);


#define ADC_MAX_NUMBER		2u
#define ADC_MAX_CHANNELS    10u

#define EXTSEL_BITS_START	17u
#define EXTSEL_BITS_MASK	0b111

#define ALIGN_BITS_START	11u
#define ALIGN_BITS_MASK		0b1

#define SCAN_MODE_BIT_START 8u
#define CONT_MODE_BIT_START 1u

#define SEQUENCE_LENGTH_BITS_START		20u
#define SEQUENCE_LENGTH_BITS_MASK		0b1111

#define SWSTART_BIT						22
#define SEQUENCE_BITS_MASK				0b11111
#endif /* ADC_INC_ADC_PRIVATE_H_ */
