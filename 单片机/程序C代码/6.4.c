#include <reg52.h>         // ����ͷ�ļ�
#define uchar unsigned char// Ԥ�����������uchar   
#define uint unsigned int  // Ԥ�����������uint

////������T0�жϷ������
void timer0 () interrupt 1 // ������T0�жϷ������
{
	P0=~P0;                  //  LED��״̬ȡ��               
}
void main()                //  ������             
{
	P0=0x00;                 //  LED��״̬��ʼ����ȫ��             
	TMOD=0x06;               //  ����T0�Ĺ�����ʽ               
	TH0=0xfd;                //  ����T0�ĳ�ֵ�Ĵ���
	TL0=0xfd;                //  ����T0�ĳ�ֵ�Ĵ���
	EA=1;                    //  ���ж������ܿ���
	ET0=1;                   //  �򿪼������ж�������
	TR0=1;                   //  ����������
	while(1);                //  �ȴ�
}