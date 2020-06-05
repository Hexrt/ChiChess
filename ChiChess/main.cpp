#include <stdio.h>
#include <stdlib.h>
#include "control.h"

int main()
{
	while (1) {
		init();	
		Welcome_page_control();
		cleardevice();   //清楚页面信息
		if (Game_modle == 1) {    //在线模式
			Online_page_control();    //进入在线页面的控制
		}
		else if (Game_modle == 3) {   //回看模块
			Look_back_page_control();    //展示回看页面
			//SomeCode
		}
		Init_time();    //重置时间
		while (1) {
			if (control())break;
			Flush_screen();
		}
	}
	return 0;
}