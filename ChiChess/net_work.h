#pragma once
//Client
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "data_structure.h"
#include "draw.h"
#pragma comment(lib,"Ws2_32.lib ")

SOCKET client;
sockaddr_in server;    //服务器
HANDLE Recieve_thread; //接受信息的线程
HANDLE Wait_thread;    //专门用于等待连接的线程
WSADATA data;    //启动
void Ok_back(int flag);

//获取ID
void get_id(char date[], char requre_id[]) {
	for (int i = 6, j = 0; date[i]; i++) {
		requre_id[j++] = date[i];    //获取ID
	}
	return;
}

//报文数据分析----------------------------------------------------
void Date_analyze(char date[])
{
	if (date[0] == '3') {    //在线列表信息
		debug(3, 3);
		Show_online_list(date);    //展示在线列表信息
		return;
	}
	else if (date[0] == '5') {    //棋子的移动信息
		cur_click_ol.x = (date[6]-'0')*10 + (date[7] - '0');
		cur_click_ol.y = (date[8] - '0') * 10 + (date[9] - '0');
		cur_select_ol.x = (date[10] - '0') * 10 + (date[11] - '0');
		cur_select_ol.y = (date[12] - '0') * 10 + (date[13] - '0');
		Online_date_new = 1;     // 更新数据标志位为新的
	}
	else if (date[0] == '6') {    //连接请求信息
		char requre_id[7];
		memset(requre_id, 0, sizeof requre_id);
		get_id( date, requre_id);
		WCHAR message_modle[] = _T("玩家请求向你连接？确定吗？");
		WCHAR message_online[20];
		memset(message_online, 0, sizeof message_online);
		int index = 0;
		for (int i = 0; i < 2; i++) {                   //玩家两个字
			message_online[index++] = message_modle[i];
		}
		for (int i = 0; requre_id[i]; i++) {
			message_online[index++] = requre_id[i];    //插入ID在消息中
		}
		for (int i = 2; message_modle[i]; i++) {
			message_online[index++] = message_modle[i]; //完成写入
		}
		outtextxy(100, 50, LPTSTR(message_online));
		if (MessageBox(NULL, LPTSTR(message_online), TEXT("有玩家请求注意！"), MB_YESNO) == IDYES) {
			Online_requre = 1;    //同意连接，更新
			for (int i = 0; requre_id[i]; i++)To_id[i] = requre_id[i];    //将请求ID设置为请求ID
		}
		else {
			Ok_back(0);    //发送不同意信息
		}
	}
	else if (date[0] == '7') {    //任意消息(成功请求信息)
		for (int i = 6, j =0; j < 5; i++,j++) {
			if (date[i] != To_id[j]) {
				Online_requre = 0;
				Regret_requre = 0;    //不同意
				return;
			}
		}
		Online_requre = 1;      //同意连接，更新
		Regret_requre = 1;    //同意悔棋，更新
		//Show_enter_button();
		//SomeCode用于覆盖退出图片，进入游戏
	}
	else if (date[0] == '8') {
		if (MessageBox(NULL, TEXT("对方请求悔棋！是否同意呢？QAQ"), TEXT("有玩家请求注意！"), MB_YESNO) == IDYES) {
			Ok_back(1);
			whoisturn = !hostman;    //将棋局给请求方
			Link_regret(&Chess_move_head, &Chess_move_tail, !hostman);    //执行悔棋操作
		}
		else {
			Ok_back(0);    //发送不同意信息
		}
	}
	return;
}
//---------------------------------------------------
//---------------------------------------------------
//初始化
void Net_init()
{
	memset(Low_date,0,sizeof Low_date);
	memset(Date, 0, sizeof Date);
	memset(My_id, 0, sizeof My_id);
	memset(To_id, 0, sizeof To_id);   //初始化
	return;
}

//转化
void i_to_s(int* index, char s[], int number)
{
	if (number <= 9) {    //错误！未加等于导致传来的数据错误
		s[(*index)++] = '0';
	}
	else {
		s[(*index)++] = '1';
	}
	s[(*index)++] = number%10 + '0';
	return;
}

