#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
/*λ����*/
//ǰ��
sbit left_go=P1^2;
sbit left_back=P1^3;
sbit right_go=P1^0;
sbit right_back=P1^1;
//����
sbit left_go2=P1^6;
sbit left_back2=P1^7;
sbit right_go2=P1^4;
sbit right_back2=P1^5;
//���ֿ���ʹ�ܶ�
sbit ENA1=P2^0;
sbit ENB1=P2^3;
sbit ENA2=P2^0;
sbit ENB2=P2^3;
//PWM���(���ƶ��)
sbit pwm1 =P3^3;
sbit pwm2 =P3^4;
sbit pwm3 =P3^5;
sbit pwm4 =P3^6;
uchar temp;             //temp�������������յ�����Ϣ
uchar count,num1;      //0.5ms������ʶ
uchar jd1,jd2;         //����Ƕȱ�ʶ
void delay(uint z);    //������ʱ����
void BlueteethInit();  //����������ʼ��
void init();           //������״̬��ʼ��
//��������ǰ�������ˡ�����ת����
void go();
void back();
void left();
void right();
void stop();

//������
void main()
{
	jd1=0;
	jd2=0;
	count=0;
	init();
	BlueteethInit();
  while(1)
	{
			switch(temp)
			{
		   
					case 0x01: go(); break;
					case 0x02: back(); break;
					case 0x03: left(); break;
					case 0x04: right(); break;
					case 0x00: stop(); break;   
//צ�Ӷ��
					case 0x05:                                            
							jd1++;
							count=0;
							temp=0;
							if(jd1==15)
							 jd2=3;                       
							if(jd1==18)
								{
									jd1=17;
									delay(200);
									jd2=15;                          
								}
								break;
					case 0x06:                                            
							temp=0;
							jd1--;
							count=0;
							if(jd1==0)
									jd1=1; break; 
//�������
                    case 0x07:                                   
							jd2++;
							count=0;
							temp=0;
							if(jd2==6)
									 jd2=5; break;
					case 0x08:        
							temp=0;
							jd2--;
							count=0;
							if(jd2==0)
									jd2=1; break;		
                }
        }
}
/*��ʱ����*/
void delay(uint z)        
{
        uint x,y;
        for(x=z;x>0;x--)
                for(y=110;y>0;y--);
}
/*�����жϳ�ʼ������ʱ��1��*/
void BlueteethInit()        
{
        TMOD= 0x21;        //T1����ģʽΪ2���Զ���װ
        TH1 = 0xfd;        //���ò�����Ϊ9600
        TL1 = 0xfd;
        TH0= 0xff;         //0.5ms
        TL0=0x8c;            //0.25ms         //0.125ms
        ET0=1;               
        TR0=1;
        TR1= 1;      
        REN= 1;
        SM0= 0;
        SM1= 1;   
        ES= 1;         //�����ж�����λ
        EA=1;         //�ն˿�������
}

/*��״̬��ʼ��*/
void init()
{
        right_back=0;
        left_go=0;
        left_back=0;
        right_go=0;

        right_back2=0;
        left_go2=0;
        left_back2=0;
        right_go2=0;
//        jd1=1;
//   jd2=1;         
//        num=0;
}
/*ǰ��*/
void go()
{
	ENA1=1;
	ENB1=1;
	ENA2=1;
	ENB2=1;
	
//	left_go=1;
//	left_back=0;
//	right_go=1;
//	right_back=0;

//	left_go2=1;
//	left_back2=0;
//	right_go2=1;
//	right_back2=0; 

//test	
	left_go=0;
	left_back=0;
	right_go=0;
	right_back=0;

	left_go2=0;
	left_back2=0;
	right_go2=0;
	right_back2=0;	
}
/*����*/
void back()
{
	ENA1=1;
	ENB1=1;
	ENA2=1;
	ENB2=1;
	
	left_go=0;
//	left_back=1;
//	right_go=0;
//	right_back=1;

//	left_go2=0;
//	left_back2=1;
//	right_go2=0;
//	right_back2=1; 

//test	
	left_go=0;
	left_back=0;
	right_go=0;
	right_back=0;

	left_go2=0;
	left_back2=0;
	right_go2=0;
	right_back2=0;	
}
/*��ת*/
void left()
{
	ENA1=1;
	ENB1=1;
	ENA2=1;
	ENB2=1;

//	left_go=0;
//	left_back=1;
//	right_go=1;
//	right_back=0;

//	left_go2=1;
//	left_back2=0;
//	right_go2=1;
//	right_back2=0;
	
//test	
	left_go=0;
	left_back=0;
	right_go=0;
	right_back=0;

	left_go2=0;
	left_back2=0;
	right_go2=0;
	right_back2=0;		
}
/*��ת*/
void right()
{
	ENA1=1;
	ENB1=1;
	ENA2=1;
	ENB2=1;
	
//	left_go=1;
//	left_back=0;
//	right_go=0;
//	right_back=1;

//	
//	left_go2=1;
//	left_back2=0;
//	right_go2=1;
//	right_back2=0;
	
//test	
	left_go=0;
	left_back=0;
	right_go=0;
	right_back=0;

	left_go2=0;
	left_back2=0;
	right_go2=0;
	right_back2=0;
}
/*ֹͣ*/
void stop()
{   
	left_go=0;
	left_back=0;
	right_go=0;
	right_back=0;

	left_go2=0;
	left_back2=0;
	right_go2=0;
	right_back2=0;
}
/*��ʱ��0������ʽ1 16λ��ʱ������PWM��*/
void time0() interrupt 1    
{
        TH0  = 0xff;            
        TL0  = 0x8c;

    if(count<jd1)              //�ж�0.5ms�����Ƿ�С�ڽǶȱ�ʶ
		{
		  pwm1=1;                //ȷʵС�ڣ�PWM����ߵ�ƽ   
		}		
	else
		{
		  pwm1=0;                                 //����������͵�ƽ
		}
	if(count<jd2)
	    {
	 	  pwm2=1;
	    }
	else
		{
		  pwm2=0;
		}
		
    count=(count+1);     //0.5ms������1      
    count=count%160;     //����ʼ�ձ���Ϊ40 ����������Ϊ20ms
                
      
}
/*�����ж�*/
void Com_Int() interrupt 4
{
        RI=0;       //����־����
        temp=SBUF;
}