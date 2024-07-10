/*
 *  esp8266_console_hal.c
 *
 *  Created on: June 11, 2021
 *      Author: biubiu
 */



#include "uart_ring_buffer_multi.h"
#include "esp8266_console_hal.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

#define PC_UART 	 &huart1
#define DEVICE_UART  &huart3


void esp8266_console_Init (void)
{
	ring_buffer_init();
}

void esp_console_start (void)
{
	if (is_data_available(PC_UART))
	{
	  int data = uart_read(PC_UART);
	  uart_write(data, DEVICE_UART);
	}

	if (is_data_available(DEVICE_UART))
	{
	  int data = uart_read(DEVICE_UART);
	  uart_write(data, PC_UART);
	}
}