//实时监听
DWORD WINAPI rec(){
	while (Game_modle==1) {    //只有在线模式才能存在长期连接，如果游戏结束就退出
		char date[100];
		if (recv(client, date, 100, 0) > 0) {    //接收到了信息
			Date_analyze(date);
			//printf("rec:%s\n", date);
		}
		if (date[0] == 'C') {    //close!
			break;
		}
	}
	return NULL;
}

DWORD WINAPI Online_waite() {
	char date[100];
	memset(date, 0 ,sizeof date);
	recv(client, date, 100, 0);
	Date_analyze(date);
	return NULL;
}

/*关闭连接*/
int Close_socket()
{
	memset(Date, 0, sizeof Date);
	for (int i = 0; i < 5; i++)Date[i + 1] = My_id[i];
	Date[0] = '0';
	send(client, Date, sizeof Date, 0);    //发送关闭
	Game_modle = -1;    //设置模式为-1
	return 1;
}

/*注册(堵塞)
1 + 5位ID (My_id)*/
int Regist()
{
	memset(Low_date, 0, sizeof Low_date);    //初始化
	memset(Date, 0, sizeof Date);    //初始化数据包
	memset(My_id, 0, sizeof My_id);
	TCHAR s[10];    //用于接受InputBox的参数
	settextcolor(RED);
	outtextxy(100, 50, _T("----成功连接服务器----\n"));
	outtextxy(100, 50, _T("-请输入5位你的ID号码:-\n"));
	InputBox(s, 10, _T("请输入 5位 您要注册的ID(英文字母或数字)："), _T("中国象棋"), _T("12345"), 0, 0, false);
	for (int i = 0; i < 5; i++)My_id[i] = s[i];    //存入到信息中
	Low_date[0] = '1';
	for (int i = 0; My_id[i]; i++)Low_date[i + 1] = My_id[i];    //数据转化处理
	send(client, Low_date, sizeof Low_date, 0);    //发送注册信息
	recv(client, Date, 100, 0);    //接受注册效果
	for (int i = 0; Net_ok[i]; i++)if (Net_ok[i] != Date[i])return 0;    //检测是否成功
	outtextxy(150, 50, _T("-------注册ID成功------\n"));
	return 1;
}

/*重连（堵塞）
2 + 5位ID (My_id)*/
int Reconect()
{
	Low_date[0] = '2';
	memset(Date, 0, sizeof Date);
	send(client, Low_date, sizeof Low_date, 0);    //发送注册信息
	recv(client, Date, 100, 0);    //接受服务器信息
	for (int i = 0; Net_ok[i]; i++)if (Net_ok[i] != Date[i])return 0;    //检测是否成功
	return 1;
}

/*获取在线列表信息（堵塞）
3 + 5位ID (My_id)*/
void Get_online()
{
	memset(Date, 0, sizeof Date);
	Date[0] = '3';
	for (int i = 0; i < 5; i++)Date[i + 1] = My_id[i];
	send(client, Date, sizeof Date, 0);    //发送注册信息
	memset(Date, 0, sizeof Date);
	recv(client, Date, 100, 0);    //接受列表信息
	//printf("%s+++\n", Date);
	Date_analyze(Date);
	//debug(2, 2);
	//SomeCode
	return;
}

/*连接测试（堵塞）
4 + 5位ID (My_id)*/
int Keep_alive()
{
	memset(Date, 0, sizeof Date);
	Low_date[0] = '4';
	send(client, Low_date, sizeof Low_date, 0);    //发送注册信息
	recv(client, Date, 100, 0);    //接受列表信息
	for (int i = 0; Net_ok[i]; i++)if (Net_ok[i] != Date[i])return 0;    //检测是否成功
	return 1;
}

