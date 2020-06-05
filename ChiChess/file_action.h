#pragma once
/*�ļ�������*/
#include <stdio.h>
#include "data_structure.h"
#include "Data_link.h"
#include <time.h>

/*��ȡ��ť��Ϣ*/
void Get_button_imfo(int Chi_button_count_offline, Chi_button_imfo button[], int Chi_button_count_online, Chi_button_imfo online_button[]
					, int Chi_button_count_welcome, Chi_button_imfo welcome_button[], int Chi_button_count_look,Chi_button_imfo look_button[])
{
	FILE* file;
	const char* file_name = "config.txt";    //�����ļ�
	fopen_s(&file, file_name, "r");
	if (file == NULL) {    //���ļ�
		printf("None!");
		return;
	}
	/////////////////////////////////////////���߰�ť(���水ť)
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file,"%c", &flag,1);
		if (flag == 'A')break;    //��ȡ��A��ʱ�����ͣ�ļ���ȡ
	}
	for (int i = 0; i < Chi_button_count_offline; i++) {
		fscanf_s(file, "%d,", &button[i].x);    //��ťxλ��
		fscanf_s(file, "%d,", &button[i].y);
		fscanf_s(file, "%d,", &button[i].width);    //��ť�Ĵ�С(���ڼ�ذ�ť����¼�)
		fscanf_s(file, "%d,", &button[i].height);
	}
	/////////////////////////////////////////(���߰�ť)
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file, "%c", &flag, 1);
		if (flag == 'B')break;    //��ȡ��B��ʱ�����ͣ�ļ���ȡ
	}
	for (int i = 0; i < Chi_button_count_online; i++) {
		fscanf_s(file, "%d,", &online_button[i].x);    //��ťxλ��
		fscanf_s(file, "%d,", &online_button[i].y);
		fscanf_s(file, "%d,", &online_button[i].width);    //��ť�Ĵ�С(���ڼ�ذ�ť����¼�)
		fscanf_s(file, "%d,", &online_button[i].height);
	}
	//////////////////////////////////////////(��ӭ����)
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file, "%c", &flag, 1);
		if (flag == 'C')break;    //��ȡ��C��ʱ�����ͣ�ļ���ȡ
	}
	for (int i = 0; i < Chi_button_count_welcome; i++) {
		fscanf_s(file, "%d,", &welcome_button[i].x);    //��ťxλ��
		fscanf_s(file, "%d,", &welcome_button[i].y);
		fscanf_s(file, "%d,", &welcome_button[i].width);    //��ť�Ĵ�С(���ڼ�ذ�ť����¼�)
		fscanf_s(file, "%d,", &welcome_button[i].height);
	}
	//////////////////////////////////////////(�ؿ�����)
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file, "%c", &flag, 1);
		if (flag == 'D')break;
	}
	for (int i = 0; i < Chi_button_count_look; i++) {
		fscanf_s(file, "%d,", &look_button[i].x);
		fscanf_s(file, "%d,", &look_button[i].y);
		fscanf_s(file, "%d,", &look_button[i].width);    //��ť�Ĵ�С(���ڼ�ذ�ť����¼�)
		fscanf_s(file, "%d,", &look_button[i].height);
		debug(look_button[i].x, look_button[i].y);
		debug(look_button[i].width, look_button[i].height);
	}
	//////////////////////////////////////////
	fclose(file);    //�������Ǽ��Ϲر��ļ�����ȡ��
	return;
}

/*�������ѵ�ͼƬ*/
void Load_reminder_img()
{
	loadimage(&reminder[0], _T("./res/reminder/reminder.png"));
	loadimage(&reminder[1], _T("./res/reminder/reminder_mask.png"));
}

/*����������Ϣ*/
void Load_chess_board_img(IMAGE* chess_board_img)
{
	loadimage(chess_board_img, _T("./res/Chess_board_img.png"));
	return;
}

