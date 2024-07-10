#include <reg52.h>         
#define uchar unsigned char    
#define uint unsigned int
uint k;
////定时器T0中断服务程序
void timer0 () interrupt 1
{
	k++;	
}
void main()
{
	uchar n,i;                        
	k=0;
	TMOD=0x02;    
	TH0=56;
	TL0=56; 
	EA=1;
	ET0=1;
	TR0=1;
	while(1)
		{
			n=0x01;
			for(i=0;i<8;i++)
			{
				P0=~n;
				while(k<500);
				k=0;
				n=n<<1;
			}
		}
}