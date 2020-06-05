#pragma once

#include "rules.h"
#include "timer.h"
#include "Data_link.h"
#include "draw.h"
#include "net_work.h"

void  Play_zheng(int *);   //正放记录
void  Play_back();    //倒放记录

/*判断是该点否在棋子的范围内
@_1 棋子 _2 鼠标*/
char in_circle(int x_1, int y_1, int x_2, int y_2) {
	return ((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2)) <= Chess_radius * Chess_radius;
}


/*判断是否在欢迎界面按钮方框内
@mous 鼠标位置*/
char in_welcome_button(int id, int mous_x, int mous_y) {
	return (Welcome_button[id].x < mous_x && Welcome_button[id].y < mous_y && Welcome_button[id].x + Welcome_button[id].width > mous_x && Welcome_button[id].y + Welcome_button[id].height > mous_y);
}


/*判断是否在方框内
@mous 鼠标位置*/
char in_button(int id, int mous_x, int mous_y) {
	return (Chi_button[id].x < mous_x && Chi_button[id].y < mous_y && Chi_button[id].x + Chi_button[id].width > mous_x&& Chi_button[id].y + Chi_button[id].height > mous_y);
}


/*判断是否在在线按钮方框内
@mous 鼠标位置*/
char in_online_button(int id, int mous_x, int mous_y) {
	return (Online_button[id].x < mous_x && Online_button[id].y < mous_y && Online_button[id].x + Online_button[id].width > mous_x && Online_button[id].y + Online_button[id].height > mous_y);
}
/*判断是否在在线按钮方框内
@mous 鼠标位置*/
char in_look_back_button(int id, int mous_x, int mous_y) {
	return (Look_back_button[id].x < mous_x && Look_back_button[id].y < mous_y && Look_back_button[id].x + Look_back_button[id].width > mous_x && Look_back_button[id].y + Look_back_button[id].height > mous_y);
}

/*增加棋子走位记录*/
void Mark_chess_move(int cli_x, int cli_y, int sel_x, int sel_y)
{
	Push_link_node(&Chess_move_head, &Chess_move_tail, cli_x,cli_y, sel_x, sel_y,0 ,0);
}

/*悔棋信息*/
void Regret_move()
{
	if (Chess_move_head == NULL)return;    //空节点就返回
	if (Game_modle == 1) {
		whoisturn = hostman;    //(在线模式)悔棋肯定是本机的人悔棋啊QAQ
	}
	else {
		whoisturn = !whoisturn;    //(离线模式，肯定是下完棋才能悔棋，所以该反过来)
		hostman = !hostman;
	}
	Link_regret(&Chess_move_head, &Chess_move_tail, hostman);
}


