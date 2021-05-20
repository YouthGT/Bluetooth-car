#include <reg52.h>
sbit  PWM01= P2^0;
sbit  PWM02= P3^4;
unsigned char count1=5;
unsigned char count2=5;
unsigned char count=0;
unsigned char RxdByte = 0;  //���ڽ��յ����ֽ�
void ConfigTimer0();
void ConfigUART0(unsigned int baud);
 
void PWM1(unsigned char x)
{
	count1=x;
}
void PWM2(unsigned char x)
{
	count2=x;
}
 
void main()
{
    EA = 1;       //���ж�
    ConfigTimer0();   //����T0��ʱ1ms
    ConfigUART0(9600);  //���ò�����Ϊ9600
    
    while (1)
    {  
					switch(RxdByte)
				{
					case 0x01:PWM1(5);break;//PWM1(5)�ֻ���Ƭ�����͡�0�������ת��0��
					case 0x02:PWM1(10);break;
					case 0x03:PWM1(15);break;//90
					case 0x04:PWM1(20);break;//135
					case 0x05:PWM1(25);break;//180
                    case 0x06:PWM2(5);break;//PWM1(5)�ֻ���Ƭ�����͡�0�������ת��0��
					case 0x07:PWM2(10);break;
					case 0x08:PWM2(15);break;
					case 0x09:PWM2(20);break;
					case 0x10:PWM2(25);break;
				}
}
}

/* ���ò�����T0��ms-T0��ʱʱ�� */
void ConfigTimer0()
{
    TMOD &= 0xF0;   //����T0�Ŀ���λ
    TMOD |= 0x01;   //����T0Ϊģʽ1
    TH0 = 0xff;     //����T0����ֵ�ĸ��ֽ�
    TL0 = 0xa3 ;    //����T0����ֵ�ĵ��ֽ�
    ET0 = 1;        //ʹ��T0�ж�
    TR0 = 1;        //����T0
}
/* �������ú�����ͨ�Ų����� */
void ConfigUART0(unsigned int baud)
{
    SCON  = 0x50;  //���ô���Ϊģʽ1
    TMOD &= 0x0F;  //����T1�Ŀ���λ
    TMOD |= 0x20;  //����T1Ϊģʽ2
    TH1 = 256 - (11059200/12/32)/baud;  //����T1����ֵ
    TL1 = TH1;     //��ֵ��������ֵ
    ET1 = 0;       //��ֹT1�ж�
    ES  = 1;       //ʹ�ܴ����ж�
    TR1 = 1;       //����T1
}
 
/* T0�жϷ����������ɨ�� */
void InterruptTimer0() interrupt 1
{
    TH0 = 0xff ;  //���¼�������ֵ
    TL0 = 0xa3;
	  if(count <= count1) 
    {
     
        PWM01 = 1;
    }
    else
    {
        PWM01 = 0;
    }
    count++;
     if(count <= count2) 
    {
     
        PWM02 = 1;
    }
    else
    {
        PWM02 = 0;
    }
    if (count >= 200) 
    {
        count = 0;
			
    }
	
}
/* UART�жϷ����� */
void InterruptUART0() interrupt 4
{
    if (RI)  //���յ��ֽ�
    {
        RI = 0;  //�ֶ���������жϱ�־λ
        RxdByte = SBUF;  //���յ������ݱ��浽�����ֽڱ�����
        SBUF = RxdByte;  //���յ���������ֱ�ӷ��أ�����-"echo"��
                         //������ʾ�û��������Ϣ�Ƿ�����ȷ����
    }
    if (TI)  //�ֽڷ������
    {
        TI = 0;  //�ֶ����㷢���жϱ�־λ
    }
}