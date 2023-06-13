#include <reg52.h>			//单片机寄存器定义
#include <stdlib.h>			//atoi头文件
#include <intrins.h>		//_nop_()头文件
#include "lcd1602.h"		//1602显示屏
#include "stdio.h"			//C语言函数
#include "adc0808.h"

uchar AD_Data;						//AD0808原始数据
uint Temp; 						  	//处理后的数据
int td;
int num;
char txt[15];





void main()
{
    int n = 0;
    L1602_init(0);		//1实物焊接，0仿真
    TimeInitial();

    while(1)
    {
        L1602_string(1, 8, "V");
        //---------------ADC0808测数据-------------------------------
        addselect(td);								//选择通道0-7
        if(num > 40)									//程序每50次循环，通道+1
        {
            td++;
            if(td > 4)								//0-7循环
                td = 0;
            num = 0;
        }
        else
        {
            num++;
        }
        AD_Data = adc0808read();						//读取adc0809的数据，返回int类型变量
        Temp = (AD_Data * 1.0 / 255 * 5) * 100; 	//数据处理：输出值=输入值*5/255  参数5是基准电压5V
        if(td == 0)
        {
            sprintf(txt, "A:%d.%2d", Temp / 100, Temp % 100);
            L1602_string(1, 1, txt);
        }
        else if(td == 1)
        {
            sprintf(txt, "B:%d.%2d", Temp / 100, Temp % 100);
            L1602_string(1, 1, txt);		//显示字符串
        }
        else if(td == 2)
        {
            sprintf(txt, "C:%d.%2d", Temp / 100, Temp % 100);
            L1602_string(1, 1, txt);		//显示字符串
        }
        else if(td == 3)
        {
            sprintf(txt, "D:%d.%2d", Temp / 100, Temp % 100);
            L1602_string(1, 1, txt);		//显示字符串
        }

    }
}



