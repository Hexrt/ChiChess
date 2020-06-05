#pragma once
/*��������Ҫ���½����ͼ�β�����*/
#include <graphics.h>
#include "my_define.h"
#include "data_structure.h"
#include "file_action.h"
#include "timer.h"
#pragma comment(lib,"Winmm.lib")

//��ȡ������Ϣ
void Get_character()
{
	whoisturn = 1;
	hostman = 1;
	return;
}

/*���û�ӭ����İ�ťͼƬ*/
void Put_welcome_img(int Welcome_button_count, Chi_button_imfo* button)
{
	for (int i = 0; i < Welcome_button_count; i++) {
		putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
	}
	return;
}

/*��������ҳ��İ�ťͼƬ*/
void Put_online_button(int Online_button_count, Chi_button_imfo* button)
{
	for (int i = 0; i < Online_button_count; i++) {
		putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
	}
	return;
}


/*���ûؿ�ҳ�水ťͼƬ*/
void Put_look_back_button_img(int Chi_button_count, Chi_button_imfo* button)
{
	for (int i = 0; i < Chi_button_count; i++) {
		putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
	}
	return;
}


/*���ð�ťͼƬ*/
void Put_button_img(int Chi_button_count, Chi_button_imfo* button)
{
	if (Game_modle == 3)    //�ؿ�ģʽ��ͼƬ��ͬ
	{
		for (int i = 3; i <= 4; i++) {
			putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
		}
	}
	else {    //���ߺ�����ģʽ
		for (int i = 0; i < Chi_button_count; i++) {
			if (Game_modle != 2 && i == 0)continue;    //����ģʽ���ܴ浵
			putimage((button + i)->x, (button + i)->y, &((button + i)->img[1]));
		}
	}
	return;
}

/*��������ҳ��ͼƬ*/
void Put_online_page_img()
{
	IMAGE temp;
	loadimage(&temp, _T("./res/Online_page.png"));
	putimage(0, 0, &temp);
}

