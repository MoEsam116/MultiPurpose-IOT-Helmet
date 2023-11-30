/*
 *@file		:	ADC_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program for ADC peripheral
 */

/******************* MAIN INCLUDES *********************/
#include <stdint.h>
#include "../../Inc/STM32F103xx.h"
#include "../../Inc/ErrTypes.h"


#include "../Inc/ADC_Interface.h"
#include "../Inc/ADC_Private.h"
/*******************************************************/

/********************** MAIN PV ************************/


static ADC_REG_t * ADCs[ADC_MAX_NUMBER]	=	{ADC1,ADC2};

/*******************************************************/


/****************** MAIN FUNCTIONS *********************/

/*
 * @function 		:	ADC_u8Init
 * @brief			:	Initialize ADC
 * @param			:	ADC Configurations structure
 * @retval			:	Error State
 * @note			:	This function must be called before Starting single Conversion
 * @warning			:	Do not call this function if you are using ADC in Sequence Conversion
 */
Error_State_t ADC_u8Init(ADC_Configs_t * ADC_Configs)
{
	Error_State_t Error_Status = OK;

	if (OK == ADC_CheckConfigs(ADC_Configs))
	{
		/*1- Set Start Conversion Source*/
		ADCs[ADC_Configs->ADC_Num]->ADC_CR2 &= ~(EXTSEL_BITS_MASK<<EXTSEL_BITS_START);
		ADCs[ADC_Configs->ADC_Num]->ADC_CR2 |=  (ADC_Configs->Start_Source<<EXTSEL_BITS_START);

		/*2- Set Data Alignment*/
		ADCs[ADC_Configs->ADC_Num]->ADC_CR2 &= ~(ALIGN_BITS_MASK<<ALIGN_BITS_START);
		ADCs[ADC_Configs->ADC_Num]->ADC_CR2 |= (ADC_Configs->Data_Align << ALIGN_BITS_START);

		/*3- Set Conversion Mode*/

		if (ADC_Configs->ADC_ConvMode == ADC_MODE_Scan_Conv)
		{
			ADCs[ADC_Configs->ADC_Num]->ADC_CR1 |= (1<<SCAN_MODE_BIT_START);
		}
		else {
			ADCs[ADC_Configs->ADC_Num]->ADC_CR2 &= ~(1<<CONT_MODE_BIT_START);
			ADCs[ADC_Configs->ADC_Num]->ADC_CR2 |= (ADC_Configs->ADC_ConvMode<<CONT_MODE_BIT_START);
		}
		/*4- Set Number of Conversions*/
		ADCs[ADC_Configs->ADC_Num]->ADC_SQR[0] &= ~((SEQUENCE_LENGTH_BITS_MASK)<<SEQUENCE_LENGTH_BITS_START);
		ADCs[ADC_Configs->ADC_Num]->ADC_SQR[0] |= ((ADC_Configs->NoOfConversions-1)<<SEQUENCE_LENGTH_BITS_START);

		/*5- Set Channels to make conversions with there order in given array*/
		for (uint8_t i =0; i<ADC_Configs->NoOfConversions ;i++)
		{
			ADCs[ADC_Configs->ADC_Num]->ADC_SQR[(2-(i/6))] &= ~(SEQUENCE_BITS_MASK<<((i%6)*5));
			ADCs[ADC_Configs->ADC_Num]->ADC_SQR[(2-(i/6))] |= (ADC_Configs->ChannelsArr[i]<<((i%6)*5));
		}
		/*6- Set Sample Time for each Channel*/
		for (uint8_t i =0; i<ADC_MAX_CHANNELS ;i++)
		{
			ADCs[ADC_Configs->ADC_Num]->ADC_SMPR[1] |= ((ADC_Configs->SampleTimeArr[i])<<(i*3));
		}
	}
	else {

		Error_Status = ADC_CheckConfigs(ADC_Configs);

	}

	return Error_Status;
}

/*
 * @function 		:	ADC_u8StartSingleConv
 * @brief			:	Start Single Conversion
 * @param			:	ADC Configurations structure
 * @param			:	Pointer to the variable that will hold the reading value
 * @retval			:	Error State
 * @note			:	This function must be called after calling ADC_u8Init
 * @warning			:	Do not call this function if you are using ADC in Sequence Conversion
 */	
