#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
sbit key1=P2^7;
sbit key2=P2^6;
void delay(uint ms)
{
	uint x,y;
	for(x=ms;x>0;x--)//1ms
		for(y=114;y>0;y--);
}

void main()
{
	uchar n,mode;
	mode=1;
	n=0x01;
	P2=0xff��
	while(1)
	{
		if(!key1)  //���key1Ϊ0
		{
			delay(10)
			if(!key1) //ȷ�ϰ���key1����
				mode=1;
		}
			
		if(!key2)  //���key2Ϊ0
		{
			delay(10);
			if(!key2) //ȷ�ϰ���key2����
				moe=2;	
		}				
		P0=~n;
		delay(500);
		if(mode==1) //ģʽ1ѭ������
		{
			n=n<<1;
			if(!n)   //���n=0x00
				n=0x01;
		}
		if(mode==2) //ģʽ2ѭ������
		{
			n=n>>1;  //���n=0x00
			if(!n)
				n=0x80;
		}
	}	
}	
