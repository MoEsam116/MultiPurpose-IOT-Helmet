#ifndef ESP8266_H
#define ESP8266_H


#define TIMEOUT_WIFI_CONNECT			2000000UL
#define TIMEOUT_WIFI_CONNECT_SERVER		35000UL
typedef enum{
	WIFI_DISCONNECTED,
	WIFI_CONNECTED
}WIFI_Status;

/**
 * @brief Initialize ESP8266 module.
 *
 * This function initializes the ESP8266 module by setting up UART communication,
 * setting a callback function, resetting the module, and configuring its mode.
 */
void ESP8266_Init(void);

/**
 * @brief Connect ESP8266 to a WiFi network.
 *
 * @param[in] SSID      SSID of the WiFi network.
 * @param[in] Password  Password of the WiFi network.
 */
void ESP8266_ConnectToWiFi(uint8_t *SSID, uint8_t *Password);

/**
 * @brief Connect ESP8266 to a TCP server.
 *
 * @param[in] Copy_u8Domain  Domain or IP address of the server.
 * @param[in] Copy_u8Port    Port number of the server.
 */
void ESP8266_ConnectToSrvTcp(uint8_t *Copy_u8Domain, uint8_t *Copy_u8Port);

/**
 * @brief Send an HTTP request to a server.
 *
 * @param[in] Copy_u8Key     API key for authentication.
 * @param[in] Copy_u8Data    Data to be sent in the HTTP request.
 * @param[in] Copy_u8Length  Length of the data to be sent.
 */
void ESP8266_SendHttpReq(uint8_t *Copy_u8Field, uint8_t *Copy_u8Data, uint8_t *Copy_u8Length);

/**
 * @brief Receive an HTTP request from a server.
 *
 * @param[in]  Copy_u8ChannelID    Channel ID for the HTTP request.
 * @param[in]  Copy_u8Length       Length of the expected data.
 * @param[out] Copy_pu8FileName    Pointer to the received file name.
 * @return     Status of the HTTP request reception.
 */
uint8_t ESP8266_u8ReceiveHttpReq(uint8_t *Copy_u8ChannelID, uint8_t *Copy_u8Length, uint8_t *Copy_pu8FileName);

/**
 * @brief Change the Access Point (AP) name of ESP8266.
 *
 * @param[in] new_SSID   New SSID for the Access Point.
 * @param[in] password   Password for the new Access Point.
 */
// void ESP8266_ChangeAccessPointName(uint8_t* new_SSID, uint8_t* password);

WIFI_Status ESP8266_CheckConnection(void);

char *ESP8266_GetLengthAscii(uint8_t Copy_u8Data);
char *ESP8266_GetDataAscii(uint8_t Copy_u8Data);

/**
 * @brief Clear the data buffer used by ESP8266.
 */
void ESP8266_ClearBuffer(void);

void ESP8266_UpdateData(uint8_t *Copy_u8Key, uint8_t *Copy_u8Data, uint8_t *Copy_u8Length);
#endif // ESP8266_H
