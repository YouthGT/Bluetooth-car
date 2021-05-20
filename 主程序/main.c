#include<reg52.h>
#include<Car_Init.h>
#include<Com_Init.h>
#define uchar unsigned char
#define uint unsigned int
	
//PWM���(���ƶ��)
sbit SEV_PWM =P2^0;
sbit SEH_PWM =P3^3;

uchar temp;                  //temp�������������յ�����Ϣ
uchar count=0;               //0.1ms������ʶ
uchar SEV_count=1;          //����Ƕȱ�ʶ
uchar SEH_count=1;

void PWM1(uchar x)
{
	SEV_count=x;
}

void main()
{
	   EA = 1; 
	   Car_Init();
       Com_Init();
      while(1)
	  {
		  switch(temp)
				{
					case 0x00: stop(); break; 
					case 0x01: go(); break;
					case 0x02: back(); break;
					case 0x03: left(); break;
					case 0x04: right(); break;
					case 0x05://�������ת
							PWM1(5);
					        break;
					case 0x06://����½�
						{
							
							if(SEV_count > 1)
								{
									SEV_count--; //����0��
								}
							else
								{
									SEV_count=1;
								}
							count = 0;
							break;
						}   
					case 0x07://��
						{
							if(SEH_count >= 3)
								{
									SEH_count = 3; //����90�� 
								}
							SEH_count++;
							count = 0;
							break;
						}   
					case 0x08://��
						{
							
							if(SEH_count <= 1) //����0��
								{
									SEH_count = 1;
								}
							SEH_count--;
							count = 0;
							break;
						}
					}
	  }
}


void uart_ser() interrupt 4  //�����жϺ���
{
	 
     RI = 0;
     temp = SBUF; //�����յ������ݴ���temp
	 
}


void Timer0_Int() interrupt 1     //��ʱ��0������ʽ1 16λ��ʱ������PWM��
{
        TH0  = 0xfe;            
        TL0  = 0x33;
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
		if (count >= 40)   //T = 20ms��ʱ������������0
			{
				count = 0;
			}
}

