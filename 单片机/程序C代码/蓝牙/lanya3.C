#include<reg52.h>
#define uchar unsigned char   
#define uint unsigned int	
uchar str1[]={'H','e','l','l','o','!'};
uchar str2[]={'e','r','r','o','r','!'};
unsigned char jieshou=0;
void delay(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=114;j>0;j--);
}
void buf_txd(uchar bz_txd)
{
	uchar cnt,i;
	if(bz_txd==1)
	{
		cnt=sizeof(str1);
		for(i=0;i<cnt;i++)
		{
			SBUF=str1[i];
			delay(30);
		}
	}
		if(bz_txd==2)
	{
		cnt=sizeof(str2);
		for(i=0;i<cnt;i++)
		{
			SBUF=str2[i];
			delay(30);
		}
	}
}
void main()
{
  SCON=0x50; //设置串口工作方式
	TMOD=0x20;//设置T1工作方式    								
	TH1=0xfd;//设置9600波特率	   									
	TL1=0xfd;	
	ES=1;//开串口中断
	EA=1;// 开总中断
	TR1=1;
	while(1);	
}

void  serial_server()interrupt 4
{
	 if(TI)
	 {
		 TI=0;//清发送中断标志
	 }
	 if(RI)
   {
		RI=0;//清接收中断标志
		jieshou=SBUF;//接收串口数据
		switch(jieshou)
		{
			case 0x31:P0=~0x01;buf_txd(1);break; 
			case 0x32:P0=~0x02;buf_txd(1);break;
			case 0x33:P0=~0x04;buf_txd(1);break; 
			case 0x34:P0=~0x08;buf_txd(1);break;				
			case 0x35:P0=~0x10;buf_txd(1);break; 
			case 0x36:P0=~0x20;buf_txd(1);break;				
			case 0x37:P0=~0x40;buf_txd(1);break; 
			case 0x38:P0=~0x80;buf_txd(1);break;	
			default:buf_txd(2);P0=0xff;	
		}
   }
}


