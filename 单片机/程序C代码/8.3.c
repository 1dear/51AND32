#include<reg52.h>
#define uchar unsigned char    
unsigned char jieshou=0;
void main()
{
  SCON=0x50; //���ô��ڹ�����ʽ
	TMOD=0x20;//����T1������ʽ    								
	TH1=0xfd;//����9600������	   									
	TL1=0xfd;	
	ES=1;//�������ж�
	EA=1;// �����ж�
	TR1=1;
	while(1);	
}

void  serial_server()interrupt 4
{
	 if(TI)
	 {
		 TI=0;//�巢���жϱ�־
	 }
	 if(RI)
   {
		RI=0;//������жϱ�־
		jieshou=SBUF;//���մ�������
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


