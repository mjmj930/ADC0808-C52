#ifndef __lcd1602_H__
#define __lcd1602_H__

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit E=P2^5;		//1602使能引脚
sbit RW=P2^6;		//1602读写引脚	
sbit RS=P2^7;		//1602数据/命令选择引脚

//	L1602_init(1);				//1实物焊接，0仿真
//	L1602_string(2,1,t4);		//显示字符串
//	LCD1602_ShowNum(2,2,a,5);	//显示数字



/********************************************************************
* 名称 : delay()
* 功能 : 延时,延时时间大概为140US。
* 输入 : 无
* 输出 : 无
***********************************************************************/

void lcd_delay()
{
	int i,j;
	for(i=0; i<=10; i++)
	for(j=0; j<=2; j++)
		;
}

/********************************************************************
* 名称 : enable(uchar del)
* 功能 : 1602命令函数
* 输入 : 输入的命令值
* 输出 : 无
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
* 名称 : write(uchar del)
* 功能 : 1602写数据函数
* 输入 : 需要写入1602的数据
* 输出 : 无
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
* 名称 : L1602_init()
* 功能 : 1602初始化，请参考1602的资料
* 输入 : 无
* 输出 : 无
***********************************************************************/
void L1602_init(int use)			//1实物焊接，0仿真
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
* 名称 : L1602_char(uchar hang,uchar lie,char sign)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符显示"b" ，调用该函数如下
		 L1602_char(1,5,'b')
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
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
* 名称 : L1602_string(uchar hang,uchar lie,uchar *p)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符开始显示"ab cd ef" ，调用该函数如下
	 	 L1602_string(1,5,"ab cd ef;")
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
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

int LCD1602_POW(int x,int y)  		//x的y次方
{
	unsigned char i;
	int Result=1;
	for(i=0;i<y;i++)
		Result*=x;
	return Result;
}
/********************************************************************
* 名称 : LCD1602_ShowNum(unsigned char Line,unsigned char Colum, unsigned int Number,unsigned char Length )
* 功能 : hang：1或2		lie：1-16			Number：写入的数字   0~65536			Length：数字长度
* 输入 : 行，列，需要输入1602的数据，数字长度
* 输出 : 无
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
		write('0'+Number/LCD1602_POW(10,i-1)%10);  //从数字转Asiic表  0x30或'0'就是标的字符0开始这样加上多少就是显示多少数字       
	}
 
}
#endif



