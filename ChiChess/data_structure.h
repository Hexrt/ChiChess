#pragma once
#include <graphics.h>
#include <time.h>
#include "my_define.h"
/*��ʹ�õ����ݽṹ*/


//��¼���ѡ���λ��
typedef struct _Select {
	int x;    //��������
	int y;    //��������
}Chi_Select;

//��ť����Ϣ
typedef struct _Chi_button_imfo {
	int x;    //��������
	int y;
	int width;    //��ť���
	int height;
	char src[20];
	IMAGE img[2];    //��ťͼ��
}Chi_button_imfo;

//������Ϣ
typedef struct _Chess_move_imfo {
	int move_who_x;    //���巽����x
	int move_who_y;    //----------y
	int move_who_id;   //���巽����id
	int ate_who_x;    //���������x
	int ate_who_y;
	int ate_who_id;   //����id(0Ϊ����)
	_Chess_move_imfo* up;    //����ָ����
	_Chess_move_imfo* down;    //����ָ����
}Chess_move_imfo;


//����ʱʱ����Ϣ
typedef struct _Time_clock_imfo {
	clock_t start;
	clock_t end;
	int rememder;
	TCHAR text_rememder[4];
}Time_clock_imfo;


/*�����ǹ滮���̵���Ϣ*/
/*���̰���my_define.h�е�Chi_square����Ϊ��λ����*/
//Ĭ�ϲ���
/*
		  -----------X
		  |
		  |
		  |
		  |
		  Y                  */

		  //Ĭ�����ӵĵ����ӳ��
		  /*
		  i--------------------------i
		  |��  ʿ  ��  �R  ܇  ��  ��|
		  |8   9   10  11  12  13  14|
		  |--------------------------|
		  |1   2   3   4   5   6   7 |
		  |˧  ʿ  ��  �R  ܇  ��  ��|
		  i--------------------------i
		  */


int Chess_board[10][9];    //��¼���̵���Ϣ10*9 (�ܹ�����λ�õĵط�)
//---------------------------------------------------
Chi_button_imfo Chi_button[6];    //��ť��Ϣ
Chi_button_imfo Online_button[6];   //����ҳ�水ťͼ
Chi_button_imfo Welcome_button[4];   ///��ӭҳ�水ť��Ϣ
Chi_button_imfo Look_back_button[4];   ///�ؿ�ҳ�水ť��Ϣ
Chess_move_imfo* Chess_move_head;    //˫�����������������Ϣ--ͷ��
Chess_move_imfo* Chess_move_tail;    //˫�������--β��
Chess_move_imfo* Chess_move_pointer; //�ؿ�ϵͳר�õ�ָ��(Ĭ��ָ��ͷ�ڵ�)
//--------------------------------------------------
IMAGE Chess_board_img;    //���̱���ͼ
IMAGE Chess_img[15];    //����ͼ����Ϣ(��1��ʼ)
IMAGE Chess_mask;    //��������ͼ
IMAGE reminder[2];   //���������ͼ��
//--------------------------------------------------
int Game_modle;    //��Ϸģʽ��1������,2,���ߣ�3�ؿ�
int whoisturn;	//˭�ľ���1�췽��0�ڷ�
int hostman;    //������˭�ٿ�
int Online_date_new;    //���ڲٿ�Contorl������жϣ�1Ϊ�����ݿ����ƶ��ˣ�0Ϊ����ȴ�
int Online_requre;      //�������߶�ս�Ĳٿأ�1Ϊͬ�⣬0Ϊ�ܾ�
int Regret_requre;      //���ڻ���Ĳٿأ�1Ϊͬ�⣬0Ϊ�ܾ�
//--------------------------------------------------
Chi_Select cur_click;    //�����λ��
Chi_Select cur_select;    //���ѡ��λ��(��cur_click֮��)
Chi_Select cur_click_ol;    //�����λ�ã�����ģʽר�ã�
Chi_Select cur_select_ol;    //���ѡ��λ��(����ģʽר��)
//--------------------------------------------------
int button_select_id;    //��ť�������ID
Time_clock_imfo   Timer;//ʱ����Ϣ
//--------------------------------------------------
char To_id[7];    //��Ҫ���͸������ID
char My_id[7];    //����ID
char Low_date[20];    //�����ݣ����ڶ̱��ĵķ���ͨ��ֻ�ı�ǰ��һ��ֵ
char Date[100];       //�����ݣ����ڽ��ܷ������������ı���
const char Net_ok[] = "OK!";    //ǰ������ű��ĵĳɹ���־λ