Error_State_t ADC_u8StartSingleConv(ADC_Configs_t * ADC_Configs , uint16_t * Reading_Value)
{
	Error_State_t Error_Status = OK;

	if (OK == ADC_CheckConfigs(ADC_Configs))
	{
		/*Enable ADC*/
		ADCs[ADC_Configs->ADC_Num]->ADC_CR2 |= 1;

		/*Start the channel Conversion if the trigger is SWSTART*/
		if (ADC_Configs->Start_Source == ADC_START_SOURCE_SWSTART)
		{
			ADCs[ADC_Configs->ADC_Num]->ADC_CR2 |= 1;
		}

		/*wait on EOC (End of Conversion) FLAG*/
		while( GET_BIT(ADCs[ADC_Configs->ADC_Num]->ADC_SR,1) == FLAG_RESET);

		/*Read ADC*/
		if (ADC_Configs->Data_Align == ADC_DATA_Align_R)
		{
			* Reading_Value = (uint16_t) (ADCs[ADC_Configs->ADC_Num]->ADC_DR) ;
		}
		else
		{
			* Reading_Value = (uint16_t) ((ADCs[ADC_Configs->ADC_Num]->ADC_DR)>>4) ;
		}
		/*ADC Disable*/
		ADCs[ADC_Configs->ADC_Num]->ADC_CR2 &= ~ 1;
	}
	else
	{

		Error_Status = ADC_CheckConfigs(ADC_Configs);

	}

	return Error_Status;

}

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
Error_State_t ADC_u8StartSequenceConv(ADC_Configs_t * ADC_Configs , uint16_t * Readings_Arr , uint8_t Arr_Size)
{
	
	Error_State_t Error_Status = OK;

	uint8_t Local_u8Iterator=0;

	for (Local_u8Iterator=0;Local_u8Iterator<Arr_Size;Local_u8Iterator++)
	{
		if (OK == ADC_CheckConfigs(&ADC_Configs[Local_u8Iterator]))
		{
			ADC_u8Init(&ADC_Configs[Local_u8Iterator]);
			ADC_u8StartSingleConv(&ADC_Configs[Local_u8Iterator], &Readings_Arr[Local_u8Iterator]);
		}
		else
		{
			Error_Status = ADC_CheckConfigs(&ADC_Configs[Local_u8Iterator]);
			break;
		}
	}
	
	return Error_Status;
}
/*******************************************************/


/***************** STATIC FUNCTIONS ********************/
static Error_State_t ADC_CheckConfigs(ADC_Configs_t * ADC_Configs)
{
	Error_State_t Error_Status =OK;

	if (ADC_Configs != NULL)
	{
		if ((ADC_Configs->ADC_ConvMode>=ADC_MODE_Single_Conv)&&(ADC_Configs->ADC_ConvMode<=ADC_MODE_Scan_Conv))
		{
			if ((ADC_Configs->ADC_Num>=ADC_Number_1)&&(ADC_Configs->ADC_Num<=ADC_Number_2))
			{
				if ((ADC_Configs->Data_Align>=ADC_DATA_Align_R)&&(ADC_Configs->Data_Align<=ADC_DATA_Align_L))
				{
					if ((ADC_Configs->Start_Source>=ADC_START_SOURCE_TIM1_CC1)&&(ADC_Configs->Start_Source<=ADC_START_SOURCE_SWSTART))
					{
						if (ADC_Configs->NoOfChannels<=ADC_MAX_CHANNELS)
						{
							if ((ADC_Configs->ChannelsArr != NULL) && (ADC_Configs->SampleTimeArr != NULL))
							{
								for(uint8_t i=0;i<ADC_Configs->NoOfChannels;i++)
								{
									if((ADC_Configs->ChannelsArr[i]>=ADC_Channel_0)&&(ADC_Configs->ChannelsArr[i]<=ADC_Channel_9))
									{
										if((ADC_Configs->SampleTimeArr[i]>=ADC_SAMPLE_TIME_1_5_Cycles)&&(ADC_Configs->SampleTimeArr[i]<=ADC_SAMPLE_TIME_239_5_Cycles))
										{
											Error_Status = OK;		
										}
										else
										{
											Error_Status = ADC_WRONG_SAMPLE_TIME;
										}
									}
									else{
										Error_Status = ADC_WRONG_CHANNEL;
									}
								}
							}
							else{
								Error_Status = Null_Pointer;
							}
						}
						else{
							Error_Status = ADC_WRONG_NUMBER_OF_CHANNELS;
						}
					}
					else{
						Error_Status = ADC_WRONG_START_SOURCE;
					}
				}
				else{
					Error_Status = ADC_WRONG_DATA_ALIGN;
				}	
			}
			else
			{
				Error_Status = ADC_WRONG_ADC_NUMBER;
			}
		}
		else{
			Error_Status = ADC_WRONG_MODE;
		}
	}
	else {
		Error_Status = Null_Pointer;
	}

	return Error_Status;
}







