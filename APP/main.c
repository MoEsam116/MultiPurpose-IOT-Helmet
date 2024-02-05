/**
 ******************************************************************************
 * @file           : main.c
 * @version        : 1.0.0
 * @author         : Safety First Team
 * @brief          : Main File Source
 ******************************************************************************
 **/

/*==============================================================================================================================================
 * INCLUDES
 *==============================================================================================================================================*/

#include "../Service/Inc/Service.h"


extern ADC_Configs_t ADC_Configs[];

int main(void)
{

	/*Array to Hold ADC Readings For MQ-5 and LDR*/
	uint16_t ADC_Readings[2]={0};

	/* Local Variables for DHT11 */
	float f32_Temp = 0, f32_Humidity = 0;

	/* Local Variable for Error Status */
	ERRORS_t u8_ErrorStatus = OK;

	/*Local Variable to hold Limit switch State*/
	uint8_t u8_LimitSwitchState = PinHigh;
	uint8_t u8_LightState = Light_OFF;

	/* Initialize Clock */
	Clock_Init();

	/* Initialize Pins */
	PINS_Init();

	/* Initialize Interrupts */
	Interrupt_Init();

	/* Initialize DHT11 */
	HDHT11_eInit(DHT11_PIN, DHT11_PORT);

	/* Initialize ESP8266 */
	ESP8266_Init();

	/* Connect to WiFi */
	ESP8266_ConnectToWiFi((uint8_t *)ESP_WIFI_SSID, (uint8_t *)ESP_WIFI_PASSWORD);

	/* Loop forever */
	while (1)
	{

		/*Read Limit Switch Status*/
		GPIO_u8ReadPinValue(Limit_Switch_PORT, Limit_Switch_PIN, &u8_LimitSwitchState);

		if( u8_LimitSwitchState == PinHigh)
		{
			/*Limit Switch not Pressed => Enter Sleep mode*/
			/*Disable UART RX Interrupt*/
			NVIC_DisableInterrupt(NVIC_USART1);

			/*Enter Sleep Mode*/
			PWR_xEnterSleepMode();

			/*Enable UART RX Interrupt*/
			NVIC_EnableInterrupt(NVIC_USART1);
		}
		else
		{
			/*	Do Nothing	*/
		}

		/*Read LDR and MQ5*/
		ADC_u8StartSequenceConv(ADC_Configs, ADC_Readings, 2);
		/*==============================================================================================================================================
		 *  LDR Algorithm
		 *==============================================================================================================================================*/
		/*MAP LDR Data to Server Range*/
		ADC_Readings[LDR_VALUE] = MAP(LDR_MIN_READ,LDR_MAX_READ,
									SERVER_MIN_RANGE,
									SERVER_MAX_RANGE,ADC_Readings[LDR_VALUE]);
		//Modify this 30 Depends on your preference and LDR sens you use
		if(ADC_Readings[LDR_VALUE] >= 30)
		{
			/*If Light status is ON => Turn on FLASH*/
			GPIO_u8SetPinValue(FLASH_PORT, FLASH_PIN, Light_ON);
		}
		else {
			/*If Light status is Off => Turn OFF FLASH*/
			GPIO_u8SetPinValue(FLASH_PORT, FLASH_PIN, Light_OFF);
		}


		/*Upload Data To Server*/
		Upload_Data(ESP_LDR_FIELD, (uint8_t) ADC_Readings[LDR_VALUE]);

		/*==============================================================================================================================================
		 *  MQ-5 Algorithm
		 *==============================================================================================================================================*/

		/*Get Ratio as Percentage of Pollution*/
		ADC_Readings[MQ5_VALUE] = MQ5_u16GetRatio(ADC_Readings[MQ5_VALUE]);

		/*Send Data to Server*/
		Upload_Data(ESP_GAS_FIELD, (uint8_t) ADC_Readings[MQ5_VALUE]);

		/*==============================================================================================================================================
		 *  DHT11 Algorithm
		 *==============================================================================================================================================*/
		/*Read DHT11 to get Temperature and Humidity*/
		HDHT11_eGetTempHumidity(&f32_Temp, &f32_Humidity);
		/*Send Temperature to Server*/
		Upload_Data(ESP_TEMPRATURE_FIELD,(uint8_t)f32_Temp );

		/*Send Humidity to Server*/
		Upload_Data(ESP_HUMIDITY_FIELD,(uint8_t)f32_Humidity );
	}
}
