#include "reg52.h"
#define uchar unsigned char    
#define uint unsigned int
#define ulong unsigned long
uchar beat=1,num=1;
uint k=0,timer;
ulong index=0;
uint timer;
bit xhmode=0;//0-Ñ­Ðò²¥·Å£»1-µ¥ÇúÑ­»·
bit zanting=0;//0-²¥·Å£»1-ÔÝÍ£
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
	uint i;
	uchar j;
	for(j=t;j>0;j--)
		for(i=23000;i>0;i--);
	TR0=0;
}

void play(uchar gequ[],uint pinlv[])
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

