#include "reg52.h"
#define uchar unsigned char    
#define uint unsigned int
#define ulong unsigned long
sbit key1=P3^2;//播放和暂停
sbit key2=P3^3;//下一首
sbit key3=P3^5;//单曲循环和顺序播放
sbit buzz=P2^2;//蜂鸣器
bit xhmode=0;//0-循序播放；1-单曲循环
bit zanting;//0-播放；1-暂停
uchar beat=1,num=1;
uint k=0,timer;
ulong index=0;
//《我和我的祖国》数据表
code uchar zuguo[]={125,126,125,124,123,122,161,165,121,
123,221,127,136,113,165,165,126,127,126,125,124,123,162,
166,127,126,125,125,131,112,163,163,125,126,125,124,123,
122,161,165,121,123,221,127,232,211,166,166,221,127,126,
165,126,125,124,163,147,126,145,122,161,161,221,222,223,
222,221,126,127,136,113,165,165,221,222,223,222,221,126,
127,135,113,166,166,125,124,123,162,127,116,116,125,163,
164,142,121,161,141,120};
//《孤勇者》数据表
code uchar guyongzhe[]={120,116,117,211,212,117,211,221,
211,117,211,212,117,211,221,211,212,213,212,213,212,223,
213,212,223,225,223,116,117,211,212,117,211,221,211,117,
211,212,117,211,221,211,212,213,212,213,212,223,213,212,
223,225,223,225,233,215,233,215,213,215,216,213,225,225,
233,215,233,215,213,215,216,213,225,215,215,213,212,222,
222,211,213,213,212,222,222,211,211,146,110,215,215,213,
212,222,222,211,213,213,212,222,222,211,211,146,140,0};
//《少年》数据表
code uchar shaonian[]={120,221,222,221,225,225,225,213,
215,225,223,223,222,222,222,222,211,213,242,222,223,126,
221,221,116,116,126,221,222,221,224,224,224,223,224,223,
222,221,225,225,225,213,215,225,223,223,222,222,222,222,
211,213,242,222,223,126,221,221,126,116,221,211,221,140,0};

code uint pinlv[]={466,523,587,659,698,784,880,//低音
	                932,1047,1175,1319,1397,1568,1760,//中音
                  1865,2094,2351,2633,2792,3134,3517};//高音
void InitTimer();
void play(uchar gequ[]);
void led(uchar LD);
void delay10ms();
void delay (uchar t);								
void main()
{
	InitTimer();
	while(1)
	{
		if(num==1)
			play(zuguo);
		if(num==2)
			play(guyongzhe);
		if(num==3)
			play(shaonian);
	}			
}
void InitTimer()
{
	TMOD=0x61;
	TH1=0xff;
	TL1=0xff;
	EA=1;
	IE=0x8f;
	IT0=1;
	IT1=1;
	PT0=1;
	TR1=1;
}
void play(uchar gequ[])
{
	if(gequ[index]==0)
	{
		TR0=0;
		index=0;
		if(!xhmode)
		{
			num++;
			if(num==4)
				num=1;
		}
	}
	else
	{
		if(gequ[index]%10==0)
			TR0=0;
		else	
		{
			k=gequ[index]%10+(gequ[index]/100-1)*7-1;
			timer=65536-(11059200/12)/(pinlv[k]*2);
			TH0=timer>>8;
			TL0=timer;
			while(zanting);
			TR0=1;
		}
		beat=gequ[index]/10%10;		
		led(gequ[index]%10);
		delay(beat);
		index++;
	}
}
void led(uchar LD)
{
	P0 = 0xff;
	switch (LD){
		case 0:P0 = 0xff;break;
		case 1:P0 = 0xfe;break;
		case 2:P0 = 0xfc;break;
		case 3:P0 = 0xf8;break;
		case 4:P0 = 0xf0;break;
		case 5:P0 = 0xe0;break;
		case 6:P0 = 0xc0;break;
		case 7:P0 = 0x80;break;	
	}
}
void delay (uchar t)
{
	unsigned long i;
	char j;
	for(j=t;j>0;j--)
		for(i=0;i<4000;i++);
	TR0=0;
}
void delay10ms() //按键去抖调用
{
	uchar i,j;
	for(i=10;i>0;i--)
	for(j=114;j>0;j--);
}
void int0() interrupt 0
{
	EX0=0;
	delay10ms();
	if(key1==0)
		zanting=~zanting;	
	EX0=1;
}
void timer0() interrupt 1
{
	TH0=timer>>8;
	TL0=timer;
	buzz=~buzz;
}
void int1() interrupt 2
{
	EX1=0;
	delay10ms();
	if(key2==0)
	{
		num++;
		index=0;
		if(num==4)
			num=1;
	}
	EX1=1;
}
void timer1() interrupt 3
{
	ET1=0;
	delay10ms();
	if(key3==0)
		xhmode=~xhmode;
	ET1=1;
}
