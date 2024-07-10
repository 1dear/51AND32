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
		if(!key1)  //如果key1为0
		{
			delay(10);
			if(!key1) //确认按键key1按下
				mode=1;
		}			
		if(!key2)  //如果key2为0
		{
			delay(10);
			if(!key2) //确认按键key2按下
				mode=2;	
		}				
		k=n|m;
		P0=~k;
		delay(500);
		if(mode==1) //模式1从两边向中间
		{
			n=n<<1;
			m=m>>1;
			if(n==0x10)   //如果n=0x10
			{
				n=0x01;
				m=0x80;
			}				 
		}
		if(mode==2) //模式2从中间向两边
		{
			n=n>>1;
			m=m<<1;
			if(!n)   //如果n=0x00
			{
				n=0x08;
				m=0x10;
			}				
		}
	}	
}	
