#include <stdio.h>
#include <stdlib.h>
#include "control.h"

int main()
{
	while (1) {
		init();	
		Welcome_page_control();
		cleardevice();   //���ҳ����Ϣ
		if (Game_modle == 1) {    //����ģʽ
			Online_page_control();    //��������ҳ��Ŀ���
		}
		else if (Game_modle == 3) {   //�ؿ�ģ��
			Look_back_page_control();    //չʾ�ؿ�ҳ��
			//SomeCode
		}
		Init_time();    //����ʱ��
		while (1) {
			if (control())break;
			Flush_screen();
		}
	}
	return 0;
}