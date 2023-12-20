/*******************************************************************/
/*  Author : Mohammed Gaafar                                       */
/*  Date : 29 / 10 / 2023                                          */
/*  Version : V1.0                                                 */
/*******************************************************************/
/*==============================================================================================================================================
 * INCLUDES SECTION START
 *==============================================================================================================================================*/
//Libraries Includes
#include <stdint.h>
#include "../../../Library/BIT_MATH.h"
#include "../../../Library/ErrType.h"
//ESP header Include
#include "../Inc/ESP8266.h"
//MCAL Includes
#include "../../../MCAL/UART/Inc/UART_Interface.h"
#include "../../../MCAL/Timer/Inc/Timer_Interface.h"

/*==============================================================================================================================================
 * INCLUDES SECTION END
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION START
 *==============================================================================================================================================*/

volatile uint8_t Iterator = 0  ;
volatile uint8_t DataCome[200] ;
/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION END
 *==============================================================================================================================================*/


/*==============================================================================================================================================
 * Private Functions SECTION START
 *==============================================================================================================================================*/


static void ESP_UARTCallBack(void){
    DataCome[Iterator] = UART_ReadDataRegister();
    Iterator++;
    UART_ClearFlags();
}

/*==============================================================================================================================================
 * Private Functions SECTION START
 *==============================================================================================================================================*/
/*==============================================================================================================================================
 * MODULES IMPLEMENTATION
 *==============================================================================================================================================*/

/**
 * @brief Initialize ESP8266 module.
 * 
 * This function initializes the ESP8266 module by setting up UART communication,
 * setting a callback function, resetting the module, and configuring its mode.
 */
void ESP8266_Init(void){
    //Init UART
    UART_Init();
    //Set CallBack Function
    UART_SetCallBack(ESP_UARTCallBack);
	UART_SendBufferSynchronous((uint8_t *)"AT+RST\r\n");
	Delay_ms(1000);
	ESP8266_ClearBuffer();
    /* Sending AT Command To Check ESP8266 Is Working Or Not  */
    UART_SendBufferSynchronous((uint8_t *)"AT\r\n");
    //Delay_ms 3 Sec
    Delay_ms(3000);
    //Clear Buffer
    ESP8266_ClearBuffer();
    UART_SendBufferSynchronous( (uint8_t *)"AT+CWMODE=1\r\n" );
    //Delay_ms 3 Sec
	Delay_ms(3000);
}
/**
 * @brief Connect ESP8266 to a WiFi network.
 * 
 * @param[in] SSID      SSID of the WiFi network.
 * @param[in] Password  Password of the WiFi network.
 */
void ESP8266_ConnectToWiFi        ( uint8_t* SSID , uint8_t * Password                               ) {
    //Clear Buffer
    ESP8266_ClearBuffer();
    //Send AT Command
    UART_SendBufferSynchronous((uint8_t *)"AT+CWJAP=\"");
    //Send SSID
    UART_SendBufferSynchronous((uint8_t *)SSID);
    //Send Password
    UART_SendBufferSynchronous((uint8_t *)"\",\"");
    UART_SendBufferSynchronous((uint8_t *)Password);
    UART_SendBufferSynchronous((uint8_t *)"\"\r\n");
    //Delay_ms 8 Sec
    Delay_ms(8000);
}

/**
 * @brief Connect ESP8266 to a TCP server.
 * 
 * @param[in] Copy_u8Domain  Domain or IP address of the server.
 * @param[in] Copy_u8Port    Port number of the server.
 */
void ESP8266_ConnectToSrvTcp      ( uint8_t* Copy_u8Domain , uint8_t * Copy_u8Port ) {
    //Clear Buffer
    ESP8266_ClearBuffer();
    //Send AT Command
    UART_SendBufferSynchronous((uint8_t *)"AT+CIPSTART=\"TCP\",\"");
    //Send Domain
    UART_SendBufferSynchronous((uint8_t *)Copy_u8Domain);
    //Send Port
    UART_SendBufferSynchronous((uint8_t *)"\",");
    UART_SendBufferSynchronous((uint8_t *)Copy_u8Port);
    UART_SendBufferSynchronous((uint8_t *)"\r\n");
    //Delay_ms 2 Sec
    Delay_ms(2000);
}


