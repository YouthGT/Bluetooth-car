#include<reg52.h>
#include<Car_Init.h>
#include<Com_Init.h>
#define uchar unsigned char
#define uint unsigned int
	
//PWM输出(控制舵机)
sbit SEV_PWM =P2^0;
sbit SEH_PWM =P3^3;

uchar temp;                  //temp储存蓝牙串口收到的信息
uchar count=0;               //0.1ms次数标识
uchar SEV_count=1;          //舵机角度标识
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
					case 0x05://舵机向上转
							PWM1(5);
					        break;
					case 0x06://舵机下降
						{
							
							if(SEV_count > 1)
								{
									SEV_count--; //保持0度
								}
							else
								{
									SEV_count=1;
								}
							count = 0;
							break;
						}   
					case 0x07://开
						{
							if(SEH_count >= 3)
								{
									SEH_count = 3; //保持90度 
								}
							SEH_count++;
							count = 0;
							break;
						}   
					case 0x08://合
						{
							
							if(SEH_count <= 1) //保持0度
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


void uart_ser() interrupt 4  //串口中断函数
{
	 
     RI = 0;
     temp = SBUF; //将接收到的数据传给temp
	 
}


void Timer0_Int() interrupt 1     //定时器0工作方式1 16位定时计数（PWM）
{
        TH0  = 0xfe;            
        TL0  = 0x33;
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
		if (count >= 40)   //T = 20ms则定时器计数变量清0
			{
				count = 0;
			}
}

