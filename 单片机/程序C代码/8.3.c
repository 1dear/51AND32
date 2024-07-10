#include<reg52.h>
#define uchar unsigned char    
unsigned char jieshou=0;
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
			case 0x31:P0=~0x01;break; 
			case 0x32:P0=~0x02;break;
			case 0x33:P0=~0x04;break; 
			case 0x34:P0=~0x08;break;				
			case 0x35:P0=~0x10;break; 
			case 0x36:P0=~0x20;break;				
			case 0x37:P0=~0x40;break; 
			case 0x38:P0=~0x80;break;	
			default:SBUF=0x0e;P0=0xff;	
		}
   }
}