/*��������ͼƬ*/
void Put_chess_img(IMAGE Chess_img[],IMAGE Chess_mask,int Chess_board[][9])
{
	/*������*/
	for (int i = 0; i < 9; i++) {    //��,x
		for (int j = 0; j < 10; j++) {    //��,y
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

/*�������������*/
void Play_reminder()
{
	mciSendString(_T("close movemus"), NULL, 0, NULL);//�رն�ý�������ļ�
	mciSendString(_T("open E:\\res\\down.mp3 alias movemus"), NULL, 0, NULL);    //
	mciSendString(_T("play movemus"), NULL, 0, NULL);    //����
	return;
}

/*�������ѱ�ǩ*/
void Put_reminder()
{
	if ((hostman == whoisturn && Game_modle==1) || (Game_modle!=1 && hostman==1)) {
		putimage(0, 470, &reminder[1], NOTSRCERASE);
		putimage(0, 470, &reminder[0], SRCINVERT);
		//outtextxy(5, 400,_T("�ҷ���"));
	}
	else {
		putimage(0, 150, &reminder[1], NOTSRCERASE);
		putimage(0, 150, &reminder[0], SRCINVERT);
		//outtextxy(5, 100,_T("�з���"));
	}
	return;
}

/*����ʱ��*/
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
	settextstyle(26, 16, _T("������"));
	outtextxy(245, 37, LPTSTR(Timer.text_rememder));
	EndBatchDraw();
	return Calc_time();
}

/*����ҳ��*/
void Show_online_page()
{
	Sleep(10);
	BeginBatchDraw();
	outtextxy(175,55,_T("�����������İ���"));
	outtextxy(140, 74, _T("������ΪCentOS 8.0.1905"));
	outtextxy(140, 89, _T("ʹ�õ�ʱ�������չ���ʹ��"));
	outtextxy(140, 104, _T("��ֹ����������Ӧ(�˵�Ū����)"));
	outtextxy(140, 125, _T("1.���ȵ��ע��ID��5λ����"));
	outtextxy(140, 145, _T("2.��ѯ������ң������б�"));
	outtextxy(140, 165, _T("3.ѡ��������һ��ߵȴ�������"));
	outtextxy(140, 185, _T("4.�����ӶԷ���ҳɹ��Զ�����"));
	outtextxy(140, 205, _T("5.ͬ��Է��󣬵��������ֿ�ʼ"));
	setcolor(RED);
	outtextxy(130, 225, _T("�����ϲ�Ҫ�����϶�����û��������"));
	setcolor(WHITE);
	Load_online_button_img(Online_button);
	Put_online_button(5,Online_button);
	EndBatchDraw();
	return;
}

/*��ӭ����*/
void Welcome_page()
{
	IMAGE temp;
	loadimage(&temp, _T("./res/Welcome.png"));
	putimage(0,0,&temp);
	Load_welcome_button(Welcome_button);
	Put_welcome_img(3,Welcome_button);
	return ;
}

/*չ����ʷ��¼*/
void Show_history(int Look_next, int Look_mark_max)
{
	FILE* file;
	fopen_s(&file, "history_comp_concise.txt", "r+");    //�򿪼����ļ�
	if (file == NULL)return;
	char ch;
	WCHAR my_Id[20], to_Id[20], The_Iime[20];
	//while (fscanf_s(file, "%c", &ch, 1) != EOF && ch != '@');
	int start = Look_next - 3; if (start <= 0)start = 1;
	int end = Look_next + 2; if (end > Look_mark_max)end = Look_mark_max;
	if (Look_mark_max >= 5 && Look_mark_max - Look_next <= 2)start = Look_mark_max - 4;
	if (start + 4 <= Look_mark_max)end = start + 4;    //����ͷ��ָ�������ߣ�����ҲҪ����5��
	if (Look_mark_max <= 5) {    //��ʱ��¼С��5����ҲҪ����5��
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
			memset(my_Id, 0, sizeof my_Id);    //��ʼ��
			memset(to_Id, 0, sizeof to_Id);    //��ʼ��
			memset(The_Iime, 0, sizeof The_Iime);    //��ʼ��
			printf("%s\n", my_id);
			for (int i = 0; i < 5; i++)my_Id[i] = my_id[i];
			for (int i = 0; i < 5; i++)to_Id[i] = to_id[i];
			for (int i = 0; i < 10; i++)The_Iime[i] = The_time[i];
			outtextxy(125,20*(i-start+1), my_Id);
			outtextxy(225, 20 * (i - start + 1), to_Id);
			outtextxy(325, 20 * (i - start + 1), The_Iime);
			if (Look_next == i)setcolor(WHITE);
		}
		/*������ָ����⣬ָ�벻�������ƶ�����ΪһЩ������ԭ�򣬶�ȡʧ�ܣ�ָ��ͣ����һ���ط�*/
	}
	EndBatchDraw();
	fclose(file);
	return;
}

/*�ؿ�����*/
void Look_back_page()
{
	cleardevice();
	Sleep(10);    //���ߣ���ֹһ��һ��
	Load_Look_back_button(Look_back_button);    //����ͼƬ
	Put_look_back_button_img(3, Look_back_button);
	//SomeCode
	return;
}

/*��ʼ������*/
void init()
{
	char s[] = "./res/docs/6666.txt";
	int temp;    //���Read_doc�ĸ���������
	Read_doc(s, Chess_board, &whoisturn, &temp);    //��ȡ�浵����ʼ���̣�
	initgraph(Chi_width, Chi_height);    //��ʼ������
	Get_button_imfo(5, Chi_button, 5, Online_button, 3, Welcome_button, 3, Look_back_button);    //��ȡ��ť��Ϣ(���� & ���� & ��ӭ���� & �ؿ�)
	Load_chess_board_img(&Chess_board_img);    //�������̱���
	Load_buuton_img(Chi_button);               //���밴ťͼƬ
	Load_chess_img(Chess_img, &Chess_mask);    //��������ͼƬ
	Load_reminder_img();                       //��������ͼƬ
	putimage(0, 0, &Chess_board_img);          //���ñ���
	Put_button_img(3, Chi_button);             //��ť
	Put_chess_img(Chess_img, Chess_mask, Chess_board); //����
	Get_character();    //��ȡ��ǰ��������һ��
	return;
}

/*ˢ����Ļ*/
void Flush_screen()
{
	Sleep(10);
	BeginBatchDraw();
	putimage(0, 0, &Chess_board_img);          //���ñ���
	Put_button_img(3, Chi_button);             //��ť
	Put_chess_img(Chess_img, Chess_mask, Chess_board); //����
	if (Game_modle!=3)Put_reminder();    //���õ�ǰΪ˭�µ����
	if (Game_modle != 3)Put_timer();
	EndBatchDraw();
	return;
}

/*չ�������б���Ϣ*/
void Show_online_list(char date[])
{
	WCHAR list_date[20];    //��ʱ��������
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