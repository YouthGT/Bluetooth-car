void Com_Init()        //蓝牙中断初始化（定时器1）
{
        TMOD=0x21;        //定时器0设置为16为定时器方式1，定时器1为自动重装方式2
        TH1=0xfd;         //设置波特率为9600
        TL1=0xfd;
	
        TH0=0xff;         //定时器0产生PWM
        TL0=0xa4;          //0.1ms产生一次中断
	
        ET0=1;             //打开定时器0中断
        TR0=1;             //打开定时器0
        ET1=0;             //关闭定时器1中断
        TR1=1;            //打开定时器1
	
        REN=1;            //允许串口接收
        SM0=0;            
        SM1=1;            //串行口方式1波特率可变模式
        ES=1;             //串口中断允许位
        EA=1;              //中断控制总允许
}