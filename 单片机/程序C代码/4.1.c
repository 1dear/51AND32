#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
void delay(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)//1ms
		for(j=114;j>0;j--);
}
void pwm(uchar k)
{
	uchar n;
	for(n=0;n<20;n++)
	{
		P0=0x00;
		delay(k);
		P0=0xff;
		delay(10-k);				
	}	
}

void main()
{
	uchar t;
	while(1)
	{
		for(t=1;t<11;t++)
			pwm(t);
		for(t=10;t>0;t--)
			pwm(t);
	}
}	