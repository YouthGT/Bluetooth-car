#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uint i,j;
uchar tmp;                    //�������������յ�����Ϣ
sbit right_go=P1^0;
sbit right_back=P1^1;
sbit left_go=P1^2;
sbit left_back=P1^3;

sbit right_go2=P1^4;
sbit right_back2=P1^5;
sbit left_go2=P1^6;
sbit left_back2=P1^7;

sbit ENA1=P2^0;
sbit ENB1=P2^3;
sbit ENA2=P2^0;
sbit ENB2=P2^3;

sbit pwm1 =P3^3;
sbit pwm2 =P3^4;
sbit pwm3 =P3^5;
sbit pwm4 =P3^6;
uchar count,num1;          //0.5ms������ʶ
uchar jd1,jd2,jd3,jd4;     //�Ƕȱ�ʶ
void delay(uint z)         //��ʱ����
{
        uint x,y;
        for(x=z;x>0;x--)
                for(y=110;y>0;y--);
}

void go()
{
        ENA1=1;
        ENB1=1;
        ENA2=1;
        ENB2=1;
        right_back=0;
        left_go=1;
        left_back=0;
        right_go=1;

        right_back2=0;
        left_go2=1;
        left_back2=0;
        right_go2=1;
               

//        right_back=0;
//        left_go=0;
//        left_back=0;
//        right_go=0;
//        right_back2=0;
//        left_go2=0;
//        left_back2=0;
//        right_go2=0;
       


}

void back()
{
        ENA1=1;
        ENB1=1;
        ENA2=1;
        ENB2=1;
        right_back=1;
        left_go=0;
        left_back=1;
        right_go=0;

        right_back2=1;
        left_go2=0;
        left_back2=1;
        right_go2=0;

       
//        right_back=0;
//        left_go=0;
//        left_back=0;
//        right_go=0;
//        right_back2=0;
//        left_go2=0;
//        left_back2=0;
//        right_go2=0;
       
}

void left()
{
        ENA1=1;
        ENB1=1;
        ENA2=1;
        ENB2=1;
        right_go=1;
        right_back=0;
        left_go=0;
        left_back=1;

        right_go2=1;
        right_back2=0;
        left_go2=1;
        left_back2=0;


//        right_go=0;
//        right_back=0;
//        left_go=0;
//        left_back=0;

//        right_go2=0;
//        right_back2=0;
//        left_go2=0;
//        left_back2=0;
       

}

void right()
{
        ENA1=1;
        ENB1=1;
        ENA2=1;
        ENB2=1;
        right_back=1;
        left_go=1;
        left_back=0;
        right_go=0;

        right_back2=0;
        left_go2=1;
        left_back2=0;
        right_go2=1;


//        right_back=0;
//        left_go=0;
//        left_back=0;
//        right_go=0;

//        right_back2=0;
//        left_go2=0;
//        left_back2=0;
//        right_go2=0;

}

void stop()
{
        right_back=0;
        left_go=0;
        left_back=0;
        right_go=0;

        right_back2=0;
        left_go2=0;
        left_back2=0;
        right_go2=0;
}
/*void duoji1_up()
{
        jd1++;                 
    num=0;              //�������� ��20ms���ڴ��¿�ʼ
    if(jd1==6)
      jd1=5;               //�Ѿ���180�ȣ��򱣳�       
}
void duoji1_dwon()
{
        jd1--;                 
    num=0;
    if(jd1==0)
      jd1=1;               //�Ѿ���0�ȣ��򱣳�
}
void duoji2_up()
{
        jd2++;                 
    num=0;              //�������� ��20ms���ڴ��¿�ʼ
    if(jd2==6)
      jd2=5;               //�Ѿ���180�ȣ��򱣳�       
}  
void duoji2_dwon()
{
        jd2--;                 
    num=0;
    if(jd2==0)
     jd2=1;               //�Ѿ���0�ȣ��򱣳�
}         */

void BlueteethInit()        //�����жϳ�ʼ������ʱ��1��
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


void init()��������������//��״̬��ʼ��
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

void main()
{
        jd1=14;
        jd2=6;
        jd3=5;
        jd4=6;
        count=0;
        init();
        BlueteethInit()
        while(1)
        {
                switch(tmp)
                {
               
                        case 0x01: go(); break;
                        case 0x02: back(); break;
                        case 0x03: left(); break;
                        case 0x04: right(); break;
                        case 0x00: stop(); break;   

                        case 0x05:                                                    //צ��
                                jd1++;
                                count=0;
                                tmp=0;
                                if(jd1==15)
                                jd2=3;                       
                                if(jd1==18)
                                        {
                                                jd1=17;
                                                delay(200);
                                                jd2=15;                                       
                                        }break;
                        case 0x06:                                             //�����½�   
                                tmp=0;
                                jd1--;
                                count=0;
                                if(jd1==0)
                                        jd1=1; break;
 /*                       case 0x07:                                   //֧��
                                jd2++;
                                count=0;
                                tmp=0;
                                if(jd2==6)
                                         jd2=5; break;
                        case 0x08:        
                                tmp=0;
                                jd2--;
                                count=0;
                                if(jd2==0)
                                        jd2=1; break;
                        case 0x09:                                    //��
                                jd3++;
                                count=0;
                                tmp=0;
                                if(jd3==21)
                                ����������jd3=20; break;
                        case 0x10:        
                                tmp=0;
                                jd3--;
                                count=0;
                                if(jd3==0)
                                        jd3=1; break;   
*/
                }


        }
}
void time0() interrupt 1       //��ʱ��0������ʽ1 16λ��ʱ������PWM��
{
        TH0  = 0xff;            
        TL0  = 0x8c;

    if(count<jd1)              //�ж�0.5ms�����Ƿ�С�ڽǶȱ�ʶ
      pwm1=1;                                //ȷʵС�ڣ�PWM����ߵ�ƽ                                      
    else
        pwm1=0;                                  //����������͵�ƽ
        if(count<jd2)
                pwm2=1;
        else
                pwm2=0;
        if(count<jd3)
                pwm3=1;
        else
                pwm3=0;       
        if(count<jd4)
                pwm4=1;
        else
                pwm4=0;                                        
        count=(count+1);                 //0.5ms������1      
    count=count%160;     //����ʼ�ձ���Ϊ40 ����������Ϊ20ms
                
      
}
void Com_Int() interrupt 4
{
        RI=0;       //����־����
        tmp=SBUF;
}