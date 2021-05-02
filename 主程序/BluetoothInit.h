void BluetoothInit()        //蓝牙中断初始化（定时器1）
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