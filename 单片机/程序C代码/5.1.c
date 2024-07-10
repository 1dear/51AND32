#include <reg51.h>         
#define uchar unsigned char    
void main()
{
	uchar k,n,i; 
	n=0x01;
	k=0;
	TMOD=0x01;   
	TH0=(65536-50000)/256;
  TL0=(65536-50000)%256;
	TR0=1;
	while(1)
		{
			n=0x01;
			for(i=0;i<8;i++)
			{
				P0=~n;
				while(k<10)
				{
					while(TF0==0);
					TH0=(65536-50000)/256;
					TL0=(65536-50000)%256;
					TF0=0;			
					k++;	
				}
				k=0;
				n=n<<1;
			}
		}		
}