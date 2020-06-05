#pragma once

#include "rules.h"
#include "timer.h"
#include "Data_link.h"
#include "draw.h"
#include "net_work.h"

void  Play_zheng(int *);   //���ż�¼
void  Play_back();    //���ż�¼

/*�ж��Ǹõ�������ӵķ�Χ��
@_1 ���� _2 ���*/
char in_circle(int x_1, int y_1, int x_2, int y_2) {
	return ((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2)) <= Chess_radius * Chess_radius;
}


/*�ж��Ƿ��ڻ�ӭ���水ť������
@mous ���λ��*/
char in_welcome_button(int id, int mous_x, int mous_y) {
	return (Welcome_button[id].x < mous_x && Welcome_button[id].y < mous_y && Welcome_button[id].x + Welcome_button[id].width > mous_x && Welcome_button[id].y + Welcome_button[id].height > mous_y);
}


/*�ж��Ƿ��ڷ�����
@mous ���λ��*/
char in_button(int id, int mous_x, int mous_y) {
	return (Chi_button[id].x < mous_x && Chi_button[id].y < mous_y && Chi_button[id].x + Chi_button[id].width > mous_x&& Chi_button[id].y + Chi_button[id].height > mous_y);
}


/*�ж��Ƿ������߰�ť������
@mous ���λ��*/
char in_online_button(int id, int mous_x, int mous_y) {
	return (Online_button[id].x < mous_x && Online_button[id].y < mous_y && Online_button[id].x + Online_button[id].width > mous_x && Online_button[id].y + Online_button[id].height > mous_y);
}
/*�ж��Ƿ������߰�ť������
@mous ���λ��*/
char in_look_back_button(int id, int mous_x, int mous_y) {
	return (Look_back_button[id].x < mous_x && Look_back_button[id].y < mous_y && Look_back_button[id].x + Look_back_button[id].width > mous_x && Look_back_button[id].y + Look_back_button[id].height > mous_y);
}

/*����������λ��¼*/
void Mark_chess_move(int cli_x, int cli_y, int sel_x, int sel_y)
{
	Push_link_node(&Chess_move_head, &Chess_move_tail, cli_x,cli_y, sel_x, sel_y,0 ,0);
}

/*������Ϣ*/
void Regret_move()
{
	if (Chess_move_head == NULL)return;    //�սڵ�ͷ���
	if (Game_modle == 1) {
		whoisturn = hostman;    //(����ģʽ)����϶��Ǳ������˻��尡QAQ
	}
	else {
		whoisturn = !whoisturn;    //(����ģʽ���϶�����������ܻ��壬���Ը÷�����)
		hostman = !hostman;
	}
	Link_regret(&Chess_move_head, &Chess_move_tail, hostman);
}


