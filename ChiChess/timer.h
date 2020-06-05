#pragma once

#include "data_structure.h"

//设置一个定时器
int set_timer(int* flag, int needed_time)
{
	static int 	timer_end;
	static int timer_start;    //静态变量
	if (*flag) {
		timer_end = clock();
	}
	else {
		timer_end = clock();
		timer_start = clock();
		(*flag)++;    //将标志位++
	}
	return(needed_time - (int)(double)((timer_end - timer_start) / CLOCKS_PER_SEC) > 0);    //没到时间
}

//初始化定时器
void Init_time()
{
	Timer.rememder = Timer_loop;
	Timer.end = Timer.start = clock();
	Timer.text_rememder[0] = '6';
	Timer.text_rememder[1] = '0';
	Timer.text_rememder[2] = 's';
	Timer.text_rememder[3] = 0;
	return;
}

//更新计算计时器
//@return 0超时
//@return 1正常
int Calc_time()
{
	Timer.end = clock();
	int old_remem = Timer.rememder;
	Timer.rememder = Timer_loop - (int)(double)((Timer.end - Timer.start) / CLOCKS_PER_SEC);
	if (Timer.rememder >= 0) {
		Timer.text_rememder[1] = Timer.rememder % 10 + '0';
		Timer.text_rememder[0] = Timer.rememder /10 + '0';
	}
	if (Game_modle == 3) return 1;    //游戏模式为回看模式
	return(Timer.rememder >=  0);
}