/*发送走棋信息（堵塞）
5 + 5位ID (My_id)*/
int Send_move_imfo(Chess_move_imfo* Chess_move_tail)
{
	memset(Date, 0, sizeof Date);
	Date[0] = '5'; 
	for (int i = 0; To_id[i]; i++)Date[i+1] = To_id[i];
	int len = 6;
	i_to_s(&len, Date, Chess_move_tail->move_who_x );
	i_to_s(&len, Date, Chess_move_tail->move_who_y);
	i_to_s(&len, Date, Chess_move_tail->ate_who_x);
	i_to_s(&len, Date, Chess_move_tail->ate_who_y);
	send(client, Date, sizeof Date, 0);    //发送走位信息
	printf("%s", Date);
	return 1;
}

/*连接玩家（堵塞）
6 + 5位ID + 5位ID(My_id)*/
int Connect_player()
{
	outtextxy(150, 50, _T("输入你需要连接对象的ID\n"));
	TCHAR s[10];    //用于接受InputBox的参数
	InputBox(s, 10, _T("请输入 5位 您想连接的ID："), _T("中国象棋"), _T("12345"), 0, 0, false);
	for (int i = 0; i < 5; i++)To_id[i] = s[i];    //存入到信息中
	memset(Date, 0, sizeof Date);
	Date[0] = '6';
	for (int i = 0; i<5; i++)Date[i + 1] = To_id[i];    //数据转化处理
	for (int i = 0; i<5; i++)Date[i + 6] = My_id[i];    //数据转化处理
	send(client, Date, sizeof Date, 0);    //发送连接信息
	recv(client, Date, sizeof Date, 0);    //接受信息
	for (int i = 6,j = 0; j < 5; i++, j++) {
		if (Date[i] != To_id[j]) {    //出错了！！！数组越界
			outtextxy(100, 50, _T("        连接失败！  \n"));
			return 0;    //连接失败，检测后五位为对方ID
		}
	}
	outtextxy(150, 50, _T("        连接成功！\n"));
	Recieve_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)rec, NULL, 0, NULL);    //建立监听
	CloseHandle(Recieve_thread);    //关闭句柄，但是不终止线程
	Online_date_new = 0;
	hostman = 1;
	return 1;
}

/*
7 + 5位ID + 5位ID
回应玩家用于成功连接的二次反馈(数据和6中的数据一样)
@parama[flag] 用于标志是否同意请求的标志位1同意，0不同意*/
void Ok_back(int flag)
{
	memset(Date, 0, sizeof Date);
	Date[0] = '7';
	for (int i = 0; i < 5; i++)Date[i + 1] = To_id[i];    //数据转化处理
	for (int i = 0; i < 5; i++)Date[i + 6] = My_id[i];    //数据转化处理
	if (!flag)Date[8] = '@';    //加上一个错误码用于返回否定信息
	send(client, Date, sizeof Date, 0);    //发送连接信息
	return;
}


/*悔棋信息
8 + 5位ID + 5位ID(My_id)*/
void request_regret()
{
	memset(Date, 0, sizeof Date);
	for (int i = 0; i < 5; i++)Low_date[i + 1] = To_id[i];
	Low_date[0] = '8';
	send(client, Low_date, sizeof Low_date, 0);    //发送悔棋信息
	//SomeCode
	return;
}


/*用于在数据解析里面递归包含问题的解决方案
* 在Contro中用于开一个长期线程*/
void Online_add_thread()
{
	Recieve_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)rec, NULL, 0, NULL);    //建立监听
	CloseHandle(Recieve_thread);    //关闭句柄，但是不终止线程
	return;
}


/*等待连接中*/
void Waite_connect()
{
	outtextxy(100, 50, _T("正在等待对象连接！\n"));
	Wait_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Online_waite, NULL, 0, NULL);    //建立监听
	CloseHandle(Wait_thread);    //关闭句柄，但是不终止线程
	return;
}


/*与服务器建立连接（堵塞）*/
int Connect_server()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSAStartup(sockVersion, &data);
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&server, 0, sizeof server);    //Clear and fill up with zero
	server.sin_family = AF_INET;                                 //协议簇
	server.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);    //绑定IP
	server.sin_port = htons(SERVER_PORT);    //绑定端口
	connect(client, (sockaddr*)&server, sizeof server);    //连接服务器
	Net_init();   //初始化
	return 0;
}
