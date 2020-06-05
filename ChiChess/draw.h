#pragma once
/*这里是需要更新界面的图形测绘操作*/
#include <graphics.h>
#include "my_define.h"
#include "data_structure.h"
#include "file_action.h"
#include "timer.h"
#pragma comment(lib,"Winmm.lib")

//获取人物信息
void Get_character()
{
	whoisturn = 1;
	hostman = 1;
	return;
}

/*放置欢迎界面的按钮图片*/
void Put_welcome_img(int Welcome_button_count, Chi_button_imfo* button)
{
	for (int i = 0; i < Welcome_button_count; i++) {
		putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
	}
	return;
}

/*放置在线页面的按钮图片*/
void Put_online_button(int Online_button_count, Chi_button_imfo* button)
{
	for (int i = 0; i < Online_button_count; i++) {
		putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
	}
	return;
}


/*放置回看页面按钮图片*/
void Put_look_back_button_img(int Chi_button_count, Chi_button_imfo* button)
{
	for (int i = 0; i < Chi_button_count; i++) {
		putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
	}
	return;
}


/*放置按钮图片*/
void Put_button_img(int Chi_button_count, Chi_button_imfo* button)
{
	if (Game_modle == 3)    //回看模式的图片不同
	{
		for (int i = 3; i <= 4; i++) {
			putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
		}
	}
	else {    //离线和在线模式
		for (int i = 0; i < Chi_button_count; i++) {
			if (Game_modle != 2 && i == 0)continue;    //离线模式才能存档
			putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
		}
	}
	return;
}

/*导入在线页面图片*/
void Put_online_page_img()
{
	IMAGE temp;
	loadimage(&temp, _T("./res/Online_page.png"));
	putimage(0, 0, &temp);
}

/*放置棋子图片*/
void Put_chess_img(IMAGE Chess_img[],IMAGE Chess_mask,int Chess_board[][9])
{
	/*画棋子*/
	for (int i = 0; i < 9; i++) {    //竖,x
		for (int j = 0; j < 10; j++) {    //横,y
			if (Chess_board[j][i]) {
				//circle(squre * i + squre * bro_left, squre * j + squre * bro_top, ri);
				//if (mapp[j][i] <= 7)settextcolor(RED);
				//else settextcolor(BLUE);
				//outtextxy(squre * i + squre * bro_left - 7, squre * j + squre * bro_top - 7, cche[mapp[j][i]]);
				putimage(Chi_square * i + Chi_square * Chi_bor_left - Chess_radius, Chi_square * j + Chi_square * Chi_bor_top - Chess_radius, &Chess_mask, NOTSRCERASE);
				putimage(Chi_square * i + Chi_square * Chi_bor_left - Chess_radius, Chi_square * j + Chi_square * Chi_bor_top - Chess_radius, &Chess_img[Chess_board[j][i]], SRCINVERT);
			}
		}
	}
	return;
}

/*播放下棋的音乐*/
void Play_reminder()
{
	mciSendString(_T("close movemus"), NULL, 0, NULL);//关闭多媒体音乐文件
	mciSendString(_T("open E:\\res\\down.mp3 alias movemus"), NULL, 0, NULL);    //
	mciSendString(_T("play movemus"), NULL, 0, NULL);    //播放
	return;
}

/*放置提醒标签*/
void Put_reminder()
{
	if ((hostman == whoisturn && Game_modle==1) || (Game_modle!=1 && hostman==1)) {
		putimage(0, 470, &reminder[1], NOTSRCERASE);
		putimage(0, 470, &reminder[0], SRCINVERT);
		//outtextxy(5, 400,_T("我方！"));
	}
	else {
		putimage(0, 150, &reminder[1], NOTSRCERASE);
		putimage(0, 150, &reminder[0], SRCINVERT);
		//outtextxy(5, 100,_T("敌方！"));
	}
	return;
}

/*放置时钟*/
int Put_timer()
{
	static unsigned long long int cnt = 0;
	cnt++;
	//Sleep(10);
	BeginBatchDraw();
	Calc_time();
	if (cnt > 9999999999)cnt = 0;
	settextcolor(0x00ffff);
	if (Timer.rememder <= 15 && (cnt % 10 < 5))settextcolor(RED);
	settextstyle(26, 16, _T("仿宋体"));
	outtextxy(245, 37, LPTSTR(Timer.text_rememder));
	EndBatchDraw();
	return Calc_time();
}

/*在线页面*/
void Show_online_page()
{
	Sleep(10);
	BeginBatchDraw();
	outtextxy(175,55,_T("在线联机中心帮助"));
	outtextxy(140, 74, _T("服务器为CentOS 8.0.1905"));
	outtextxy(140, 89, _T("使用的时候尽量按照规则使用"));
	outtextxy(140, 104, _T("防止服务器不响应(菜得弄不好)"));
	outtextxy(140, 125, _T("1.首先点击注册ID（5位数）"));
	outtextxy(140, 145, _T("2.查询在线玩家，给出列表"));
	outtextxy(140, 165, _T("3.选择连接玩家或者等待被连接"));
	outtextxy(140, 185, _T("4.若连接对方玩家成功自动进入"));
	outtextxy(140, 205, _T("5.同意对方后，点击进入棋局开始"));
	setcolor(RED);
	outtextxy(130, 225, _T("连不上不要紧，肯定是我没开服务器"));
	setcolor(WHITE);
	Load_online_button_img(Online_button);
	Put_online_button(5,Online_button);
	EndBatchDraw();
	return;
}