/*鼠标点击
@return 0 点击无有效事件(外边框)
@return 1 点击棋子(选择了棋子)
@return 2 点击按钮*/
int Click() {
	MOUSEMSG mous;
	if (MouseHit()) {    //如果没有鼠标事件就退出
		mous = GetMouseMsg();
		//外边界
		if (!mous.mkLButton)return 0;
		if (mous.x < Chi_square * Chi_bor_left - Chess_radius || mous.x > Chi_width - Chi_square * Chi_bor_right + Chess_radius || mous.y < Chi_square * Chi_bor_top - Chess_radius || mous.y > Chi_height - Chi_square * Chi_bor_button + Chess_radius) {
			for (int i = 0; i < 3; i++) {
				if (in_button(i, mous.x, mous.y)) {
					button_select_id = i;    //保存哪个按钮被点击
					return 2;    //点击了按钮
				}
			}
			return 1;    //无效事件
		}

		//不在河界内
		if (mous.y < Chi_square * Chi_bor_top + Chi_square * 4 + Chi_square * Chess_radius||    //上地盘
			mous.y > Chi_square* Chi_bor_top + Chi_square * 5 - Chi_square * Chess_radius) {    //下地盘
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 10; j++) {
					if (in_circle(Chi_square * i + Chi_square * Chi_bor_left, Chi_square * j + Chi_square * Chi_bor_top, mous.x, mous.y)) {
						if (!Chess_board[j][i])return 0;    //如果没有棋子在这的话，直接返回
						int check_turn = (hostman==whoisturn)? 1 : 0;     //对应的判断要倒置
						if (Game_modle == 2)check_turn = whoisturn;    //错误，未能及时更新判断离线模式
						if ((check_turn == 0 && Chess_board[j][i] <= 7) || (check_turn == 1 && Chess_board[j][i] >= 8)) return 0;    //选的对方的棋子，返回0
						cur_click.x = i; cur_click.y = j;    //否则存在有效事件更新返回
						debug(i,j);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


/*鼠标再次点击
@return 0 : 没有点击事件
@return 1 : 成功点击棋子
@return 2 : 点击了其他地方*/
int Select() {
	MOUSEMSG mous;
	if (MouseHit()) {
		mous = GetMouseMsg();
		//外边界
		if (!mous.mkLButton)return 0;
		if (mous.x < Chi_square * Chi_bor_left - Chess_radius || mous.x > Chi_width - Chi_square * Chi_bor_right + Chess_radius ||
			mous.y < Chi_square * Chi_bor_top - Chess_radius || mous.y > Chi_height - Chi_square * Chi_bor_button + Chess_radius)return 2;
		//河界
		if (mous.y < Chi_square * Chi_bor_top + Chi_square * 4 + Chi_square * Chess_radius ||    //上地盘
			mous.y > Chi_square* Chi_bor_top + Chi_square * 5 - Chi_square * Chess_radius) {    //下地盘
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 10; j++) {
					if (in_circle(Chi_square * i + Chi_square * Chi_bor_left, Chi_square * j + Chi_square * Chi_bor_top, mous.x, mous.y)) {
						cur_select.x = i; cur_select.y = j;
						debug(i, j);
						return 1;
					}
				}
			}
		}
		return 2;
	}
	return 0;
}

/*反转坐标
专门用于处理服务器传来的数据*/
void Reverse_position()
{
	cur_click_ol.x = 8 - cur_click_ol.x;
	cur_click_ol.y = 9 - cur_click_ol.y;
	cur_select_ol.x = 8 - cur_select_ol.x;
	cur_select_ol.y = 9 - cur_select_ol.y;
	return;
}


/*回看界面的鼠标监测模块*/
int Look_back_page_click()
{
	MOUSEMSG mous;
	if (MouseHit()) {    //如果没有鼠标事件就退出
		mous = GetMouseMsg();
		if (mous.mkLButton)
		{
			for (int i = 0; i < 3; i++) {
				if (in_look_back_button(i, mous.x, mous.y))
				{
					button_select_id = i;    //用这个保存哪个按钮被点击
					return 1;
				}
			}
		}
	}
	return 0;
}

/*回看按钮事件*/
int Look_back_button_down()
{
	static int Look_next = 1;
	int Look_mark_max = Get_look_mark_max();
	if (button_select_id == 0) {
		if (Look_next > 1)Look_next--;
		Show_history(Look_next, Look_mark_max);
		return 0;
	}
	else if (button_select_id == 1) {
		if (Look_next < Look_mark_max)Look_next++;
		Show_history(Look_next, Look_mark_max);
		return 1;
	}
	else {
		Read_chess_mark(Look_next);    //读取数据
		return 2;
	}
	return 2;    //错误，防止卡死
}

/*在线页面按钮事件
@return 0 点击无有效事件
@return 1 点击按钮*/
int Online_button_click()
{
	MOUSEMSG mous;
	if (MouseHit()) {    //如果没有鼠标事件就退出
		mous = GetMouseMsg();
		if (!mous.mkLButton)return 0;
		for (int i = 0; i < 5; i++) {
			if (in_online_button(i, mous.x, mous.y)) {
				if(button_select_id == i)return 0;    //用这个保存哪个按钮被点击
				button_select_id = i;
				return 1;    //点击了按钮
			}
		}
	}
	return 0;
}

/*在线页面按钮事件*/
int Online_button_down()
{
	if (button_select_id == 0) {    //连接服务器
		Connect_server();
		Regist();
	}
	else if (button_select_id == 1) {
		Get_online();    //获取在线列表
	}
	else if (button_select_id == 2) {
		if (!Connect_player())return 1;    //连接失败退出
		else {
			hostman = 1;    //第二个按钮是邀请人，所以作为主方先下棋hostman = 1
			return 4;    //成功连接进入游戏
		}
	}
	else if (button_select_id == 3) {
		Online_requre = 0;    //等待请求前，重置为0
		Waite_connect();
		///SomeCoe
	}
	else if (button_select_id == 4) {
		if (Online_requre == 1) {
			hostman = 0;    //第三个按钮是被人邀请，所以作为客方后下棋hostman = 0
			debug(5,5);
			Ok_back(1);    //选择进入游戏后反馈给邀请人（顺便同步时间）
			Online_add_thread();    //这里就是解决，重复头文件包含的另开线程
		}
		else
		{
			Game_modle = 2;    //错误，忘记判断直接进入游戏的情况（后期代码修改为严禁提前进入游戏）
		}
		outtextxy(100, 50, _T("退出在线模式\n"));
	}
	return button_select_id;
}

/*非在线按钮事件（在线包含事件2,3，不包含事件1）*/
void Button_down(int* who_win)
{
	//防止重复点击
	static int mark_click = -1, mark_turn = -1;
	if (mark_turn != whoisturn) {
		mark_click = -1;
		mark_turn = whoisturn;
	}
	if (mark_click == button_select_id) return;
	else mark_click = button_select_id;


	if (button_select_id == 0 && Game_modle == 2) {    //第一个按钮（只能离线看）
		char modle_1[] = "./res/docs/";
		char modle_2[] = ".txt";
		char file_path[30];
		int index = 0;
		memset(file_path, 0 ,sizeof file_path);
		TCHAR s[10];    //用于接受InputBox的参数
		if (!InputBox(s, 10, _T("请输入 5位 您想要读取的存档名称："), _T("中国象棋"), _T("20200"), 0, 0, false))return;    //同下
		for (int i = 0; modle_1[i]; i++)file_path[index++] = modle_1[i];
		for (int i = 0; i < 5; i++)file_path[index++] = s[i];
		for (int i = 0; modle_2[i]; i++)file_path[index++] = modle_2[i];
		Read_doc(file_path,Chess_board,&whoisturn,&hostman);     //读取文件
	}
	else if (button_select_id == 1) {                  //第二个按钮
		if (Game_modle != 3)
		{
			char modle_1[] = "./res/docs/";
			char modle_2[] = ".txt";
			char file_path[30];
			int index = 0;
			memset(file_path, 0, sizeof file_path);
			TCHAR s[10];    //用于接受InputBox的参数
			if (!InputBox(s, 10, _T("请输入 5位 您想要保存的存档名称："), _T("中国象棋"), _T("20200"), 0, 0, false))return;    //没输入信息就返回
			for (int i = 0; modle_1[i]; i++)file_path[index++] = modle_1[i];
			for (int i = 0; i < 5; i++)file_path[index++] = s[i];
			for (int i = 0; modle_2[i]; i++)file_path[index++] = modle_2[i];
			Save_doc(file_path, Chess_board, whoisturn);    //保存文档
		}
		else {
			Play_back();    //回看
		}
	}
	else if (button_select_id == 2) {                  //第三个按钮
		if (Game_modle == 1) 
		{    
			Regret_requre = 0;
			request_regret();    //发送请求
			int flag = 0;
			while (!Regret_requre && set_timer(&flag, 10)) Put_timer();    //放置时钟; 直到结束(在线模式10s等待)设置计时器
			if (Regret_requre == 1) {
				Regret_move();                          //自己悔棋操作 
			}
			else {
				outtextxy(100, 50, _T("对方拒绝了你的请求\n"));    //及时反馈
			}
		}
		else if (Game_modle == 2) 
		{
			Regret_move();    //悔棋
		}
		else
		{
			Play_zheng(who_win);   //正看Debug！
		}
	}
	button_select_id = -1;
	return;
}

/*控制走位
@return 0 正常
@return 1 红方胜利
@return 2 黑方胜利*/
int Move(int cli_x, int cli_y, int sel_x, int sel_y)
{
	if (cli_x == sel_x && cli_y == sel_y)return 0;
	//Play_reminder();    //播放音乐
	if (Chess_board[sel_y][sel_x] == 1 || Chess_board[sel_y][sel_x] == 8) {
		MessageBox(NULL, TEXT("客官是否要重新再来一局咩？"), TEXT("嘤嘤嘤结束了哦！"), MB_OK);   //图形弹窗,6yes,7no
		if (Game_modle == 1)Close_socket();    //关闭连接
		return (Chess_board[sel_y][sel_x]%8+1)%2 + 1;    //红胜利 (1%8+1 = 2)%2+1 = 1 ,黑胜利 (8%8+1 = 1)%2+1 = 2
	}
	Chess_board[sel_y][sel_x] = Chess_board[cli_y][cli_x];
	Chess_board[cli_y][cli_x] = 0;
	whoisturn = !whoisturn;    //换个回合
	if (Game_modle == 2)hostman = !hostman;    //如果不是在线的话也要相应的更新
	Online_date_new = 0;    //数据已经用过了，重置为0
	return 0;
}

/*欢迎界面的鼠标监测模块*/
int Welcome_page_click()
{
	MOUSEMSG mous;
	if (MouseHit()) {    //如果没有鼠标事件就退出
		mous = GetMouseMsg();
		if (mous.mkLButton)
		{
			for (int i = 0; i < 3; i++) {
				if (in_welcome_button(i, mous.x, mous.y))
				{
					button_select_id = i;    //用这个保存哪个按钮被点击
					return 1;
				}
			}
		}
	}
	return 0;
}

/*正放-》*/
void  Play_zheng(int* whowin)
{
	*whowin = Move(Chess_move_pointer->move_who_x, Chess_move_pointer->move_who_y, Chess_move_pointer->ate_who_x, Chess_move_pointer->ate_who_y);    //直接移动
	if (Chess_move_pointer != NULL)Chess_move_pointer = Chess_move_pointer->down;    //如果下一个不为空就往下走
	if (Chess_move_pointer == NULL)Chess_move_pointer = Chess_move_tail;    //如果往下走后为空，就让他等于头
	return;
}

/*回放《-*/
void Play_back()
{
	Move(Chess_move_pointer->move_who_x, Chess_move_pointer->move_who_y, Chess_move_pointer->ate_who_x, Chess_move_pointer->ate_who_y);    //直接移动
	Chess_board[Chess_move_pointer->move_who_y][Chess_move_pointer->move_who_x] = Chess_move_pointer->move_who_id;    //直接让棋盘中的数据等于回放指针的数据
	Chess_board[Chess_move_pointer->ate_who_y][Chess_move_pointer->ate_who_x] = Chess_move_pointer->ate_who_id;    //同上
	if (Chess_move_pointer != NULL)Chess_move_pointer = Chess_move_pointer->up;
	if (Chess_move_pointer == NULL)Chess_move_pointer = Chess_move_head;    //如果往下走后为空，就让他等于头
	return;
}

/*回看页面控制 上一个 下一个 确定*/
void Look_back_page_control()
{
	Look_back_page();
	while (1) {
		while (!Look_back_page_click());    //等待鼠标事件
		Look_back_page();
		if (Look_back_button_down() == 2)break;    //如果选择了确定键就返回
	}
	//Play_zheng();
	return;
}

/*欢迎界面控制 在线 离线 回看*/
void Welcome_page_control()
{
	Welcome_page();
	FlushMouseMsgBuffer();    //清除鼠标缓存
	while (!Welcome_page_click());
	if (button_select_id == 0)Game_modle = 1;   //在线模式
	else if (button_select_id == 1)Game_modle = 2;   //离线
	else Game_modle = 3;   //回看模式
	return;
}

/*在线模块*/
void Online_page_control()
{
	Put_online_page_img();
	Show_online_page();    //展示在线页面
	button_select_id = -1;
	static int Button_mark[5];
	memset(Button_mark, 0 , sizeof Button_mark);
	while (1) {
		if (Online_button_click())    //如果在线操作页面存在按钮点击
		{
			if (button_select_id != 0 && !Button_mark[0])continue;    //如果没注册，不能点击其他任何按钮
			if (button_select_id == 0 && Button_mark[0])continue;    //如果已经注册了，就不能再注册
			if (button_select_id == 4 && !Button_mark[3])continue;    //如果没有等待连接不能进入游戏
			Button_mark[button_select_id]++;
			if (Online_button_down() == 4) {     //第5个按钮（退出在线模式按钮）
				break;
			}
		}
	}
	Init_time();    //重置时间
	whoisturn = 1;    //无论如何都是红方先下棋
	if (whoisturn != hostman)Reverse_img(Chess_img);    //如果是黑方就要棋盘倒置
	return;
}

/*主控制程序
@return 0 正常
@return 1 红方胜利
@return 2 黑方胜利*/
int control()
{
	int click_action_type = Click();
	int who_win = 0;    //记录谁赢了
	if (whoisturn == hostman && click_action_type == 1 && Game_modle != 3) {    //只有当本轮才能操作棋子（非回看模式）
		char select_action_type = 0;
		while ((select_action_type = Select()) == 0) {
			if(!Put_timer())break;    //超时返回;    //持续监听鼠标事件(如果超时了，就停止监听)
		}
		if (select_action_type == 1 && rules() && Calc_time()) {    //符合规则走位！（超时退出）
			Mark_chess_move(cur_click.x, cur_click.y, cur_select.x, cur_select.y);    //记录棋子走位信息
			Send_move_imfo(Chess_move_tail);    //转发操作信息（由于要通过记录栈顶来发送，故在栈记录操作后面）
			Init_time();    //重置事件
			Put_timer();    //放置时钟
			who_win = Move(cur_click.x, cur_click.y, cur_select.x, cur_select.y);    //直接移动
		}
	}
	else if (click_action_type == 2) {    //点击了按钮（重头戏）
		Button_down(&who_win);
	}
	else if(whoisturn != hostman && Online_date_new){       //在线模式对对方棋子走位的操作
		Reverse_position();    //颠倒位置（因为棋盘在不同的阵营有不同的显示，所以统一坐标，解析数据）
		Mark_chess_move(cur_click_ol.x, cur_click_ol.y, cur_select_ol.x, cur_select_ol.y);    //记录棋子走位信息
		Init_time();    //重置时间
		who_win = Move(cur_click_ol.x, cur_click_ol.y, cur_select_ol.x, cur_select_ol.y);
	}
	if (who_win) {      //如果胜负已定
		if (Game_modle != 3)
		{
			char s[] = "./res/docs/1234.txt";
			Save_doc(s, Chess_board, whoisturn);    //保存文档
			Save_chess_mark();    //保存走棋信息，用于回看功能
			if (Game_modle == 1)Close_socket();    //关闭连接
		}
		return who_win;
	}
	if (!Calc_time()) {
		MessageBox(NULL, TEXT("客官是否要重新再来一局咩？"), TEXT("Sorry有人超时了哦！"), MB_OK);   //图形弹窗,6yes,7no
		Save_chess_mark();    //保存走棋信息，用于回看功能
		if (Game_modle == 1)Close_socket();    //关闭连接
		return who_win = whoisturn?2:1;    //超时返回
	}
	return 0;
}