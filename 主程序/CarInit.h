//���ֿ���ʹ�ܶ�
sbit ENA1=P2^0;
sbit ENB1=P2^3;
sbit ENA2=P2^0;
sbit ENB2=P2^3;
//ǰ��
sbit left_go=P1^2;
sbit left_back=P1^3;
sbit right_go=P1^0;
sbit right_back=P1^1;
//����
sbit left_go2=P1^6;
sbit left_back2=P1^7;
sbit right_go2=P1^4;
sbit right_back2=P1^5;
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
//����
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
//��ת
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
//��ת
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
