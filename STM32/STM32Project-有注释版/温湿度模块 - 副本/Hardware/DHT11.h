#ifndef __DHT11_H
#define	__DHT11_H

#include "stm32f10x.h"


#define HIGH  1
#define LOW   0

#define DHT11_CLK     RCC_APB2Periph_GPIOB
#define DHT11_PIN     GPIO_Pin_10                  
#define DHT11_PORT		GPIOB 

//???,???????????,?????????
#define DHT11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_10)
 //???????
#define  DHT11_DATA_IN()	   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)

typedef struct
{
	uint8_t  humi_int;		//???????
	uint8_t  humi_deci;	 	//???????
	uint8_t  temp_int;	 	//???????
	uint8_t  temp_deci;	 	//???????
	uint8_t  check_sum;	 	//???
		                 
}DHT11_Data_TypeDef;

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
static uint8_t Read_Byte(void);

#endif /* __DHT11_H */







