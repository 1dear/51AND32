
#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "DHT11.h"

// MCU设置为输出模式
void SetMCU_Output()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		  // GPIO引脚，赋值为第12号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO速度，赋值为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// MCU设置为输入模式,给自己叫做输入，需要知道DHT11的高低电平
void SetMCU_Input()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	//上拉输入 GPIO_Mode_IPU ？？？？？？？   不稳定
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;	  // GPIO模式，浮空输入  GPIO_Mode_IN_FLOATING
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		  // GPIO引脚，赋值为第12号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO速度，赋值为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// 初始化DHT11(MCU的复位(发送开始信号)+DHT11的响应)
uint32_t DHT11_Init()
{
	// MCU的复位

	// 设置为输出接收电平
	SetMCU_Output();
	// 先设置为高电平，再置低电平
	// GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	// 拉低至少18ms
	Delay_ms(20);
	// 拉高20-40us
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Delay_us(30);
	// 切换到输入模式
	SetMCU_Input();

	// DHT11的响应

	// 延时15us保证得到低电平
	uint8_t retry = 0; // 防止没有接收，一直等待
	Delay_us(20);
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
	{
		// 看DHT11是否拉高,只要是低电平就继续等待
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0 && retry <= 100)
		{
			++retry;
			Delay_us(1);
		}
		if (retry > 100)
		{
			return 0; // 响应失败
		}
		else
		{
			return 1; // 响应成功
		}

		retry=0;
		//等待高电平结束，到低电平，停止位
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1 && retry <= 100)
		{
			++retry;
			Delay_us(1);
		}
		if (retry > 100)
		{
			return 0; // 响应失败
		}
		else
		{
			return 1; // 响应成功
		}
	}
	else
	{
		return 0;
	}
	
}

// 接收一个字节的数据
void DHT11_GetByte(uint8_t *DHHT11_Byte)
{
	uint8_t retry = 0;
	uint8_t i = 0;
	uint8_t tmp = 0;
	*DHHT11_Byte = 0;
	for (i = 0; i < 8; ++i)
	{
		// 只要是低电平就继续等待
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0 && retry <= 100)
		{
			
			Delay_us(1);
			++retry;
		}
		retry = 0;
		// 延时30us看看是低电平还是高电平
		Delay_us(35);
		// 低电平是0，高电平是1	
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
		{
			tmp = 0;
		}
		else
		{
			tmp = 1;
		}
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1 && retry <= 100)
		{
			
			Delay_us(1);
			++retry;
		}
		retry = 0;
		*DHHT11_Byte <<= (uint8_t)1;
		*DHHT11_Byte |= (uint8_t)tmp;
	}
}
/*
接收40bit和校验位，并得到数据
参数：数据数组，数组元素个数，是否接收成功
*/
int DHT11_GetData(uint8_t *DHT11_Data, int size, uint32_t *flag)
{
	uint32_t res = DHT11_Init();
	//处于低电平
	if (res == 0)
	{
		*flag = 0;
		return 0;
	}
	else
	{
		*flag=1;
	}
	uint8_t sum = 0;
	uint8_t retry = 0;
	uint8_t i = 0;
	
	for (i = 0; i < 5; ++i)
	{

		DHT11_GetByte(&DHT11_Data[i]);
	}
	// 最后拉低50us，表示取完
	Delay_us(50);

	// 检验是否正确
	sum = DHT11_Data[0] + DHT11_Data[1] + DHT11_Data[2]+DHT11_Data[3];
	OLED_ShowNum(1, 3, sum, 3);
	//注意sum的类型，要的是最后8位
	OLED_ShowNum(1, 7, (uint8_t)(sum), 3);//强转后得到的，校验位是多少
	if ((uint8_t)(sum) != DHT11_Data[4])
	{
		
		return 0; 
	}
	else
	{
		return 1;
	}
}

