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
	uchar n,m,k,mode;
	mode=1;
	n=0x01;
	m=0x80;
	P2=0xff;
	while(1)
	{
		if(!key1)  //���key1Ϊ0
		{
			delay(10);
			if(!key1) //ȷ�ϰ���key1����
				mode=1;
		}			
		if(!key2)  //���key2Ϊ0
		{
			delay(10);
			if(!key2) //ȷ�ϰ���key2����
				mode=2;	
		}				
		k=n|m;
		P0=~k;
		delay(500);
		if(mode==1) //ģʽ1���������м�
		{
			n=n<<1;
			m=m>>1;
			if(n==0x10)   //���n=0x10
			{
				n=0x01;
				m=0x80;
			}				 
		}
		if(mode==2) //ģʽ2���м�������
		{
			n=n>>1;
			m=m<<1;
			if(!n)   //���n=0x00
			{
				n=0x08;
				m=0x10;
			}				
		}
	}	
}	
