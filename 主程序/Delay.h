#define uchar unsigned char
#define uint unsigned int
 //��ʱ����
void delay(uint z)        
{
        uint x,y;
        for(x=z;x>0;x--)
                for(y=110;y>0;y--);
}