/**
 ******************************************************************************
 * @file           : Config.h
 * @version        : 1.0.0
 * @author         : Safety First Team
 * @brief          : Main Configuration File Header
 ******************************************************************************
 **/
#ifndef CONFIG_H_
#define CONFIG_H_

/* NVIC GROUPING OPTIONS */
#define NVIC_Priority_Grouping NVIC_4_GROUP_4_SUB

/* DHT11 PORT AND PIN */
#define DHT11_PORT PORTA
#define DHT11_PIN PIN3

/* MQ5 PORT AND PIN */
#define MQ5_PORT PORTA
#define MQ5_PIN PIN1

/* Limit Switch PORT AND PIN */
#define Limit_Switch_PORT PORTA
#define Limit_Switch_PIN PIN4

/*ESP TX PORT AND PIN */
#define ESP_TX_PORT PORTA
#define ESP_TX_PIN PIN9

/*ESP RX PORT AND PIN */
#define ESP_RX_PORT PORTA
#define ESP_RX_PIN PIN10

/*LDR Pin*/
#define LDR_PORT PORTA
#define LDR_PIN PIN2

/*FLASH Pin*/
#define FLASH_PORT PORTA
#define FLASH_PIN PIN5

#define ESP_WIFI_SSID 		"Mowael22"
#define ESP_WIFI_PASSWORD   "01551997281"

/* "Mohammed Ebrahim"
 * "mohamed1122"
 */
#define ESP_KEY "TCGT0TF1IJ5AKLSD"

#define ESP_IP_THINGSPEAK			(uint8_t *)"184.106.153.149"
#define ESP_PORT_THINGSPEAK			(uint8_t *)"80"

/* ESP Fields Numbers */
#define ESP_TEST_FIELD				"2"
#define ESP_TEMPRATURE_FIELD 		"3"
#define ESP_GAS_FIELD 				"5"
#define ESP_LDR_FIELD 				"4"
#define ESP_HUMIDITY_FIELD 			"6"



#endif /* CONFIG_H_ */
