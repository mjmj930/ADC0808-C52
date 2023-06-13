#ifndef __lcd1602_H__
#define __lcd1602_H__

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit E=P2^5;		//1602ʹ������
sbit RW=P2^6;		//1602��д����	
sbit RS=P2^7;		//1602����/����ѡ������

//	L1602_init(1);				//1ʵ�ﺸ�ӣ�0����
//	L1602_string(2,1,t4);		//��ʾ�ַ���
//	LCD1602_ShowNum(2,2,a,5);	//��ʾ����



/********************************************************************
* ���� : delay()
* ���� : ��ʱ,��ʱʱ����Ϊ140US��
* ���� : ��
* ��� : ��
***********************************************************************/

void lcd_delay()
{
	int i,j;
	for(i=0; i<=10; i++)
	for(j=0; j<=2; j++)
		;
}

/********************************************************************
* ���� : enable(uchar del)
* ���� : 1602�����
* ���� : ���������ֵ
* ��� : ��
***********************************************************************/

void enable(uchar del)
{
	P0 = del;
	RS = 0;
	RW = 0;
	E = 0;
	lcd_delay();
	E = 1;
	lcd_delay();
}

/********************************************************************
* ���� : write(uchar del)
* ���� : 1602д���ݺ���
* ���� : ��Ҫд��1602������
* ��� : ��
***********************************************************************/

void write(uchar del)
{
	P0 = del;
	RS = 1;
	RW = 0;
	E = 0;
	lcd_delay();
	E = 1;
	lcd_delay();
}

/********************************************************************
* ���� : L1602_init()
* ���� : 1602��ʼ������ο�1602������
* ���� : ��
* ��� : ��
***********************************************************************/
void L1602_init(int use)			//1ʵ�ﺸ�ӣ�0����
{

	if(use==1)
	{
		enable(0x01);
		enable(0x38);
		enable(0x0c);
		enable(0x06);
		enable(0xd0);		
	}
	else
	{
		enable(0x38);
		enable(0x0c);
		enable(0x06);
		enable(0x01);	
	}

}

/********************************************************************
* ���� : L1602_char(uchar hang,uchar lie,char sign)
* ���� : �ı�Һ����ĳλ��ֵ�����Ҫ�õ�һ�У�������ַ���ʾ"b" �����øú�������
		 L1602_char(1,5,'b')
* ���� : �У��У���Ҫ����1602������
* ��� : ��
***********************************************************************/
void L1602_char(uchar hang,uchar lie,char sign)
{
	uchar a;
	if(hang == 1) a = 0x80;
	if(hang == 2) a = 0xc0;
	a = a + lie - 1;
	enable(a);
	write(sign);
}

/********************************************************************
* ���� : L1602_string(uchar hang,uchar lie,uchar *p)
* ���� : �ı�Һ����ĳλ��ֵ�����Ҫ�õ�һ�У�������ַ���ʼ��ʾ"ab cd ef" �����øú�������
	 	 L1602_string(1,5,"ab cd ef;")
* ���� : �У��У���Ҫ����1602������
* ��� : ��
***********************************************************************/
void L1602_string(uchar hang,uchar lie,uchar *p)
{
	uchar a;
	if(hang == 1) a = 0x80;
	if(hang == 2) a = 0xc0;
	a = a + lie - 1;
	enable(a);
	while(1)
	{
		if(*p == '\0') break;
		write(*p);
		p++;
	}

}

int LCD1602_POW(int x,int y)  		//x��y�η�
{
	unsigned char i;
	int Result=1;
	for(i=0;i<y;i++)
		Result*=x;
	return Result;
}
/********************************************************************
* ���� : LCD1602_ShowNum(unsigned char Line,unsigned char Colum, unsigned int Number,unsigned char Length )
* ���� : hang��1��2		lie��1-16			Number��д�������   0~65536			Length�����ֳ���
* ���� : �У��У���Ҫ����1602�����ݣ����ֳ���
* ��� : ��
***********************************************************************/
void LCD1602_ShowNum(unsigned char hang,unsigned char lie, unsigned int Number,unsigned char Length )
{
	unsigned char i,a;
	if(hang == 1) a = 0x80;
	if(hang == 2) a = 0xc0;
	a = a + lie - 1;
	enable(a);	
	for(i=Length;i>0;i--)
	{
		write('0'+Number/LCD1602_POW(10,i-1)%10);  //������תAsiic��  0x30��'0'���Ǳ���ַ�0��ʼ�������϶��پ�����ʾ��������       
	}
 
}
#endif