/*欢迎界面*/
void Welcome_page()
{
	IMAGE temp;
	loadimage(&temp, _T("./res/Welcome.png"));
	putimage(0,0,&temp);
	Load_welcome_button(Welcome_button);
	Put_welcome_img(3,Welcome_button);
	return ;
}

/*展现历史记录*/
void Show_history(int Look_next, int Look_mark_max)
{
	FILE* file;
	fopen_s(&file, "history_comp_concise.txt", "r+");    //打开简明文件
	if (file == NULL)return;
	char ch;
	WCHAR my_Id[20], to_Id[20], The_Iime[20];
	//while (fscanf_s(file, "%c", &ch, 1) != EOF && ch != '@');
	int start = Look_next - 3; if (start <= 0)start = 1;
	int end = Look_next + 2; if (end > Look_mark_max)end = Look_mark_max;
	if (Look_mark_max >= 5 && Look_mark_max - Look_next <= 2)start = Look_mark_max - 4;
	if (start + 4 <= Look_mark_max)end = start + 4;    //到后头的指针往下走，但是也要保持5格
	if (Look_mark_max <= 5) {    //及时记录小于5个，也要保持5格
		start = 1;
		end = Look_mark_max;
	}
	char my_id[20], to_id[20],The_time[20];
	BeginBatchDraw();
	for (int i = 1; i <= end; i++) {
		fscanf_s(file,"\n@(%5s)",my_id, 6);
		fscanf_s(file, "(%5s)", to_id, 6);
		fscanf_s(file,"(%9s)", The_time,10);
		if (i >= start) {
			if (Look_next == i)setcolor(RED);
			memset(my_Id, 0, sizeof my_Id);    //初始化
			memset(to_Id, 0, sizeof to_Id);    //初始化
			memset(The_Iime, 0, sizeof The_Iime);    //初始化
			printf("%s\n", my_id);
			for (int i = 0; i < 5; i++)my_Id[i] = my_id[i];
			for (int i = 0; i < 5; i++)to_Id[i] = to_id[i];
			for (int i = 0; i < 10; i++)The_Iime[i] = The_time[i];
			outtextxy(125,20*(i-start+1), my_Id);
			outtextxy(225, 20 * (i - start + 1), to_Id);
			outtextxy(325, 20 * (i - start + 1), The_Iime);
			if (Look_next == i)setcolor(WHITE);
		}
		/*这里出现个问题，指针不会向下移动，因为一些参数的原因，读取失败，指针停留在一个地方*/
	}
	EndBatchDraw();
	fclose(file);
	return;
}

/*回看界面*/
void Look_back_page()
{
	cleardevice();
	Sleep(10);    //休眠，防止一闪一闪
	Load_Look_back_button(Look_back_button);    //导入图片
	Put_look_back_button_img(3, Look_back_button);
	//SomeCode
	return;
}

/*初始化画面*/
void init()
{
	char s[] = "./res/docs/6666.txt";
	int temp;    //解决Read_doc的复用性问题
	Read_doc(s, Chess_board, &whoisturn, &temp);    //读取存档（初始棋盘）
	initgraph(Chi_width, Chi_height);    //初始化画布
	Get_button_imfo(5, Chi_button, 5, Online_button, 3, Welcome_button, 3, Look_back_button);    //获取按钮信息(离线 & 在线 & 欢迎界面 & 回看)
	Load_chess_board_img(&Chess_board_img);    //载入棋盘背景
	Load_buuton_img(Chi_button);               //载入按钮图片
	Load_chess_img(Chess_img, &Chess_mask);    //载入棋子图片
	Load_reminder_img();                       //载入提醒图片
	putimage(0, 0, &Chess_board_img);          //放置背景
	Put_button_img(3, Chi_button);             //按钮
	Put_chess_img(Chess_img, Chess_mask, Chess_board); //棋子
	Get_character();    //获取当前人物是哪一方
	return;
}

/*刷新屏幕*/
void Flush_screen()
{
	Sleep(10);
	BeginBatchDraw();
	putimage(0, 0, &Chess_board_img);          //放置背景
	Put_button_img(3, Chi_button);             //按钮
	Put_chess_img(Chess_img, Chess_mask, Chess_board); //棋子
	if (Game_modle!=3)Put_reminder();    //放置当前为谁下的棋局
	if (Game_modle != 3)Put_timer();
	EndBatchDraw();
	return;
}

/*展现在线列表信息*/
void Show_online_list(char date[])
{
	WCHAR list_date[20];    //临时缓存数据
	WCHAR moDle[25];
	memset(moDle, 0 ,sizeof moDle);
	char modle[] = { "Players online list:" };
	memset(list_date, 0, sizeof list_date);
	for (int i = 0; modle[i]; i++)moDle[i] = modle[i];
	int list_count = (date[1] - '0') * 10 + date[2] - '0';
	int index = 3;
	outtextxy(150, 50, LPTSTR(moDle));
	for (int i = 1; i <= list_count; i++) {
		for(int j = 0; j < 5; j++) {
			list_date[j] = date[index++];
		}
		outtextxy(150, 50+20*i, LPTSTR(list_date));
	}
	return;
}