#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
/*位定义*/
//前轮
sbit left_go=P1^2;
sbit left_back=P1^3;
sbit right_go=P1^0;
sbit right_back=P1^1;
//后轮
sbit left_go2=P1^6;
sbit left_back2=P1^7;
sbit right_go2=P1^4;
sbit right_back2=P1^5;
//车轮控制使能段
sbit ENA1=P2^0;
sbit ENB1=P2^3;
sbit ENA2=P2^0;
sbit ENB2=P2^3;
//PWM输出(控制舵机)
sbit PWM1 =P3^3;
sbit PWM2 =P3^4;

uchar temp;            //temp储存蓝牙串口收到的信息
uchar count;           //0.5ms次数标识
uchar jd1,jd2;         //舵机角度标识
void delay(uint z);    //声明延时函数
void BlueteethInit();  //声明蓝牙初始化
void init();           //声明车状态初始化
//声明车的前进、后退、左右转函数
void go();
void back();
void left();
void right();
void stop();

/*void duoji1_up()
{
        jd1++;                 
    num=0;              //按键按下 则20ms周期从新开始
    if(jd1==6)
      jd1=5;               //已经是180度，则保持       
}
void duoji1_dwon()
{
        jd1--;                 
    num=0;
    if(jd1==0)
      jd1=1;               //已经是0度，则保持
}
void duoji2_up()
{
        jd2++;                 
    num=0;              //按键按下 则20ms周期从新开始
    if(jd2==6)
      jd2=5;               //已经是180度，则保持       
}  
void duoji2_dwon()
{
        jd2--;                 
    num=0;
    if(jd2==0)
     jd2=1;               //已经是0度，则保持
}         */


void main()
{
        jd1=14;
        jd2=6;
        count=0;
        Init();
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

                        case 0x05:                                                    //爪子
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
                                        }break;
                        case 0x06:                                             //上升下降   
                                temp=0;
                                jd1--;
                                count=0;
                                if(jd1==0)
                                        jd1=1; break;
 /*                       case 0x07:                                   //支架
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
                        case 0x09:                                    //门
                                jd3++;
                                count=0;
                                temp=0;
                                if(jd3==21)
                                　　　　　jd3=20; break;
                        case 0x10:        
                                temp=0;
                                jd3--;
                                count=0;
                                if(jd3==0)
                                        jd3=1; break;   
*/
                }


        }
}

void delay(uint z)         //延时函数
{
        uint x,y;
        for(x=z;x>0;x--)
                for(y=110;y>0;y--);
}

void BlueteethInit()        //蓝牙中断初始化（定时器1）
{
        TMOD= 0x21;        //T1工作模式为2，自动重装
        TH1 = 0xfd;        //设置波特率为9600
        TL1 = 0xfd;
        TH0= 0xff;         //0.5ms
        TL0=0x8c;            //0.25ms         //0.125ms
        ET0=1;               
        TR0=1;
        TR1= 1;      
        REN= 1;
        SM0= 0;
        SM1= 1;   
        ES= 1;         //串口中断允许位
        EA=1;         //终端控制允许
}


void Init()//车状态初始化
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
void go()
{
	ENA1=1;
	ENB1=1;
	ENA2=1;
	ENB2=1;
	
	left_go=1;
	left_back=0;
	right_go=1;
	right_back=0;

	left_go2=1;
	left_back2=0;
	right_go2=1;
	right_back2=0; 

//test	
//	left_go=0;
//	left_back=0;
//	right_go=0;
//	right_back=0;

//	left_go2=0;
//	left_back2=0;
//	right_go2=0;
//	right_back2=0;	
}

void back()
{
	ENA1=1;
	ENB1=1;
	ENA2=1;
	ENB2=1;
	
	left_go=0;
	left_back=1;
	right_go=0;
	right_back=1;

	left_go2=0;
	left_back2=1;
	right_go2=0;
	right_back2=1; 

//test	
//	left_go=0;
//	left_back=0;
//	right_go=0;
//	right_back=0;

//	left_go2=0;
//	left_back2=0;
//	right_go2=0;
//	right_back2=0;	
}

void left()
{
	ENA1=1;
	ENB1=1;
	ENA2=1;
	ENB2=1;

	left_go=0;
	left_back=1;
	right_go=1;
	right_back=0;

	left_go2=1;
	left_back2=0;
	right_go2=1;
	right_back2=0;
	
//test	
//	left_go=0;
//	left_back=0;
//	right_go=0;
//	right_back=0;

//	left_go2=0;
//	left_back2=0;
//	right_go2=0;
//	right_back2=0;		
}

void right()
{
	ENA1=1;
	ENB1=1;
	ENA2=1;
	ENB2=1;
	
	left_go=1;
	left_back=0;
	right_go=0;
	right_back=1;

	
	left_go2=1;
	left_back2=0;
	right_go2=1;
	right_back2=0;
	
//test	
//	left_go=0;
//	left_back=0;
//	right_go=0;
//	right_back=0;

//	left_go2=0;
//	left_back2=0;
//	right_go2=0;
//	right_back2=0;
}

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
void Timer0_Int() interrupt 1     //定时器0工作方式1 16位定时计数（PWM）
{
        TH0  = 0xff;            
        TL0  = 0x8c;

    if(count<jd1)              //判断0.5ms次数是否小于角度标识
		{
		  PWM1=1;                //确实小于，PWM输出高电平   
		}		
	else
		{
		  PWM1=0;                                 //大于则输出低电平
		}
	if(count<jd2)
	    {
	 	  PWM2=1;
	    }
	else
		{
		  PWM2=0;
		}
		
    count=(count+1);     //0.5ms次数加1      
    count=count%160;     //次数始终保持为40 即保持周期为20ms
                
      
}

void Com_Init() interrupt 4
{
        RI=0;       //读标志清零
        temp=SBUF;  //将接收到的数据给temp
}