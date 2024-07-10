#include "stm32f10x.h"
#include <stdio.h>
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "DHT11.h"
#include "ESP_01S.h"
#include "serial.h"
/*
1.	A2 	2tx  ,A3 2rx
2.	A9 1tx	A10 1rx
*/
uint32_t flag = 0;
uint8_t DHT11_Data[5] = {0};
int res = 0;
void OLED_Show_DHT11()
{
	OLED_ShowNum(1, 1, flag, 1);
	// 湿度
	OLED_ShowString(2, 1, "h:");
	OLED_ShowNum(2, 3, DHT11_Data[0], 3);
	OLED_ShowChar(2, 6, '.');
	OLED_ShowNum(2, 7, DHT11_Data[1], 3);
	// 温度

	OLED_ShowString(3, 1, "t:");
	OLED_ShowNum(3, 3, DHT11_Data[2], 2);
	OLED_ShowChar(3, 5, '.');
	OLED_ShowNum(3, 6, DHT11_Data[3], 2);

	// 校验位是否正确
	OLED_ShowNum(4, 1, res, 1);
	OLED_ShowNum(4, 7, DHT11_Data[4], 5);
}
// void DHT11_data_send_STDOUT()
// {
// 	char cmd[100];
// 	sprintf(cmd, "\r\n湿度：%d.%d", DHT11_Data[0], DHT11_Data[1]);
// 	Serial_SendString(cmd);
// 	sprintf(cmd, "\r\n温度：%d.%d", DHT11_Data[2], DHT11_Data[3]);
// 	Serial_SendString(cmd);
// }

// void Json_Made(char *data)
// {
// 	char cmd[100];
// 	sprintf(cmd, "{\"湿度\":%d,\"温度\":}", DHT11_Data[0], DHT11_Data[1]);
// }
// void DHT11_data_send_server()
// {
// 	TCP_Connect("vivo S15", "34302955");
// 	char cmd[100];
// 	sprintf(cmd, "\r\n{\nhumidity:%d.%d", DHT11_Data[0], DHT11_Data[1]);
// 	TCP_SendData(cmd);
// 	sprintf(cmd, "\r\\{\ntemperature:%d.%d\r\n}", DHT11_Data[2], DHT11_Data[3]);
// 	TCP_SendData(cmd);
// }

int main(void)
{
	Delay_s(3);
	/*模块初始化*/
	OLED_Init(); // OLED初始化
	// Serial_Init(); // 串口初始化
	ESP_01S_Init();

	Delay_s(1);
	TCP_Connect();
	Delay_s(1);
	TCP_CIP_SEND();
	Delay_s(1);
	char request[150];
	char data[80];
	while (1)
	{
		// 里面含初始化
		res = DHT11_GetData(DHT11_Data, 5, &flag);
		OLED_Show_DHT11();
		json_DHT11(data, DHT11_Data[0], DHT11_Data[2]);
		make_request(request, data);
		ESP_01S_SendString(request);
		Delay_s(5);
	}
}