/*�����
@return 0 �������Ч�¼�(��߿�)
@return 1 �������(ѡ��������)
@return 2 �����ť*/
int Click() {
	MOUSEMSG mous;
	if (MouseHit()) {    //���û������¼����˳�
		mous = GetMouseMsg();
		//��߽�
		if (!mous.mkLButton)return 0;
		if (mous.x < Chi_square * Chi_bor_left - Chess_radius || mous.x > Chi_width - Chi_square * Chi_bor_right + Chess_radius || mous.y < Chi_square * Chi_bor_top - Chess_radius || mous.y > Chi_height - Chi_square * Chi_bor_button + Chess_radius) {
			for (int i = 0; i < 3; i++) {
				if (in_button(i, mous.x, mous.y)) {
					button_select_id = i;    //�����ĸ���ť�����
					return 2;    //����˰�ť
				}
			}
			return 1;    //��Ч�¼�
		}

		//���ںӽ���
		if (mous.y < Chi_square * Chi_bor_top + Chi_square * 4 + Chi_square * Chess_radius||    //�ϵ���
			mous.y > Chi_square* Chi_bor_top + Chi_square * 5 - Chi_square * Chess_radius) {    //�µ���
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 10; j++) {
					if (in_circle(Chi_square * i + Chi_square * Chi_bor_left, Chi_square * j + Chi_square * Chi_bor_top, mous.x, mous.y)) {
						if (!Chess_board[j][i])return 0;    //���û����������Ļ���ֱ�ӷ���
						int check_turn = (hostman==whoisturn)? 1 : 0;     //��Ӧ���ж�Ҫ����
						if (Game_modle == 2)check_turn = whoisturn;    //����δ�ܼ�ʱ�����ж�����ģʽ
						if ((check_turn == 0 && Chess_board[j][i] <= 7) || (check_turn == 1 && Chess_board[j][i] >= 8)) return 0;    //ѡ�ĶԷ������ӣ�����0
						cur_click.x = i; cur_click.y = j;    //���������Ч�¼����·���
						debug(i,j);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


/*����ٴε��
@return 0 : û�е���¼�
@return 1 : �ɹ��������
@return 2 : ����������ط�*/
int Select() {
	MOUSEMSG mous;
	if (MouseHit()) {
		mous = GetMouseMsg();
		//��߽�
		if (!mous.mkLButton)return 0;
		if (mous.x < Chi_square * Chi_bor_left - Chess_radius || mous.x > Chi_width - Chi_square * Chi_bor_right + Chess_radius ||
			mous.y < Chi_square * Chi_bor_top - Chess_radius || mous.y > Chi_height - Chi_square * Chi_bor_button + Chess_radius)return 2;
		//�ӽ�
		if (mous.y < Chi_square * Chi_bor_top + Chi_square * 4 + Chi_square * Chess_radius ||    //�ϵ���
			mous.y > Chi_square* Chi_bor_top + Chi_square * 5 - Chi_square * Chess_radius) {    //�µ���
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

/*��ת����
ר�����ڴ������������������*/
void Reverse_position()
{
	cur_click_ol.x = 8 - cur_click_ol.x;
	cur_click_ol.y = 9 - cur_click_ol.y;
	cur_select_ol.x = 8 - cur_select_ol.x;
	cur_select_ol.y = 9 - cur_select_ol.y;
	return;
}


/*�ؿ�����������ģ��*/
int Look_back_page_click()
{
	MOUSEMSG mous;
	if (MouseHit()) {    //���û������¼����˳�
		mous = GetMouseMsg();
		if (mous.mkLButton)
		{
			for (int i = 0; i < 3; i++) {
				if (in_look_back_button(i, mous.x, mous.y))
				{
					button_select_id = i;    //����������ĸ���ť�����
					return 1;
				}
			}
		}
	}
	return 0;
}

/*�ؿ���ť�¼�*/
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
		Read_chess_mark(Look_next);    //��ȡ����
		return 2;
	}
	return 2;    //���󣬷�ֹ����
}

/*����ҳ�水ť�¼�
@return 0 �������Ч�¼�
@return 1 �����ť*/
int Online_button_click()
{
	MOUSEMSG mous;
	if (MouseHit()) {    //���û������¼����˳�
		mous = GetMouseMsg();
		if (!mous.mkLButton)return 0;
		for (int i = 0; i < 5; i++) {
			if (in_online_button(i, mous.x, mous.y)) {
				if(button_select_id == i)return 0;    //����������ĸ���ť�����
				button_select_id = i;
				return 1;    //����˰�ť
			}
		}
	}
	return 0;
}

/*����ҳ�水ť�¼�*/
int Online_button_down()
{
	if (button_select_id == 0) {    //���ӷ�����
		Connect_server();
		Regist();
	}
	else if (button_select_id == 1) {
		Get_online();    //��ȡ�����б�
	}
	else if (button_select_id == 2) {
		if (!Connect_player())return 1;    //����ʧ���˳�
		else {
			hostman = 1;    //�ڶ�����ť�������ˣ�������Ϊ����������hostman = 1
			return 4;    //�ɹ����ӽ�����Ϸ
		}
	}
	else if (button_select_id == 3) {
		Online_requre = 0;    //�ȴ�����ǰ������Ϊ0
		Waite_connect();
		///SomeCoe
	}
	else if (button_select_id == 4) {
		if (Online_requre == 1) {
			hostman = 0;    //��������ť�Ǳ������룬������Ϊ�ͷ�������hostman = 0
			debug(5,5);
			Ok_back(1);    //ѡ�������Ϸ�����������ˣ�˳��ͬ��ʱ�䣩
			Online_add_thread();    //������ǽ�����ظ�ͷ�ļ����������߳�
		}
		else
		{
			Game_modle = 2;    //���������ж�ֱ�ӽ�����Ϸ����������ڴ����޸�Ϊ�Ͻ���ǰ������Ϸ��
		}
		outtextxy(100, 50, _T("�˳�����ģʽ\n"));
	}
	return button_select_id;
}

/*�����߰�ť�¼������߰����¼�2,3���������¼�1��*/
void Button_down(int* who_win)
{
	//��ֹ�ظ����
	static int mark_click = -1, mark_turn = -1;
	if (mark_turn != whoisturn) {
		mark_click = -1;
		mark_turn = whoisturn;
	}
	if (mark_click == button_select_id) return;
	else mark_click = button_select_id;


	if (button_select_id == 0 && Game_modle == 2) {    //��һ����ť��ֻ�����߿���
		char modle_1[] = "./res/docs/";
		char modle_2[] = ".txt";
		char file_path[30];
		int index = 0;
		memset(file_path, 0 ,sizeof file_path);
		TCHAR s[10];    //���ڽ���InputBox�Ĳ���
		if (!InputBox(s, 10, _T("������ 5λ ����Ҫ��ȡ�Ĵ浵���ƣ�"), _T("�й�����"), _T("20200"), 0, 0, false))return;    //ͬ��
		for (int i = 0; modle_1[i]; i++)file_path[index++] = modle_1[i];
		for (int i = 0; i < 5; i++)file_path[index++] = s[i];
		for (int i = 0; modle_2[i]; i++)file_path[index++] = modle_2[i];
		Read_doc(file_path,Chess_board,&whoisturn,&hostman);     //��ȡ�ļ�
	}
	else if (button_select_id == 1) {                  //�ڶ�����ť
		if (Game_modle != 3)
		{
			char modle_1[] = "./res/docs/";
			char modle_2[] = ".txt";
			char file_path[30];
			int index = 0;
			memset(file_path, 0, sizeof file_path);
			TCHAR s[10];    //���ڽ���InputBox�Ĳ���
			if (!InputBox(s, 10, _T("������ 5λ ����Ҫ����Ĵ浵���ƣ�"), _T("�й�����"), _T("20200"), 0, 0, false))return;    //û������Ϣ�ͷ���
			for (int i = 0; modle_1[i]; i++)file_path[index++] = modle_1[i];
			for (int i = 0; i < 5; i++)file_path[index++] = s[i];
			for (int i = 0; modle_2[i]; i++)file_path[index++] = modle_2[i];
			Save_doc(file_path, Chess_board, whoisturn);    //�����ĵ�
		}
		else {
			Play_back();    //�ؿ�
		}
	}
	else if (button_select_id == 2) {                  //��������ť
		if (Game_modle == 1) 
		{    
			Regret_requre = 0;
			request_regret();    //��������
			int flag = 0;
			while (!Regret_requre && set_timer(&flag, 10)) Put_timer();    //����ʱ��; ֱ������(����ģʽ10s�ȴ�)���ü�ʱ��
			if (Regret_requre == 1) {
				Regret_move();                          //�Լ�������� 
			}
			else {
				outtextxy(100, 50, _T("�Է��ܾ����������\n"));    //��ʱ����
			}
		}
		else if (Game_modle == 2) 
		{
			Regret_move();    //����
		}
		else
		{
			Play_zheng(who_win);   //����Debug��
		}
	}
	button_select_id = -1;
	return;
}

/*������λ
@return 0 ����
@return 1 �췽ʤ��
@return 2 �ڷ�ʤ��*/
int Move(int cli_x, int cli_y, int sel_x, int sel_y)
{
	if (cli_x == sel_x && cli_y == sel_y)return 0;
	//Play_reminder();    //��������
	if (Chess_board[sel_y][sel_x] == 1 || Chess_board[sel_y][sel_x] == 8) {
		MessageBox(NULL, TEXT("�͹��Ƿ�Ҫ��������һ���㣿"), TEXT("�����ӽ�����Ŷ��"), MB_OK);   //ͼ�ε���,6yes,7no
		if (Game_modle == 1)Close_socket();    //�ر�����
		return (Chess_board[sel_y][sel_x]%8+1)%2 + 1;    //��ʤ�� (1%8+1 = 2)%2+1 = 1 ,��ʤ�� (8%8+1 = 1)%2+1 = 2
	}
	Chess_board[sel_y][sel_x] = Chess_board[cli_y][cli_x];
	Chess_board[cli_y][cli_x] = 0;
	whoisturn = !whoisturn;    //�����غ�
	if (Game_modle == 2)hostman = !hostman;    //����������ߵĻ�ҲҪ��Ӧ�ĸ���
	Online_date_new = 0;    //�����Ѿ��ù��ˣ�����Ϊ0
	return 0;
}

/*��ӭ����������ģ��*/
int Welcome_page_click()
{
	MOUSEMSG mous;
	if (MouseHit()) {    //���û������¼����˳�
		mous = GetMouseMsg();
		if (mous.mkLButton)
		{
			for (int i = 0; i < 3; i++) {
				if (in_welcome_button(i, mous.x, mous.y))
				{
					button_select_id = i;    //����������ĸ���ť�����
					return 1;
				}
			}
		}
	}
	return 0;
}

/*����-��*/
void  Play_zheng(int* whowin)
{
	*whowin = Move(Chess_move_pointer->move_who_x, Chess_move_pointer->move_who_y, Chess_move_pointer->ate_who_x, Chess_move_pointer->ate_who_y);    //ֱ���ƶ�
	if (Chess_move_pointer != NULL)Chess_move_pointer = Chess_move_pointer->down;    //�����һ����Ϊ�վ�������
	if (Chess_move_pointer == NULL)Chess_move_pointer = Chess_move_tail;    //��������ߺ�Ϊ�գ�����������ͷ
	return;
}

/*�طš�-*/
void Play_back()
{
	Move(Chess_move_pointer->move_who_x, Chess_move_pointer->move_who_y, Chess_move_pointer->ate_who_x, Chess_move_pointer->ate_who_y);    //ֱ���ƶ�
	Chess_board[Chess_move_pointer->move_who_y][Chess_move_pointer->move_who_x] = Chess_move_pointer->move_who_id;    //ֱ���������е����ݵ��ڻط�ָ�������
	Chess_board[Chess_move_pointer->ate_who_y][Chess_move_pointer->ate_who_x] = Chess_move_pointer->ate_who_id;    //ͬ��
	if (Chess_move_pointer != NULL)Chess_move_pointer = Chess_move_pointer->up;
	if (Chess_move_pointer == NULL)Chess_move_pointer = Chess_move_head;    //��������ߺ�Ϊ�գ�����������ͷ
	return;
}

/*�ؿ�ҳ����� ��һ�� ��һ�� ȷ��*/
void Look_back_page_control()
{
	Look_back_page();
	while (1) {
		while (!Look_back_page_click());    //�ȴ�����¼�
		Look_back_page();
		if (Look_back_button_down() == 2)break;    //���ѡ����ȷ�����ͷ���
	}
	//Play_zheng();
	return;
}

/*��ӭ������� ���� ���� �ؿ�*/
void Welcome_page_control()
{
	Welcome_page();
	FlushMouseMsgBuffer();    //�����껺��
	while (!Welcome_page_click());
	if (button_select_id == 0)Game_modle = 1;   //����ģʽ
	else if (button_select_id == 1)Game_modle = 2;   //����
	else Game_modle = 3;   //�ؿ�ģʽ
	return;
}

/*����ģ��*/
void Online_page_control()
{
	Put_online_page_img();
	Show_online_page();    //չʾ����ҳ��
	button_select_id = -1;
	static int Button_mark[5];
	memset(Button_mark, 0 , sizeof Button_mark);
	while (1) {
		if (Online_button_click())    //������߲���ҳ����ڰ�ť���
		{
			if (button_select_id != 0 && !Button_mark[0])continue;    //���ûע�ᣬ���ܵ�������κΰ�ť
			if (button_select_id == 0 && Button_mark[0])continue;    //����Ѿ�ע���ˣ��Ͳ�����ע��
			if (button_select_id == 4 && !Button_mark[3])continue;    //���û�еȴ����Ӳ��ܽ�����Ϸ
			Button_mark[button_select_id]++;
			if (Online_button_down() == 4) {     //��5����ť���˳�����ģʽ��ť��
				break;
			}
		}
	}
	Init_time();    //����ʱ��
	whoisturn = 1;    //������ζ��Ǻ췽������
	if (whoisturn != hostman)Reverse_img(Chess_img);    //����Ǻڷ���Ҫ���̵���
	return;
}

/*�����Ƴ���
@return 0 ����
@return 1 �췽ʤ��
@return 2 �ڷ�ʤ��*/
int control()
{
	int click_action_type = Click();
	int who_win = 0;    //��¼˭Ӯ��
	if (whoisturn == hostman && click_action_type == 1 && Game_modle != 3) {    //ֻ�е����ֲ��ܲ������ӣ��ǻؿ�ģʽ��
		char select_action_type = 0;
		while ((select_action_type = Select()) == 0) {
			if(!Put_timer())break;    //��ʱ����;    //������������¼�(�����ʱ�ˣ���ֹͣ����)
		}
		if (select_action_type == 1 && rules() && Calc_time()) {    //���Ϲ�����λ������ʱ�˳���
			Mark_chess_move(cur_click.x, cur_click.y, cur_select.x, cur_select.y);    //��¼������λ��Ϣ
			Send_move_imfo(Chess_move_tail);    //ת��������Ϣ������Ҫͨ����¼ջ�������ͣ�����ջ��¼�������棩
			Init_time();    //�����¼�
			Put_timer();    //����ʱ��
			who_win = Move(cur_click.x, cur_click.y, cur_select.x, cur_select.y);    //ֱ���ƶ�
		}
	}
	else if (click_action_type == 2) {    //����˰�ť����ͷϷ��
		Button_down(&who_win);
	}
	else if(whoisturn != hostman && Online_date_new){       //����ģʽ�ԶԷ�������λ�Ĳ���
		Reverse_position();    //�ߵ�λ�ã���Ϊ�����ڲ�ͬ����Ӫ�в�ͬ����ʾ������ͳһ���꣬�������ݣ�
		Mark_chess_move(cur_click_ol.x, cur_click_ol.y, cur_select_ol.x, cur_select_ol.y);    //��¼������λ��Ϣ
		Init_time();    //����ʱ��
		who_win = Move(cur_click_ol.x, cur_click_ol.y, cur_select_ol.x, cur_select_ol.y);
	}
	if (who_win) {      //���ʤ���Ѷ�
		if (Game_modle != 3)
		{
			char s[] = "./res/docs/1234.txt";
			Save_doc(s, Chess_board, whoisturn);    //�����ĵ�
			Save_chess_mark();    //����������Ϣ�����ڻؿ�����
			if (Game_modle == 1)Close_socket();    //�ر�����
		}
		return who_win;
	}
	if (!Calc_time()) {
		MessageBox(NULL, TEXT("�͹��Ƿ�Ҫ��������һ���㣿"), TEXT("Sorry���˳�ʱ��Ŷ��"), MB_OK);   //ͼ�ε���,6yes,7no
		Save_chess_mark();    //����������Ϣ�����ڻؿ�����
		if (Game_modle == 1)Close_socket();    //�ر�����
		return who_win = whoisturn?2:1;    //��ʱ����
	}
	return 0;
}