/**
 * @brief Send an HTTP request to a server.
 * 
 * @param[in] Copy_u8Key     API key for authentication.
 * @param[in] Copy_u8Data    Data to be sent in the HTTP request.
 * @param[in] Copy_u8Length  Length of the data to be sent.
 */
void ESP8266_SendHttpReq(uint8_t* Copy_u8Key, uint8_t* Copy_u8Data, uint8_t* Copy_u8Length) {
    // Clear Buffer (Assuming you have a function to clear the buffer)
    ESP8266_ClearBuffer();

    // Send AT Command to start data transmission
    UART_SendBufferSynchronous((uint8_t *)"AT+CIPSEND=");
    UART_SendBufferSynchronous(Copy_u8Length); // Send the length
    UART_SendBufferSynchronous((uint8_t *)"\r\n");

    // Delay_ms for a moment to allow the ESP8266 to prepare for data reception
    Delay_ms(2000);
    // Clear Buffer (Assuming you have a function to clear the buffer)
    ESP8266_ClearBuffer();

    // Construct and send the HTTP GET request to ThingSpeak
    UART_SendBufferSynchronous((uint8_t *)"GET /update?api_key=");
    UART_SendBufferSynchronous((uint8_t *)Copy_u8Key);  // Send the API key
    UART_SendBufferSynchronous((uint8_t *)"&field1="); // Assuming you want to update field1
    UART_SendBufferSynchronous((uint8_t *)Copy_u8Data); // Send the data
    UART_SendBufferSynchronous((uint8_t *)"\r\n");

    // Delay_ms for a moment to allow the ESP8266 to send the data
		//while(DataCome[39] != 'C' && DataCome[40] != 'L');
    Delay_ms(15000);
}


/**
 * @brief Receive an HTTP request from a server.
 * 
 * @param[in]  Copy_u8ChannelID    Channel ID for the HTTP request.
 * @param[in]  Copy_u8Length       Length of the expected data.
 * @param[out] Copy_pu8FileName    Pointer to the received file name.
 * @return     Status of the HTTP request reception.
 */
uint8_t   ESP8266_u8ReceiveHttpReq   ( uint8_t* Copy_u8ChannelID , uint8_t * Copy_u8Length,uint8_t* Copy_pu8FileName) {
	ESP8266_ClearBuffer();
    //Send AT Command
    UART_SendBufferSynchronous((uint8_t *)"AT+CIPSEND=");
    //Send Length
    UART_SendBufferSynchronous((uint8_t *)Copy_u8Length);
    UART_SendBufferSynchronous((uint8_t *)"\r\n");
    //Delay_ms 4 Sec
    Delay_ms(4000);
    //Clear Buffer
    //ESP8266_ClearBuffer();
    //Send AT Command
    UART_SendBufferSynchronous((uint8_t *)"GET http://");
    //Send Channel ID
    UART_SendBufferSynchronous((uint8_t *)Copy_u8ChannelID);
    UART_SendBufferSynchronous((uint8_t *)Copy_pu8FileName);

    UART_SendBufferSynchronous((uint8_t *)"\r\n");
    //Delay_ms 20 Sec
    //Delay_ms(20000);
	while(DataCome[66] == 0x00);
	uint8_t x = DataCome[60];
    return x;
}


/**
 * @brief Change the Access Point (AP) name of ESP8266.
 * 
 * @param[in] new_SSID   New SSID for the Access Point.
 * @param[in] password   Password for the new Access Point.
 */
 /*
void ESP8266_ChangeAccessPointName(uint8_t* new_SSID, uint8_t* password) {
    //Clear Buffer
    ESP8266_ClearBuffer();
    //Send AT Command
    UART_SendBufferSynchronous((uint8_t *)"AT+CWSAP_CUR=\"");
    //Send new SSID
    UART_SendBufferSynchronous((uint8_t *)new_SSID);
    //Send Password
    UART_SendBufferSynchronous((uint8_t *)"\",\"");
    UART_SendBufferSynchronous((uint8_t *)password);
    UART_SendBufferSynchronous((uint8_t *)"\"\r\n");
    //Delay_ms 8 Sec
    Delay_ms(8000);

}*/


/**
 * @brief Clear the data buffer used by ESP8266.
 */
void ESP8266_ClearBuffer          ( void                                                    ) {
    Iterator = 0 ;
    for ( uint8_t i = 0 ; i < 200 ; i++ ){
        DataCome[i] = 0 ;
    }
}
