/*
 *@file		:	ADC_INTERFACE.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main functions for ADC peripheral
 */
#ifndef ADC_INC_ADC_INTERFACE_H_
#define ADC_INC_ADC_INTERFACE_H_

#include "../../../Library/ErrType.h"
/************** MAIN USER DEFINED VARIABLES ************/

/*************************
 * @ADC_Number_t enum
 */
typedef enum {
	
	ADC_Number_1,
	ADC_Number_2,
}ADC_Number_t;

/*************************
 * @ADC_Convresion_Mode_t enum
 */
typedef enum {
	ADC_MODE_Single_Conv,
	ADC_MODE_Continuous_Conv,
	ADC_MODE_Scan_Conv,
}ADC_Convresion_Mode_t;

/*************************
 * @ADC_Channels_t enum
 */
typedef enum {
	ADC_Channel_0,
	ADC_Channel_1,
	ADC_Channel_2,
	ADC_Channel_3,
	ADC_Channel_4,
	ADC_Channel_5,
	ADC_Channel_6,
	ADC_Channel_7,
	ADC_Channel_8,
	ADC_Channel_9
}ADC_Channels_t;

/*************************
 * @ADC_Data_Align_t enum
 */
typedef enum {
	ADC_DATA_Align_R,
	ADC_DATA_Align_L,
}ADC_Data_Align_t;

/*************************
 * @ADC_Start_Source_t enum
 */
typedef enum {
	ADC_START_SOURCE_TIM1_CC1,
	ADC_START_SOURCE_TIM1_CC2,
	ADC_START_SOURCE_TIM1_CC3,
	ADC_START_SOURCE_TIM2_CC2,
	ADC_START_SOURCE_TIM3_TRGO,
	ADC_START_SOURCE_EXTI11=6,
	ADC_START_SOURCE_SWSTART
}ADC_Start_Source_t;

/*************************
 * @ADC_Channels_SampleTime_t enum
 */
typedef enum	{
	ADC_SAMPLE_TIME_1_5_Cycles,
	ADC_SAMPLE_TIME_7_5_Cycles,
	ADC_SAMPLE_TIME_13_5_Cycles,
	ADC_SAMPLE_TIME_28_5_Cycles,
	ADC_SAMPLE_TIME_41_5_Cycles,
	ADC_SAMPLE_TIME_55_5_Cycles,
	ADC_SAMPLE_TIME_71_5_Cycles,
	ADC_SAMPLE_TIME_239_5_Cycles	
}ADC_Channels_SampleTime_t;
/*********************************************************/

/************************* ADC_Configs_t Structure *************************
 * @ADC_Num				:	ADC Number
 * @ChannelsArr			:	Channels Array
 * @NoOfChannels		:	Channels Array Size
 * @NoOfConversions		:	No of Conversion that will be done in sequence
 * @Data_Align			:	Data Alignment
 * @Start_Source		:	Start Source
 * @ADC_ConvMode		:	Conversion Mode
 * @SampleTimeArr		:	Contains the sample time for each channel in order
 */
typedef struct {

	ADC_Number_t 				ADC_Num;
	
	ADC_Channels_t* 			ChannelsArr;

	uint8_t	 					NoOfChannels;		/*Keep it 1*/
	
	uint8_t						NoOfConversions;	/*Keep it 1*/

	ADC_Data_Align_t			Data_Align;

	ADC_Start_Source_t			Start_Source;

	ADC_Convresion_Mode_t		ADC_ConvMode;

	ADC_Channels_SampleTime_t	SampleTimeArr[10];

}ADC_Configs_t;

/*
 * @function 		:	ADC_u8Init
 * @brief			:	Initialize ADC
 * @param			:	ADC Configurations structure
 * @retval			:	Error State
 * @note			:	This function must be called before Starting single Conversion
 * @warning			:	Do not call this function if you are using ADC in Sequence Conversion
 */
ERRORS_t ADC_u8Init(ADC_Configs_t * ADC_Configs);

/*
 * @function 		:	ADC_u8StartSingleConv
 * @brief			:	Start Single Conversion
 * @param			:	ADC Configurations structure
 * @param			:	Pointer to the variable that will hold the reading value
 * @retval			:	Error State
 * @note			:	This function must be called after calling ADC_u8Init
 * @warning			:	Do not call this function if you are using ADC in Sequence Conversion
 */
ERRORS_t ADC_u8StartSingleConv(ADC_Configs_t * ADC_Configs , uint16_t * Reading_Value);

/*
 * @function 		:	ADC_u8StartSequenceConv
 * @brief			:	Start Sequence Conversion (By repeating single Conversion method)
 * @param			:	Array of ADC Configurations structure
 * @param			:	Pointer to the array that will hold the reading values
 * @param			:	Array Size
 * @retval			:	Error State
 * @note			:	This function must be called Without calling ADC_u8Init
 * @warning			:	Do not call this function if you are using ADC in Single Conversion
 */
ERRORS_t ADC_u8StartSequenceConv(ADC_Configs_t * ADC_Configs , uint16_t * Readings_Arr , uint8_t Arr_Size);

#endif /* ADC_INC_ADC_INTERFACE_H_ */
