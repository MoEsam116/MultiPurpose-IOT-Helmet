/**
 ******************************************************************************
 * @file           : Service.c
 * @version        : 1.0.0
 * @author         : Safety First Team
 * @brief          : Service File Source
 ******************************************************************************
 **/

/*==============================================================================================================================================
 * INCLUDES
 *==============================================================================================================================================*/

#include <stdint.h>

#include "../Inc/Service.h"

/*==============================================================================================================================================
 * GLOBAL VARIABLES
 *==============================================================================================================================================*/

extern ADC_Configs_t ADC_Configs[];

/*==============================================================================================================================================
 * Functions Definitions
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 *@fn : void Clock_Init(void)
 *@brief : This function is used to initialize the clock for the system
 *@paramters : void
 *@retval void
 *==============================================================================================================================================*/

void Clock_Init(void)
{
    /* Enable Clock For ADC 1 */
    RCC_APB2EnableCLK(APB2_ADC1);

    /* Enable Clock For UART 1 */
    RCC_APB2EnableCLK(APB2_USART1);

    /* Enable Clock For GPIO A */
    RCC_APB2EnableCLK(APB2_IOPA);

    /* Enable Clock For AFIO */
    RCC_APB2EnableCLK(APB2_AFIO);

    /* Enable Clock For Timer 1 */
    RCC_APB2EnableCLK(APB2_TIM1);
}

/*==============================================================================================================================================
 *@fn : void PINS_Init(void)
 *@brief : This function is used to initialize the pins for the system
 *@paramters : void
 *@retval void
 *==============================================================================================================================================*/

void PINS_Init(void)
{
    /* Configure Pins For MQ5 Sensor */
    Pin_Config_t MQ5_PIN_Config =
        {
            .Mode = Input,
            .InputMode = Input_Analog,
            .Port = MQ5_PORT,
            .PinNum = MQ5_PIN};

    /* Configure Pins For LDR Sensor */
    Pin_Config_t LDR_PIN_Config =
            {
                .Mode = Input,
                .InputMode = Input_Analog,
                .Port = LDR_PORT,
                .PinNum = LDR_PIN};

    /* Configure Pins For Limit Switch */
    Pin_Config_t Limit_Switch_Config =
        {
            .Mode = Input,
            .InputMode = Input_PU,
            .Port = Limit_Switch_PORT,
            .PinNum = Limit_Switch_PIN};

    /* Configure Pins For ESP8266 */

    Pin_Config_t ESP_TX_Config =
        {
            .Mode = Output_10MHZ,
            .OutputMode = AFPP,
            .Port = ESP_TX_PORT,
            .PinNum = ESP_TX_PIN};

    Pin_Config_t ESP_RX_Config =
        {
            .Mode = Input,
            .InputMode = Floating_Input,
            .Port = ESP_RX_PORT,
            .PinNum = ESP_RX_PIN};

    /* Configure Pins For FLASH */
    Pin_Config_t FLASH_Config =
            {
                .Mode = Output_10MHZ,
                .OutputMode = PushPull,
                .Port = FLASH_PORT,
                .PinNum = FLASH_PIN};


    /* Initialize Pin For MQ5 Sensor */
    GPIO_u8PinInit(&MQ5_PIN_Config);

    /* Initialize Pin For LDR Sensor */
    GPIO_u8PinInit(&LDR_PIN_Config);

    /* Initialize Pin For FLASH Sensor */
    GPIO_u8PinInit(&FLASH_Config);

    /* Initialize Pin For ESP8266 */
    GPIO_u8PinInit(&ESP_TX_Config);

    GPIO_u8PinInit(&ESP_RX_Config);

    /* Initialize Pin For Limit Switch */
    GPIO_u8PinInit(&Limit_Switch_Config);
}

/*==============================================================================================================================================
 *@fn : void Interrupt_Init(void)
 *@brief : This function is used to initialize the interrupts for the system
 *@paramters : void
 *@retval void
 *==============================================================================================================================================*/

void Interrupt_Init(void)
{
    /* Enable Interrupt For USART 1 */
    NVIC_EnableInterrupt(NVIC_USART1);

    /* Enable Interrupt For EXTI 2 For Limit Switch */
    //NVIC_EnableInterrupt(NVIC_EXTI4);

    /* Enable Interrupt For EXTI 3 For DHT11 */
    //NVIC_EnableInterrupt(NVIC_EXTI3);

    /* Configuring Call Back Function For EXTI 2 For Limit Switch */
    //MEXTI_SetCallBack(EXTI_LINE_4, &Limit_Switch_CallBack);

    /* Configuring EXTI 2 Port For Limit Switch */
    //AFIO_U8SetEXTIPort(AFIO_EXTI4, AFIO_PortA);

    /* Configure EXTI 2 For Limit Switch & Trigger On Falling Edge */
    //MEXTI_eEnableEXTILine(EXTI_LINE_4, EXTI_TRIGGER_FALLING);
}

/*==============================================================================================================================================
 *@fn : void Limit_Switch_CallBack(void)
 *@brief : Call back function for the limit switch interrupt
 *@paramters : void
 *@retval void
 *==============================================================================================================================================*/

void Limit_Switch_CallBack(void)
{
}

/*==============================================================================================================================================
 *@fn : void Upload_Data(void)
 *@brief : This function is used to Upload Data to Server
 *@paramters : 	uint8_t * Data_Field => Field of Data on Web site
 *				uint8_t   Data 		 => Data to Send on Web site
 *@retval void
 *==============================================================================================================================================*/
void Upload_Data(char * Data_Field, uint8_t Data)
{
	/*Variable to hold Data Length (Number of Digits)*/
	char * c_Data_Length	=	NULL;
	char * c_Data	=	NULL;

	/*Get Data Length (Number of Digits)*/
	c_Data_Length = ESP8266_GetLengthAscii(Data);

	/*Get the Data in ASCII Form*/
	c_Data = ESP8266_GetDataAscii(Data);

	/*Connect To Server*/
	ESP8266_ConnectToSrvTcp(ESP_IP_THINGSPEAK, ESP_PORT_THINGSPEAK);

	/*Send Data*/
	ESP8266_SendHttpReq(Data_Field, c_Data, c_Data_Length);

}
