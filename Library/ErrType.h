/*
 * ErrTypes.h
 *
 *  Created on: May 10, 2023
 *      Author: mhmd wael
 */

#ifndef INC_ERRTYPES_H_
#define INC_ERRTYPES_H_

typedef enum  {  
					ADC_WRONG_MODE,
					ADC_WRONG_ADC_NUMBER,
					ADC_WRONG_DATA_ALIGN,
					ADC_WRONG_START_SOURCE,
					ADC_WRONG_NUMBER_OF_CHANNELS,
					ADC_WRONG_CHANNEL,
					ADC_WRONG_SAMPLE_TIME
					
}Error_State_t;

#endif /* INC_ERRTYPES_H_ */
