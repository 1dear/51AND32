#include "stm32f10x.h"
#include <stdio.h>
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "DHT11.h"
#include "ESP_01S.h"
/*
1.	A2 	2tx  ,A3 2rx
2.	A9 1tx	A10 1rx
*/

int main(void)
{
	// DHT11的数据
	uint8_t DHT11_Data[5] = {0};
	uint8_t res = 0;
	char data[50];
	char request[200];
	enum STATUS stauts;
	 // 初始化模块
	OLED_Init();
	ESP_01S_Init();

	while (TCP_Connect() == 0)
	{
		switch (stauts)
		{
		case OK:
			break;
		case ERROR:
		break;
		}
	}

	while (1)
	{
		// 直接俄得到DHT11数据(包含初始化)
		res = DHT11_GetData(DHT11_Data);
		json_DHT11(data, DHT11_Data[0], DHT11_Data[2]);

		make_request(request, data);
		ESP_01S_SendString(request);
		Delay_s(2);
	}
}
