#pragma once
/*文件操作库*/
#include <stdio.h>
#include "data_structure.h"
#include "Data_link.h"
#include <time.h>

/*获取按钮信息*/
void Get_button_imfo(int Chi_button_count_offline, Chi_button_imfo button[], int Chi_button_count_online, Chi_button_imfo online_button[]
					, int Chi_button_count_welcome, Chi_button_imfo welcome_button[], int Chi_button_count_look,Chi_button_imfo look_button[])
{
	FILE* file;
	const char* file_name = "config.txt";    //配置文件
	fopen_s(&file, file_name, "r");
	if (file == NULL) {    //空文件
		printf("None!");
		return;
	}
	/////////////////////////////////////////离线按钮(界面按钮)
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file,"%c", &flag,1);
		if (flag == 'A')break;    //读取到A的时候就暂停文件读取
	}
	for (int i = 0; i < Chi_button_count_offline; i++) {
		fscanf_s(file, "%d,", &button[i].x);    //按钮x位置
		fscanf_s(file, "%d,", &button[i].y);
		fscanf_s(file, "%d,", &button[i].width);    //按钮的大小(用于监控按钮点击事件)
		fscanf_s(file, "%d,", &button[i].height);
	}
	/////////////////////////////////////////(在线按钮)
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file, "%c", &flag, 1);
		if (flag == 'B')break;    //读取到B的时候就暂停文件读取
	}
	for (int i = 0; i < Chi_button_count_online; i++) {
		fscanf_s(file, "%d,", &online_button[i].x);    //按钮x位置
		fscanf_s(file, "%d,", &online_button[i].y);
		fscanf_s(file, "%d,", &online_button[i].width);    //按钮的大小(用于监控按钮点击事件)
		fscanf_s(file, "%d,", &online_button[i].height);
	}
	//////////////////////////////////////////(欢迎界面)
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file, "%c", &flag, 1);
		if (flag == 'C')break;    //读取到C的时候就暂停文件读取
	}
	for (int i = 0; i < Chi_button_count_welcome; i++) {
		fscanf_s(file, "%d,", &welcome_button[i].x);    //按钮x位置
		fscanf_s(file, "%d,", &welcome_button[i].y);
		fscanf_s(file, "%d,", &welcome_button[i].width);    //按钮的大小(用于监控按钮点击事件)
		fscanf_s(file, "%d,", &welcome_button[i].height);
	}
	//////////////////////////////////////////(回看界面)
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file, "%c", &flag, 1);
		if (flag == 'D')break;
	}
	for (int i = 0; i < Chi_button_count_look; i++) {
		fscanf_s(file, "%d,", &look_button[i].x);
		fscanf_s(file, "%d,", &look_button[i].y);
		fscanf_s(file, "%d,", &look_button[i].width);    //按钮的大小(用于监控按钮点击事件)
		fscanf_s(file, "%d,", &look_button[i].height);
		debug(look_button[i].x, look_button[i].y);
		debug(look_button[i].width, look_button[i].height);
	}
	//////////////////////////////////////////
	fclose(file);    //错误，忘记加上关闭文件流读取了
	return;
}

/*导入提醒的图片*/
void Load_reminder_img()
{
	loadimage(&reminder[0], _T("./res/reminder/reminder.png"));
	loadimage(&reminder[1], _T("./res/reminder/reminder_mask.png"));
}

/*载入棋盘信息*/
void Load_chess_board_img(IMAGE* chess_board_img)
{
	loadimage(chess_board_img, _T("./res/Chess_board_img.png"));
	return;
}

/*载入欢迎界面按钮图像*/
void Load_welcome_button(Chi_button_imfo* button)
{
	//遮罩图
	loadimage(&((button + 0)->img[0]), _T("./res/button/welcome/1_m.png"));
	loadimage(&((button + 1)->img[0]), _T("./res/button/welcome/2_m.png"));
	loadimage(&((button + 2)->img[0]), _T("./res/button/welcome/3_m.png"));
	//真图
	loadimage(&((button + 0)->img[1]), _T("./res/button/welcome/1.png"));
	loadimage(&((button + 1)->img[1]), _T("./res/button/welcome/2.png"));
	loadimage(&((button + 2)->img[1]), _T("./res/button/welcome/3.png"));
	return;
}

