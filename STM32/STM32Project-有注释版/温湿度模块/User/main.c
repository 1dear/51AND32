#include "stm32f10x.h"
#include "OLED.h"
#include "DHT11.h"
#include"Delay.h"
uint8_t DHT11_Data[5] = {0};

int main(void)
{
	uint32_t flag = 0;//响应是否成功
	/*模块初始化*/
	OLED_Init(); // OLED初始化
	int res = 0;//校验位是否正确

	while (1)
	{
		res = DHT11_GetData(DHT11_Data, 5, &flag);
		OLED_ShowNum(1, 1, flag, 1);
		//湿度
		OLED_ShowString(2, 1, "h:");
		OLED_ShowNum(2, 3, DHT11_Data[0], 3);
		OLED_ShowChar(2, 6, '.');
		OLED_ShowNum(2, 7, DHT11_Data[1], 2);
		
		//温度
		
		OLED_ShowString(3, 1, "t:");
		OLED_ShowNum(3, 3, DHT11_Data[2], 2);
		OLED_ShowChar(3, 5, '.');
		OLED_ShowNum(3, 6, DHT11_Data[3], 2);
		
		//校验位是否正确
		OLED_ShowNum(4, 1, res, 1);
		OLED_ShowNum(4, 7, DHT11_Data[4], 5);

		Delay_s(1);
	}
}
