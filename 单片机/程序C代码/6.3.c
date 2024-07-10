#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
sbit key1=P3^2;
uchar k;
code uchar led[]={0xff,0xfe,0xfc,0xf8,
 0xf0,0xe0,0xc0,0x80};//led��8��״̬
void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=114;j>0;j--);//1ms��ʱ
}
///�ⲿ�ж�INT0�жϷ������	
void int0() interrupt 0
{
	delayms(10);
	if(!key1)
		TR0=~TR0;
}
///��ʱ��T0�жϷ������
void timer0 () interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	k++;	
}
void main()
{
	uchar i;                        
	k=0;
	TMOD=0x01;    
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256; 
	EA=1;
	ET0=1;
	EX0=1;
	IT0=1;
	TR0=1;
	while(1)
		{
			for(i=0;i<8;i++)
			{
				P0=led[i];
				while(k<4);
				k=0;
			}
		}
}