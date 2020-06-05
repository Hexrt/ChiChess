#pragma once
#include <graphics.h>
#include <time.h>
#include "my_define.h"
/*所使用的数据结构*/


//记录鼠标选择的位置
typedef struct _Select {
	int x;    //横向坐标
	int y;    //纵向坐标
}Chi_Select;

//按钮的信息
typedef struct _Chi_button_imfo {
	int x;    //横向坐标
	int y;
	int width;    //按钮宽度
	int height;
	char src[20];
	IMAGE img[2];    //按钮图像
}Chi_button_imfo;

//走棋信息
typedef struct _Chess_move_imfo {
	int move_who_x;    //走棋方坐标x
	int move_who_y;    //----------y
	int move_who_id;   //走棋方棋子id
	int ate_who_x;    //落棋地坐标x
	int ate_who_y;
	int ate_who_id;   //落棋id(0为空棋)
	_Chess_move_imfo* up;    //向上指针域
	_Chess_move_imfo* down;    //向下指针域
}Chess_move_imfo;


//倒计时时间信息
typedef struct _Time_clock_imfo {
	clock_t start;
	clock_t end;
	int rememder;
	TCHAR text_rememder[4];
}Time_clock_imfo;


/*这里是规划棋盘的信息*/
/*棋盘按照my_define.h中的Chi_square来作为单位长度*/
//默认布局
/*
		  -----------X
		  |
		  |
		  |
		  |
		  Y                  */

		  //默认棋子的的序号映射
		  /*
		  i--------------------------i
		  |将  士  象  馬  車  炮  卒|
		  |8   9   10  11  12  13  14|
		  |--------------------------|
		  |1   2   3   4   5   6   7 |
		  |帅  士  相  馬  車  炮  兵|
		  i--------------------------i
		  */


int Chess_board[10][9];    //记录棋盘的信息10*9 (能够放置位置的地方)
//---------------------------------------------------
Chi_button_imfo Chi_button[6];    //按钮信息
Chi_button_imfo Online_button[6];   //在线页面按钮图
Chi_button_imfo Welcome_button[4];   ///欢迎页面按钮信息
Chi_button_imfo Look_back_button[4];   ///回看页面按钮信息
Chess_move_imfo* Chess_move_head;    //双向链表的棋子走棋信息--头部
Chess_move_imfo* Chess_move_tail;    //双向链表的--尾端
Chess_move_imfo* Chess_move_pointer; //回看系统专用的指针(默认指向头节点)
//--------------------------------------------------
IMAGE Chess_board_img;    //棋盘背景图
IMAGE Chess_img[15];    //棋子图像信息(从1开始)
IMAGE Chess_mask;    //棋子遮罩图
IMAGE reminder[2];   //提醒下棋的图标
//--------------------------------------------------
int Game_modle;    //游戏模式，1，在线,2,离线，3回看
int whoisturn;	//谁的局势1红方，0黑方
int hostman;    //东道主谁操控
int Online_date_new;    //用于操控Contorl里面的判断，1为新数据可以移动了，0为还需等待
int Online_requre;      //用于在线对战的操控，1为同意，0为拒绝
int Regret_requre;      //用于悔棋的操控，1为同意，0为拒绝
//--------------------------------------------------
Chi_Select cur_click;    //鼠标点击位置
Chi_Select cur_select;    //鼠标选择位置(在cur_click之后)
Chi_Select cur_click_ol;    //鼠标点击位置（在线模式专用）
Chi_Select cur_select_ol;    //鼠标选择位置(在线模式专用)
//--------------------------------------------------
int button_select_id;    //按钮被点击的ID
Time_clock_imfo   Timer;//时间信息
//--------------------------------------------------
char To_id[7];    //需要发送给对象的ID
char My_id[7];    //本人ID
char Low_date[20];    //短数据，用于短报文的发送通常只改变前面一个值
char Date[100];       //长数据，用于接受服务器传送来的报文
const char Net_ok[] = "OK!";    //前几个编号报文的成功标志位