/*���뻶ӭ���水ťͼ��*/
void Load_welcome_button(Chi_button_imfo* button)
{
	//����ͼ
	loadimage(&((button + 0)->img[0]), _T("./res/button/welcome/1_m.png"));
	loadimage(&((button + 1)->img[0]), _T("./res/button/welcome/2_m.png"));
	loadimage(&((button + 2)->img[0]), _T("./res/button/welcome/3_m.png"));
	//��ͼ
	loadimage(&((button + 0)->img[1]), _T("./res/button/welcome/1.png"));
	loadimage(&((button + 1)->img[1]), _T("./res/button/welcome/2.png"));
	loadimage(&((button + 2)->img[1]), _T("./res/button/welcome/3.png"));
	return;
}

/*�������߰�ťͼ��*/
void Load_online_button_img(Chi_button_imfo* button)
{
	//����ͼ
	loadimage(&((button + 0)->img[0]), _T("./res/button/online/1_m.png"));
	loadimage(&((button + 1)->img[0]), _T("./res/button/online/2_m.png"));
	loadimage(&((button + 2)->img[0]), _T("./res/button/online/3_m.png"));
	loadimage(&((button + 3)->img[0]), _T("./res/button/online/4_m.png"));
	loadimage(&((button + 4)->img[0]), _T("./res/button/online/5_m.png"));
	//��ͼ
	loadimage(&((button + 0)->img[1]), _T("./res/button/online/1.png"));
	loadimage(&((button + 1)->img[1]), _T("./res/button/online/2.png"));
	loadimage(&((button + 2)->img[1]), _T("./res/button/online/3.png"));
	loadimage(&((button + 3)->img[1]), _T("./res/button/online/4.png"));
	loadimage(&((button + 4)->img[1]), _T("./res/button/online/5.png"));
	return;
}

/*����ؿ����水ťͼ��*/
void Load_Look_back_button(Chi_button_imfo* button)
{
	//����ͼ
	loadimage(&((button + 0)->img[0]), _T("./res/button/look_back/1_m.png"));
	loadimage(&((button + 1)->img[0]), _T("./res/button/look_back/2_m.png"));
	loadimage(&((button + 2)->img[0]), _T("./res/button/look_back/3_m.png"));
	//��ͼ
	loadimage(&((button + 0)->img[1]), _T("./res/button/look_back/1.png"));
	loadimage(&((button + 1)->img[1]), _T("./res/button/look_back/2.png"));
	loadimage(&((button + 2)->img[1]), _T("./res/button/look_back/3.png"));
	return;
}

/*���밴ťͼ��*/
void Load_buuton_img(Chi_button_imfo* button)
{

	//��ͼ
	loadimage(&((button + 0)->img[1]), _T("./res/button/1.png"));
	loadimage(&((button + 1)->img[1]), _T("./res/button/2.png"));
	loadimage(&((button + 2)->img[1]), _T("./res/button/3.png"));
	loadimage(&((button + 3)->img[1]), _T("./res/button/4.png"));
	loadimage(&((button + 4)->img[1]), _T("./res/button/5.png"));
	return;
}

/*��תͼ��*/
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

/*��������ͼ��*/
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
	loadimage(Chess_mask, _T("./res/chess/chess_mask.png"));    //����ͼ
	return;
}

/*��ȡ�浵*/
/*                  *�浵��           ����        *����  */
void Read_doc(char* file_name, int Chess_board[][9], int* whoisturn, int* hostman)
{
	FILE* file;
	fopen_s(&file, file_name, "r");
	if (file == NULL)return;          //���ļ�����
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			fscanf_s(file, "%d", &Chess_board[i][j]);
		}
	}
	fscanf_s(file, "%d", whoisturn);    //��ȡ��˭�Ļغ�
	*hostman = *whoisturn;
	fclose(file);
	return;
}

/*����浵*/
/*                  *�浵��           ����        ����  */
void Save_doc(char* file_name, int Chess_board[][9], int whoisturn)
{
	FILE* file;
	fopen_s(&file, file_name, "w+");
	if (file == NULL)return;          //���ļ�����
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			fprintf_s(file, "%d ", Chess_board[i][j]);
		}
		fprintf_s(file, "\n");
	}
	fprintf_s(file, "%d\n", whoisturn);    //��¼��˭�ľ�
	fclose(file);    //�ر��ļ����ܱ���
	return;
}