/*载入在线按钮图像*/
void Load_online_button_img(Chi_button_imfo* button)
{
	//遮罩图
	loadimage(&((button + 0)->img[0]), _T("./res/button/online/1_m.png"));
	loadimage(&((button + 1)->img[0]), _T("./res/button/online/2_m.png"));
	loadimage(&((button + 2)->img[0]), _T("./res/button/online/3_m.png"));
	loadimage(&((button + 3)->img[0]), _T("./res/button/online/4_m.png"));
	loadimage(&((button + 4)->img[0]), _T("./res/button/online/5_m.png"));
	//真图
	loadimage(&((button + 0)->img[1]), _T("./res/button/online/1.png"));
	loadimage(&((button + 1)->img[1]), _T("./res/button/online/2.png"));
	loadimage(&((button + 2)->img[1]), _T("./res/button/online/3.png"));
	loadimage(&((button + 3)->img[1]), _T("./res/button/online/4.png"));
	loadimage(&((button + 4)->img[1]), _T("./res/button/online/5.png"));
	return;
}

/*载入回看界面按钮图像*/
void Load_Look_back_button(Chi_button_imfo* button)
{
	//遮罩图
	loadimage(&((button + 0)->img[0]), _T("./res/button/look_back/1_m.png"));
	loadimage(&((button + 1)->img[0]), _T("./res/button/look_back/2_m.png"));
	loadimage(&((button + 2)->img[0]), _T("./res/button/look_back/3_m.png"));
	//真图
	loadimage(&((button + 0)->img[1]), _T("./res/button/look_back/1.png"));
	loadimage(&((button + 1)->img[1]), _T("./res/button/look_back/2.png"));
	loadimage(&((button + 2)->img[1]), _T("./res/button/look_back/3.png"));
	return;
}

/*载入按钮图像*/
void Load_buuton_img(Chi_button_imfo* button)
{

	//真图
	loadimage(&((button + 0)->img[1]), _T("./res/button/1.png"));
	loadimage(&((button + 1)->img[1]), _T("./res/button/2.png"));
	loadimage(&((button + 2)->img[1]), _T("./res/button/3.png"));
	loadimage(&((button + 3)->img[1]), _T("./res/button/4.png"));
	loadimage(&((button + 4)->img[1]), _T("./res/button/5.png"));
	return;
}

/*反转图像*/
void Reverse_img(IMAGE Chess_img[])
{
	for (int i = 8; i <= 14; i++)
	{
		IMAGE temp = Chess_img[i];
		Chess_img[i] = Chess_img[i%8+1];
		Chess_img[i % 8 + 1] = temp;
	}
	return;
}

/*载入象棋图像*/
void Load_chess_img(IMAGE Chess_img[], IMAGE* Chess_mask)
{
	loadimage(&Chess_img[1], _T("./res/chess/1.png"));
	loadimage(&Chess_img[2], _T("./res/chess/2.png"));
	loadimage(&Chess_img[3], _T("./res/chess/3.png"));
	loadimage(&Chess_img[4], _T("./res/chess/4.png"));
	loadimage(&Chess_img[5], _T("./res/chess/5.png"));
	loadimage(&Chess_img[6], _T("./res/chess/6.png"));
	loadimage(&Chess_img[7], _T("./res/chess/7.png"));
	loadimage(&Chess_img[8], _T("./res/chess/8.png"));
	loadimage(&Chess_img[9], _T("./res/chess/9.png"));
	loadimage(&Chess_img[10], _T("./res/chess/10.png"));
	loadimage(&Chess_img[11], _T("./res/chess/11.png"));
	loadimage(&Chess_img[12], _T("./res/chess/12.png"));
	loadimage(&Chess_img[13], _T("./res/chess/13.png"));
	loadimage(&Chess_img[14], _T("./res/chess/14.png"));
	loadimage(Chess_mask, _T("./res/chess/chess_mask.png"));    //遮罩图
	return;
}

/*读取存档*/
/*                  *存档名           棋盘        *局势  */
void Read_doc(char* file_name, int Chess_board[][9], int* whoisturn, int* hostman)
{
	FILE* file;
	fopen_s(&file, file_name, "r");
	if (file == NULL)return;          //空文件返回
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			fscanf_s(file, "%d", &Chess_board[i][j]);
		}
	}
	fscanf_s(file, "%d", whoisturn);    //读取是谁的回合
	*hostman = *whoisturn;
	fclose(file);
	return;
}

