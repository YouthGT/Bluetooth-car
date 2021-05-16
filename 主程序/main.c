#include<reg52.h>
#include<Car_Init.h>
#include<Com_Init.h>
#define uchar unsigned char
#define uint unsigned int
	
//PWM���(���ƶ��)
sbit SEH_PWM =P3^3;
sbit SEV_PWM =P3^4;

uchar temp;            //temp�������������յ�����Ϣ
uchar count=0;           //0.5ms������ʶ
uchar SEH_count=15;
uchar SEV_count=15;         //����Ƕȱ�ʶ

void main()
{
        Car_Init();
        Com_Init();
      while(1);
}

void Timer0_Int() interrupt 1     //��ʱ��0������ʽ1 16λ��ʱ������PWM��
{
        TH0  = 0xff;            
        TL0  = 0xa4;
		//���1
		if(count <= SEH_count) //����ռ�ձ�����
			{
				SEH_PWM = 1;//���count�ļ���С�ڣ�5-25��Ҳ����0.5ms-2.5ms�����Сt���ڳ����ߵ�ƽ����������
			}
		else
			{
				SEH_PWM = 0;
			}
		//���2
		if(count <= SEV_count) //����ռ�ձ�����
			{
				SEV_PWM = 1;
			}
		else
			{
				SEV_PWM = 0;
			}
		count++;
		if (count >= 200) //T = 20ms��ʱ������������0
			{
				count = 0;
			}
}

void uart_ser() interrupt 4
{
     if (RI == 0)
		{
			return;
		}
     ES = 0;
     RI = 0;
     temp = SBUF; //�����յ������ݴ���command
	 switch(temp)
				{
					case 0x00: stop(); break; 
					case 0x01: go(); break;
					case 0x02: back(); break;
					case 0x03: left(); break;
					case 0x04: right(); break;
					case 0x05://�������ת
						{
							SEV_count++;
							if(SEV_count >= 25)
								{
									SEV_count = 25;//����180��
								}
							count = 0; //ռ�ձȲ���t�ı䣬�ö�ʱ�����¼���
							break;
						}   
					case 0x06://����½�
						{
							SEV_count--;
							if(SEV_count <= 5)
								{
									SEV_count = 5; //����0��
								}
							count = 0;
							break;
						}   
					case 0x07://��
						{
							SEH_count++;
							if(SEH_count >= 15)
								{
									SEH_count = 15; //����90�� 
								}
							count = 0;
							break;
						}   
					case 0x08://��
						{
							SEH_count--;
							if(SEH_count <= 5) //����0��
								{
									SEH_count = 5;
								}
							count = 0;
							break;
						}
					case 0x09:  //�����λ
						{
							SEH_count = 15;
							SEV_count = 15;
							count = 0;
							break;
						}
					}
    ES = 1; //�򿪴���
}
