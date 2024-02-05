/**
 ******************************************************************************
 * @file           : Config.c
 * @version        : 1.0.0
 * @author         : Safety First Team
 * @brief          : Link Time Configuration File Source
 ******************************************************************************
 **/

/*==============================================================================================================================================
 * INCLUDES
 *==============================================================================================================================================*/
#include <stdint.h>

#include "ErrType.h"

#include "../MCAL/UART/Inc/UART_Interface.h"

#include "../MCAL/SYSTICK/Inc/SYSTICK_Interface.h"

#include "../MCAL/ADC/Inc/ADC_Interface.h"

/*==============================================================================================================================================
 * GLOBAL VARIABLES
 *==============================================================================================================================================*/

/* Configuration For SYSTICK Timer */
SYSTICK_CONFIG_t SYSTICK_TIMER_CONFIG =
    {
        .CLK = SYSTICK_AHB_BY8, .CPU_FREQUENCY = 8000000UL};

/* Configuration For UART 1 */
const UART_Init_t UART_Configuration = {
    .BaudRate = UART_115200,
    .Parity = UART_No_Parity,
    .StopBits = UART_One_Stop_Bit,
    .WordLength = UART_8_WORD_LENGTH,
    .RXNEIE = UART_RXNEIE_EN};

/* Configuration For ADC 1 */
ADC_Channels_t ADC_CHANNELS[][1] = {{ADC_Channel_1}, {ADC_Channel_2}};
ADC_Configs_t ADC_Configs[] =
    {
        /* Configuration For MQ5 */
        {.ADC_Num = ADC_Number_1,
         .ChannelsArr = ADC_CHANNELS[0],
         .ADC_ConvMode = ADC_MODE_Single_Conv,
         .Data_Align = ADC_DATA_Align_R,
         .NoOfConversions = 1,
         .NoOfChannels = 1,
         .SampleTimeArr = {0, ADC_SAMPLE_TIME_55_5_Cycles, ADC_SAMPLE_TIME_55_5_Cycles},
         .Start_Source = ADC_START_SOURCE_SWSTART},

        /* Configuration For LDR */
        {.ADC_Num = ADC_Number_1,
         .ChannelsArr = ADC_CHANNELS[1],
         .ADC_ConvMode = ADC_MODE_Single_Conv,
         .Data_Align = ADC_DATA_Align_R,
         .NoOfConversions = 1,
         .NoOfChannels = 1,
         .SampleTimeArr = {0, ADC_SAMPLE_TIME_55_5_Cycles, ADC_SAMPLE_TIME_55_5_Cycles},
         .Start_Source = ADC_START_SOURCE_SWSTART}};
