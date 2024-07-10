#include "stm32f10x.h"
#include "OLED.h"
#include "DHT11.h"
#include "Delay.h"
DHT11_Data_TypeDef DHT11_Data;

int main(void)
{
	uint32_t flag = 0; // 响应是否成功
	/*模块初始化*/
	OLED_Init(); // OLED初始化
	int res = 0; // 校验位是否正确

	/*初始化DTT11的引脚*/
	DHT11_GPIO_Config();

	while (1)
	{

		if (Read_DHT11(&DHT11_Data) == SUCCESS)
		{
		
			OLED_ShowNum(1, 1, flag, 1);
			// 湿度
			OLED_ShowString(2, 1, "h:");
			OLED_ShowNum(2, 3, DHT11_Data.humi_int, 3);
			OLED_ShowChar(2, 6, '.');
			OLED_ShowNum(2, 7, DHT11_Data.humi_deci, 2);

			// 温度

			OLED_ShowString(3, 1, "t:");
			OLED_ShowNum(3, 3, DHT11_Data.humi_int, 2);
			OLED_ShowChar(3, 5, '.');
			OLED_ShowNum(3, 6, DHT11_Data.temp_deci, 2);
		}
		else
		{
			OLED_ShowString(3, 1, "t:");
		}
		Delay_s(1);
	}
}
