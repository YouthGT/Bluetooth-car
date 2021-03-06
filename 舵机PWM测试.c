    #include<reg52.h>
    unsigned int a, b;
    //------------------------------------------
    void main()
    {
             TMOD = 0x01;                 //T0定时方式1
             TH0 = (65536-50000) / 256;   //50ms@12MHz
             TL0 = (65536-50000) % 256;
             TR0 = 1;

             ET0 = 1;
             EX0 = 1; EX1 = 1;
             IT0 = 1; IT1 = 1;
             EA = 1;

             a = 0;
             b = 10;
             while(1);
    }
    //------------------------------------------
    void time0() interrupt 1
    {
             TL0 = (65536-50000) % 256;
             TH0 = (65536-50000) / 256;   //50ms@12MHz
             a++;
             if(a == 20) a = 0;           //在这里调整周期.
             if(a < b) P2 = 0xff;        //在这里调整占空比.
             else   P2 = 0x00;
             P0 = ((b / 10) << 4) + b % 10; //显示占空比等级
    }
    //------------------------------------------
    void X0_INT() interrupt 0
    {
             b++;
             if(b > 19) b = 19;           //占空比等级最大为19
    }
    //------------------------------------------
    void X1_INT() interrupt 2
    {
             b--;
             if(b < 1) b = 1;             //占空比等级最小为1.
    }
