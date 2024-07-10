#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
//软件延时
void delay ( void )
{
	uint i;
	for (i=0;i<25530;i++);
}
void main ( )
{
	uchar i,j,n,m,k;
	while(1)
	{
//1.发光二极管先由上到下再由下到上来回流动，循环两次;
		for( i=0;i<2;i++ )
		{
			n=0x01;
			for(j=0;j<8;j++)
			{
				P0=~n;
				delay( );
				n=n<<1;
			}
			n=0x80;
			for (j=0;j<8;j++)
			{
				P0=~n;
				delay( ) ;
				n=n>>1;
			}
		}
//2.发光二极管先由上至下依次增加，再由下至上依次减少来回流动，循环两次;
		for( i=0;i<2;i++)
		{
			n=0xfe;		
			for (j=0;j<8;j++)
			{
				P0=n;
				delay( ) ;
				delay( );
				n=n<<1;
			}
			n=0x7f;
			for(j=0;j<8;j++)
			{
				P0=~n;
				delay( );
				delay( );
				n=n>>1;
			}
			
			n=0x7f;
			for(j=0;j<8;j++)
			{
				P0=n;
				delay( );
				delay( );
				n=n>>1;
			}			
			n=0xfe;		
			for (j=0;j<8;j++)
			{
				P0=~n;
				delay( ) ;
				delay( );
				n=n<<1;
			}
		}
//3.发光二极管分别从两边往中间流动，循环两次:
			for (i=0;i<2;i++)
			{
				n=0x01;
				m=0x80;
				for (j=0;j<4;j++)
				{
					k=n|m;
					P0=~k;
					delay();
					delay( );
					n=n<<1;
					m=m>>1;
				}
			}
//4.发光二极管从中间往两边流动，循环两次:
			for (i=0;i<2;i++ )
			{
				n=0x08;
				m=0x10;
				for(j=0;j<4;j++ )
				{
					k=n|m;
					P0=~k;
					delay();
					delay( );
					n=n>>1;
					m=m<<1;
				}
			}
//5.发光二极管分别从两边往中间递增和递减流动，循环两次:
			for (i=0;i<2;i++)
			{
				n=0x01;
				m=0x80;
				for (j=0;j<4;j++)
				{
					k=n|m;
					P0=~k;
					delay( );
					delay();
					n=n<<1;
					n=n|0x01;
					m=m>>1;
					m=m|0x80;
				}
				n=0x08;
				m=0x10;
				for(j=0;j<4;j++ )
				{
					k=n|m;
					P0=k;
					delay( );
					delay();
					n=n>>1;
					n=n|0x08;
					m=m<<1;
					m=m|0x10;
				}
		}			
	}
}