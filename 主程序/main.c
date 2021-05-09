#include<reg52.h>
#include<CarInit.h>
#include<Delay.h>
#include<BluetoothInit.h>
#define uchar unsigned char
#define uint unsigned int
//PWM输出(控制舵机)
sbit PWM1 =P3^3;
sbit PWM2 =P3^4;


uchar temp;            //temp储存蓝牙串口收到的信息
uchar count;           //0.125ms次数标识（分成20份）
uchar jd1,jd2;         //舵机角度标识

void main()
{
        jd1=0;
        jd2=0;
        count=0;
        Init();
        BluetoothInit();
     while(1)
       {
		switch(temp)
			{
					case 0x00: stop(); break; 
					case 0x01: go(); break;
					case 0x02: back(); break;
					case 0x03: left(); break;
					case 0x04: right(); break;  
					case 0x05:                              //支架
						    temp=0;
							jd1+=5;
							count=0;
							if(jd1==20)
								{
									delay(200);
									jd1=19;
								}									
                             break;
					case 0x06:                                            
							temp=0;
							jd1-=5;
							count=0;
							if(jd1==0)
									jd1=1; break;
					case 0x07:                           //爪子             
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

void Timer0_Int() interrupt 1    //定时器0工作方式1 16位定时计数（PWM）
{
        TH0  = 0xff;            
        TL0  = 0x8c;             //0.125ms产生一次中断

    if(count<jd1)                //判断0.125ms次数是否小于角度标识
		{
		  PWM1=1;                //确实小于，PWM输出高电平   
		}		
	else
		{
		  PWM1=0;                //大于则输出低电平
		}
	if(count<jd2)
	    {
	 	  PWM2=1;
	    }
	else
		{
		  PWM2=0;
		}
		
    count=(count+1);     //0.125ms次数加1      
    count=count%160;     //次数始终保持为40 即保持周期为20ms
                
      
}

void Com_Init() interrupt 4
{
        RI=0;       //读标志清零
        temp=SBUF;  //将接收到的数据给temp
}