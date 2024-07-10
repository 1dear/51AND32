#include "stm32f10x.h"
#include "OLED.h"
#include "DHT11.h"
#include"Delay.h"
int main(void)
{
	u8 temp, humi;
	
	OLED_Init(); // OLED初始化
	u8 res = 0;//校验位是否正确
	res= DHT11_Init();  
	OLED_ShowNum(4,1,res,4);
	while (1)
	{
		res = DHT11_Read_Data(&temp,&humi);
		OLED_ShowNum(1, 1, temp, 5);
		OLED_ShowNum(2, 1, humi, 5);
		OLED_ShowNum(3,1,res,4);
		Delay_s(1);
	}
}
