//���ֿ���ʹ�ܶ�(ģ����������5V)
//sbit ENA1=P2^0;
//sbit ENB1=P2^3;
//sbit ENA2=P2^0;
//sbit ENB2=P2^3;
//ǰ��
sbit left_go=P1^0;
sbit left_back=P1^1;
sbit right_go=P1^2;
sbit right_back=P1^3;

//����
sbit left_go2=P1^4;
sbit left_back2=P1^5;
sbit right_go2=P1^6;
sbit right_back2=P1^7;
//��״̬��ʼ��
void Init()
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
//ǰ��
void go()
{

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
//����
void back()
{

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
//��ת
void left()
{
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
//��ת
void right()
{
	
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
//ֹͣ
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
