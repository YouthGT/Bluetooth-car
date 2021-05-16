#include<reg52.h>
#include<Car_Init.h>
#include<Com_Init.h>
#define uchar unsigned char
#define uint unsigned int
	
//PWM输出(控制舵机)
sbit SEH_PWM =P3^3;
sbit SEV_PWM =P3^4;

uchar temp;            //temp储存蓝牙串口收到的信息
uchar count=0;           //0.5ms次数标识
uchar SEH_count=15;
uchar SEV_count=15;         //舵机角度标识

void main()
{
        Car_Init();
        Com_Init();
      while(1);
}

void Timer0_Int() interrupt 1     //定时器0工作方式1 16位定时计数（PWM）
{
        TH0  = 0xff;            
        TL0  = 0xa4;
		//舵机1
		if(count <= SEH_count) //控制占空比左右
			{
				SEH_PWM = 1;//如果count的计数小于（5-25）也就是0.5ms-2.5ms则这段小t周期持续高电平。产生方波
			}
		else
			{
				SEH_PWM = 0;
			}
		//舵机2
		if(count <= SEV_count) //控制占空比上下
			{
				SEV_PWM = 1;
			}
		else
			{
				SEV_PWM = 0;
			}
		count++;
		if (count >= 200) //T = 20ms则定时器计数变量清0
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
     temp = SBUF; //将接收到的数据传给command
	 switch(temp)
				{
					case 0x00: stop(); break; 
					case 0x01: go(); break;
					case 0x02: back(); break;
					case 0x03: left(); break;
					case 0x04: right(); break;
					case 0x05://舵机向上转
						{
							SEV_count++;
							if(SEV_count >= 25)
								{
									SEV_count = 25;//保持180度
								}
							count = 0; //占空比参数t改变，让定时器重新计数
							break;
						}   
					case 0x06://舵机下降
						{
							SEV_count--;
							if(SEV_count <= 5)
								{
									SEV_count = 5; //保持0度
								}
							count = 0;
							break;
						}   
					case 0x07://开
						{
							SEH_count++;
							if(SEH_count >= 15)
								{
									SEH_count = 15; //保持90度 
								}
							count = 0;
							break;
						}   
					case 0x08://合
						{
							SEH_count--;
							if(SEH_count <= 5) //保持0度
								{
									SEH_count = 5;
								}
							count = 0;
							break;
						}
					case 0x09:  //舵机复位
						{
							SEH_count = 15;
							SEV_count = 15;
							count = 0;
							break;
						}
					}
    ES = 1; //打开串口
}
