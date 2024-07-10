#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
sbit key1=P3^2;
sbit key2=P3^3;
uchar k=0; 
bit mode=0;
void delay(uint ms)
{
	uint x,y;
	for(x=ms;x>0;x--)//1ms
		for(y=114;y>0;y--);
}
void timer0() interrupt 1
{
	TH0=0x3c;
	TL0=0xb0;
	k++;
}
void int0() interrupt 0
{			
	mode=0;	
}
void int1() interrupt 2
{
	mode=1;
}
void main()
{
	uchar n=0x01;
	TMOD=0x01;
	TH0=0x3c;
	TL0=0xb0;
	IE=0x87;
	IT0=1;
	IT1=1;
	TR0=1;
	while(1)
	{
		P0=~n;
		if(k==10)
		{
			k=0;
			if(!mode)
			{
				n=n<<1;
				if(!n)
					n=0x01;
			}
			else
			{
				n=n>>1;
				if(!n)
					n=0x80;
			}
		}
	}	
}	

