#include <reg52.h>         
#define uchar unsigned char    
#define uint unsigned int
uchar k;
////定时器T0中断服务程序
void timer0 () interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	k++;	
}
void main()
{
	uchar n,i;                        
	k=0;
	P0=n;
	TMOD=0x01;    
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256; 
	EA=1;
	ET0=1;
	TR0=1;
	while(1)
		{
			n=0x01;
			for(i=0;i<8;i++)
			{
				P0=~n;
				while(k<2);
				k=0;
				n=n<<1;
			}
		}
}