/*��Ϸ�����󱣴�����·��*/
void Save_chess_mark()
{
	FILE* file;
	fopen_s(&file,"history_comp.txt", "a+");    //�ٽ��д�洢
	if (file == NULL)return;          //���ļ�����
	if (Chess_move_head == NULL)return;    //���û��������Ϣ��Ps:���������⣬��ô�����أ�
	Chess_move_imfo* temp = Chess_move_head;
	int step_count = 0;
	while (temp != NULL)   //�Ȼ�ȡ����Ŀ
	{
		temp = temp->down;
		step_count++;
	}
	temp = Chess_move_head;    //�ֻص����
	fprintf_s(file ,"@%d", step_count);    //�������
	for (int i = 0; i < step_count; i++,temp = temp->down) {
		fprintf_s(file, "+%d-%d-%d,%d-%d-%d", temp->move_who_x, temp->move_who_y , temp->move_who_id, temp->ate_who_x , temp->ate_who_y, temp->ate_who_id);    //д����λ����
	}
	fprintf_s(file, "\n");
	fclose(file);    //�ر��ļ�
	//--------------��ȡʱ�������Դ:https://zhidao.baidu.com/question/558299804.html
	fopen_s(&file, "history_comp_concise.txt", "a+");    //�ٽ��м�Ҫ��Ϣ�洢
	if (file == NULL)return;
	time_t time_imfo;
	struct tm p;    //ʱ����Ϣָ��
	time(&time_imfo);    //��ȡʱ����Ϣ
	gmtime_s(&p, &time_imfo);    //��ʽ��ʱ����Ϣ���ṹ����
	if (To_id[4] == 0) fprintf_s(file, "@(%s)(%s)(%d-%d-%d)\n", "NONE!", "NONE!", 1900 + p.tm_year, 1 + p.tm_mon, p.tm_mday);   //�ж�����ģʽ�ļ�¼�洢
	else fprintf_s(file, "@(%s)(%s)(%d-%d-%d)\n", My_id, To_id, 1900+p.tm_year,1+p.tm_mon,p.tm_mday );    //�ҵ����ƣ��������ƣ�ʱ��(  ��(��1900��ʼ), ��(��0��ʼ), ��(����))
	fclose(file);   //�ر��ļ�
	return;
}

/*��ȡchess_mark
Ĭ�϶�ȡ��һ�ε�����*/
void Read_chess_mark(int index)
{
	FILE* file;
	fopen_s(&file, "history_comp.txt", "r");    //�ٽ��д�洢
	if (file == NULL)return;    //���ļ�
	Clear_link_node(&Chess_move_head, &Chess_move_tail);    //������нڵ�
	char ch;
	int mark_flag = 0;
	for (int i = 0;; i++) {
		char flag;
		fscanf_s(file, "%c", &flag, 1);
		if (flag == '@')++mark_flag;    //��ȡ��index��ʱ�����ͣ�ļ���ȡ
		if (mark_flag == index)break;
	}
	int step_count;
	fscanf_s(file, "%d", &step_count);    //��ȡ�������������ڵ�ļ���
	debug(step_count, mark_flag);
	for (int i = 0; i < step_count; i++) {
		int mov_x, mov_y,mov_id, eat_x, eat_y,eat_id;
		fscanf_s(file, "+%d-%d-%d,%d-%d-%d",&mov_x, &mov_y,&mov_id, &eat_x, &eat_y, &eat_id);
		printf("+%d-%d,%d-%d\n", mov_x, mov_y, eat_x, eat_y);
		Push_link_node(&Chess_move_head, &Chess_move_tail, mov_x, mov_y, eat_x, eat_y,mov_id, eat_id);    //���ӽڵ�	
	}
	fclose(file);    //�ر��ļ�
	Chess_move_pointer = Chess_move_head;    //��ָ��ָ��ͷ�ڵ�
	return;
}

/*��ȡ�ؿ���¼�����ֵ*/
int Get_look_mark_max()
{
	int Look_mark_max = 0;     //��ʼ��һ����־λ
	FILE* file;
	fopen_s(&file, "history_comp_concise.txt", "r");    //��ȡ�ļ�
	if (file == NULL)return 0;
	char ch;
	while (fscanf_s(file, "%c", &ch, 1)!=EOF)
	{
		if (ch == '@')Look_mark_max++;    //��ȡ���ļ���־λ������Ϊ��ʽ������Ϣ��
	}
	fclose(file);
	return Look_mark_max;
}