/*保存存档*/
/*                  *存档名           棋盘        局势  */
void Save_doc(char* file_name, int Chess_board[][9], int whoisturn)
{
	FILE* file;
	fopen_s(&file, file_name, "w+");
	if (file == NULL)return;          //空文件返回
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			fprintf_s(file, "%d ", Chess_board[i][j]);
		}
		fprintf_s(file, "\n");
	}
	fprintf_s(file, "%d\n", whoisturn);    //记录是谁的局
	fclose(file);    //关闭文件才能保存
	return;
}

/*游戏结束后保存棋子路径*/
void Save_chess_mark()
{
	FILE* file;
	fopen_s(&file,"history_comp.txt", "a+");    //再进行存存储
	if (file == NULL)return;          //空文件返回
	if (Chess_move_head == NULL)return;    //如果没有走棋信息，Ps:绝对有问题，怎么可能呢？
	Chess_move_imfo* temp = Chess_move_head;
	int step_count = 0;
	while (temp != NULL)   //先获取到数目
	{
		temp = temp->down;
		step_count++;
	}
	temp = Chess_move_head;    //又回到起点
	fprintf_s(file ,"@%d", step_count);    //输出数量
	for (int i = 0; i < step_count; i++,temp = temp->down) {
		fprintf_s(file, "+%d-%d-%d,%d-%d-%d", temp->move_who_x, temp->move_who_y , temp->move_who_id, temp->ate_who_x , temp->ate_who_y, temp->ate_who_id);    //写入走位数据
	}
	fprintf_s(file, "\n");
	fclose(file);    //关闭文件
	//--------------获取时间代码来源:https://zhidao.baidu.com/question/558299804.html
	fopen_s(&file, "history_comp_concise.txt", "a+");    //再进行简要信息存储
	if (file == NULL)return;
	time_t time_imfo;
	struct tm p;    //时间信息指针
	time(&time_imfo);    //获取时间信息
	gmtime_s(&p, &time_imfo);    //格式化时间信息到结构体中
	if (To_id[4] == 0) fprintf_s(file, "@(%s)(%s)(%d-%d-%d)\n", "NONE!", "NONE!", 1900 + p.tm_year, 1 + p.tm_mon, p.tm_mday);   //判断离线模式的记录存储
	else fprintf_s(file, "@(%s)(%s)(%d-%d-%d)\n", My_id, To_id, 1900+p.tm_year,1+p.tm_mon,p.tm_mday );    //我的名称，对手名称，时间(  年(从1900开始), 月(从0开始), 日(正常))
	fclose(file);   //关闭文件
	return;
}

/*读取chess_mark
默认读取第一次的数据*/
void Read_chess_mark(int index)
{
	FILE* file;
	fopen_s(&file, "history_comp.txt", "r");    //再进行存存储
	if (file == NULL)return;    //空文件
	Clear_link_node(&Chess_move_head, &Chess_move_tail);    //清空所有节点
	char ch;
	int mark_flag = 0;
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file, "%c", &flag, 1);
		if (flag == '@')++mark_flag;    //读取到index的时候就暂停文件读取
		if (mark_flag == index)break;
	}
	int step_count;
	fscanf_s(file, "%d", &step_count);    //获取个数，方便后面节点的加入
	debug(step_count, mark_flag);
	for (int i = 0; i < step_count; i++) {
		int mov_x, mov_y,mov_id, eat_x, eat_y,eat_id;
		fscanf_s(file, "+%d-%d-%d,%d-%d-%d",&mov_x, &mov_y,&mov_id, &eat_x, &eat_y, &eat_id);
		printf("+%d-%d,%d-%d\n", mov_x, mov_y, eat_x, eat_y);
		Push_link_node(&Chess_move_head, &Chess_move_tail, mov_x, mov_y, eat_x, eat_y,mov_id, eat_id);    //增加节点	
	}
	fclose(file);    //关闭文件
	Chess_move_pointer = Chess_move_head;    //将指针指向头节点
	return;
}

/*获取回看记录的最大值*/
int Get_look_mark_max()
{
	int Look_mark_max = 0;     //初始有一个标志位
	FILE* file;
	fopen_s(&file, "history_comp_concise.txt", "r");    //读取文件
	if (file == NULL)return 0;
	char ch;
	while (fscanf_s(file, "%c", &ch, 1)!=EOF)
	{
		if (ch == '@')Look_mark_max++;    //读取到文件标志位（后面为格式化的信息）
	}
	fclose(file);
	return Look_mark_max;
}