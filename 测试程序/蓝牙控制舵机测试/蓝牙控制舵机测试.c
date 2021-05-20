#include <reg52.h>
sbit  PWM01= P2^0;
sbit  PWM02= P3^4;
unsigned char count1=5;
unsigned char count2=5;
unsigned char count=0;
unsigned char RxdByte = 0;  //串口接收到的字节
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
    EA = 1;       //总中断
    ConfigTimer0();   //配置T0定时1ms
    ConfigUART0(9600);  //配置波特率为9600
    
    while (1)
    {  
					switch(RxdByte)
				{
					case 0x01:PWM1(5);break;//PWM1(5)手机向单片机发送‘0’，舵机转到0度
					case 0x02:PWM1(10);break;
					case 0x03:PWM1(15);break;//90
					case 0x04:PWM1(20);break;//135
					case 0x05:PWM1(25);break;//180
                    case 0x06:PWM2(5);break;//PWM1(5)手机向单片机发送‘0’，舵机转到0度
					case 0x07:PWM2(10);break;
					case 0x08:PWM2(15);break;
					case 0x09:PWM2(20);break;
					case 0x10:PWM2(25);break;
				}
}
}

/* 配置并启动T0，ms-T0定时时间 */
void ConfigTimer0()
{
    TMOD &= 0xF0;   //清零T0的控制位
    TMOD |= 0x01;   //配置T0为模式1
    TH0 = 0xff;     //加载T0重载值的高字节
    TL0 = 0xa3 ;    //加载T0重载值的低字节
    ET0 = 1;        //使能T0中断
    TR0 = 1;        //启动T0
}
/* 串口配置函数，通信波特率 */
void ConfigUART0(unsigned int baud)
{
    SCON  = 0x50;  //配置串口为模式1
    TMOD &= 0x0F;  //清零T1的控制位
    TMOD |= 0x20;  //配置T1为模式2
    TH1 = 256 - (11059200/12/32)/baud;  //计算T1重载值
    TL1 = TH1;     //初值等于重载值
    ET1 = 0;       //禁止T1中断
    ES  = 1;       //使能串口中断
    TR1 = 1;       //启动T1
}
 
/* T0中断服务函数，完成扫描 */
void InterruptTimer0() interrupt 1
{
    TH0 = 0xff ;  //重新加载重载值
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
/* UART中断服务函数 */
void InterruptUART0() interrupt 4
{
    if (RI)  //接收到字节
    {
        RI = 0;  //手动清零接收中断标志位
        RxdByte = SBUF;  //接收到的数据保存到接收字节变量中
        SBUF = RxdByte;  //接收到的数据又直接发回，叫作-"echo"，
                         //用以提示用户输入的信息是否已正确接收
    }
    if (TI)  //字节发送完毕
    {
        TI = 0;  //手动清零发送中断标志位
    }
}