#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
//�����ʱ
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
//1.��������������ϵ��������µ�������������ѭ������;
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
//2.��������������������������ӣ��������������μ�������������ѭ������;
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
//3.��������ֱܷ���������м�������ѭ������:
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
//4.��������ܴ��м�������������ѭ������:
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
//5.��������ֱܷ���������м�����͵ݼ�������ѭ������:
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