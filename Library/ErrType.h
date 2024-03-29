/*
 ******************************************************************************
 * @file           : ErrType.h
 * @Author         :
 * @brief          : ERROR TYPES FILE
 * @Date           : May 8, 2023
 ******************************************************************************

 */
#ifndef ERRTYPE_H_
#define ERRTYPE_H_

/*==============================================================================================================================================
 * ERRORS
 *==============================================================================================================================================*/

typedef enum
{
	/*==============================================================================================================================================
	 * GENERAL PURPOSE ERRORS
	 *==============================================================================================================================================*/
	OK,
	NOK,
	NULL_POINTER,
	TIME_OUT_ERROR,
	OUT_OF_RANGE,
    BUSY_FUNCTION,
	/*==============================================================================================================================================
	 * ADC ERRORS
	 *==============================================================================================================================================*/
	ADC_WRONG_MODE,
	ADC_WRONG_ADC_NUMBER,
	ADC_WRONG_DATA_ALIGN,
	ADC_WRONG_START_SOURCE,
	ADC_WRONG_NUMBER_OF_CHANNELS,
	ADC_WRONG_CHANNEL,
	ADC_WRONG_SAMPLE_TIME

} ERRORS_t;

#endif /* ERRTYPE_H_ */
