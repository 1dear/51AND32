#include "reg52.h"
#define uchar unsigned char    
#define uint unsigned int

sbit buzz=P2^2;//������
sbit key1=P2^7;//����
bit start;    //���������ı���
uchar num;    //21�����ļ���
uint timer;   //��ʱ����ֵ
//Ƶ�ʱ�
code uint pinlv[]={466,523,587,659,698,784,880,//����
	                932,1047,1175,1319,1397,1568,1760,//����
                  1865,2094,2351,2633,2792,3134,3517};//����

void delayms(uint ms);
void delay(uchar t);									
void play();
void main()
{
	buzz=1;
	TMOD=0x01;
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
			play();
			start=0;
		}
	}
}
void timer0() interrupt 1
{	
	TH0=timer/256;
	TL0=timer%256;	
	buzz=~buzz;	
}
void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=114;j>0;j--);
}
void delay(uchar t)
{
	uint i,j;
	for(i=t;i>0;i--)
		for(j=29000;j>0;j--);
}
void play()
{
	for(num=0;num<21;num++)
	{
		TR0=1;
		timer=65536-(11059200/12)/(pinlv[num]*2);
		TH0=timer/256;
		TL0=timer%256;	
		delay(1);
	}	
	TR0=0;
}

