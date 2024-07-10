#include "reg52.h"
#define uchar unsigned char    
#define uint unsigned int
sbit buzz=P2^2;//������
sbit key1=P2^7;//����
bit start;   //���������ı���
uchar num=10;  //��ͣ��ѭ������
uint timer;   //��ʱ����ֵ
uint pinlv=500;//������Ƶ��
void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=114;j>0;j--);
}
void baojing()
{
	for(num=10;num>0;num--)
	{
		TR0=~TR0;
		delayms(500);
	}	
}
void timer0() interrupt 1
{	
	TH0=timer/256;
	TL0=timer%256;	
	buzz=~buzz;	
}
void main()
{
	buzz=1;
	TMOD=0x01;
	timer=65536-(11059200/12)/(pinlv*2);
	TH0=timer/256;
	TL0=timer%256;	
	EA=1;
	ET0=1;
	while(1)
	{
		if(!key1)
		{
			delayms(10);
			if(key1==0)
				start=1;
		}
		if(start)
		{
			baojing();
			start=0;
		}
	}
}


