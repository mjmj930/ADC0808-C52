#include <reg52.h>			//��Ƭ���Ĵ�������
#include <stdlib.h>			//atoiͷ�ļ�
#include <intrins.h>		//_nop_()ͷ�ļ�
#include "lcd1602.h"		//1602��ʾ��
#include "stdio.h"			//C���Ժ���
#include "adc0808.h"

uchar AD_Data;						//AD0808ԭʼ����
uint Temp; 						  	//����������
int td;
int num;
char txt[15];





void main()
{
    int n = 0;
    L1602_init(0);		//1ʵ�ﺸ�ӣ�0����
    TimeInitial();

    while(1)
    {
        L1602_string(1, 8, "V");
        //---------------ADC0808������-------------------------------
        addselect(td);								//ѡ��ͨ��0-7
        if(num > 40)									//����ÿ50��ѭ����ͨ��+1
        {
            td++;
            if(td > 4)								//0-7ѭ��
                td = 0;
            num = 0;
        }
        else
        {
            num++;
        }
        AD_Data = adc0808read();						//��ȡadc0809�����ݣ�����int���ͱ���
        Temp = (AD_Data * 1.0 / 255 * 5) * 100; 	//���ݴ������ֵ=����ֵ*5/255  ����5�ǻ�׼��ѹ5V
        if(td == 0)
        {
            sprintf(txt, "A:%d.%2d", Temp / 100, Temp % 100);
            L1602_string(1, 1, txt);
        }
        else if(td == 1)
        {
            sprintf(txt, "B:%d.%2d", Temp / 100, Temp % 100);
            L1602_string(1, 1, txt);		//��ʾ�ַ���
        }
        else if(td == 2)
        {
            sprintf(txt, "C:%d.%2d", Temp / 100, Temp % 100);
            L1602_string(1, 1, txt);		//��ʾ�ַ���
        }
        else if(td == 3)
        {
            sprintf(txt, "D:%d.%2d", Temp / 100, Temp % 100);
            L1602_string(1, 1, txt);		//��ʾ�ַ���
        }

    }
}



