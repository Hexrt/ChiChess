#pragma once
#include "my_define.h"
#include "data_structure.h"

/*�������*/
char rules() {
	if (Chess_board[cur_click.y][cur_click.x] <= 7 && Chess_board[cur_select.y][cur_select.x] <= 7 && Chess_board[cur_select.y][cur_select.x] > 0)return 0;    //�Լ�����������ѡ��ĵط�(�Ϸ�)
	if (Chess_board[cur_click.y][cur_click.x] >= 8 && Chess_board[cur_select.y][cur_select.x] >= 8)return 0;    //ͬ��(�·�)
	//����˧-----------------------------------------------------------------------------------------------------------------------
	if (Chess_board[cur_click.y][cur_click.x] == 1 || Chess_board[cur_click.y][cur_click.x] == 8)
	{    //����˧
		if ((Chess_board[cur_click.y][cur_click.x] == 1 && Chess_board[cur_select.y][cur_select.x] == 8) || (Chess_board[cur_click.y][cur_click.x] == 8 && Chess_board[cur_select.y][cur_select.x] == 1)) {    //ֱ�ӷ�ɱ
			if ((cur_click.x == cur_select.x)) {
				for (int i = min(cur_select.y, cur_click.y) + 1; i < max(cur_select.y, cur_click.y); i++) {
					if (Chess_board[i][cur_click.x]) return 0;
				}
			}
			return 1;
		}
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 1)return 0;    //ֻ��ֱ����һ��
		if ((cur_select.x > 5 || cur_select.x < 3 || cur_select.y > 2) && Chess_board[cur_click.y][cur_click.x] == 8)return 0;    //�����ϾŹ���
		if ((cur_select.x > 5 || cur_select.x < 3 || cur_select.y < 7) && Chess_board[cur_click.y][cur_click.x] == 1)return 0;    //�����¾Ź���
		return 1;
	}

	//ʿ,ʿ------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 2 || Chess_board[cur_click.y][cur_click.x] == 9)
	{    //ʿ,ʿ
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 2)return 0;    //ֻ����б��
		if ((cur_select.x > 5 || cur_select.x < 3 || cur_select.y > 2) && Chess_board[cur_click.y][cur_click.x] == 9)return 0;    //�����ϾŹ���
		if ((cur_select.x > 5 || cur_select.x < 3 || cur_select.y < 7) && Chess_board[cur_click.y][cur_click.x] == 2)return 0;    //�����¾Ź���
		return 1;
	}

	//��,��------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 3 || Chess_board[cur_click.y][cur_click.x] == 10)
	{    //��,��
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 8)return 0;    //ֻ��б������
		if (cur_select.y > 4 && Chess_board[cur_click.y][cur_click.x] == 10)return 0;    //�����Ϸ�����
		if (cur_select.y < 4 && Chess_board[cur_click.y][cur_click.x] == 3)return 0;    //�����·�����
		if (Chess_board[(cur_select.y + cur_click.y) / 2][(cur_select.x + cur_click.x) / 2])return 0;    //������
		return 1;
	}

	//�R,��------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 4 || Chess_board[cur_click.y][cur_click.x] == 11)
	{    //�R,��
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 5)return 0;    //ֻ����ri
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) == 1 && Chess_board[cur_click.y][(cur_select.x + cur_click.x) / 2])return 0;    //��������ſ���
		if ((cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) == 1 && Chess_board[(cur_select.y + cur_click.y) / 2][cur_click.x])return 0;    //���������
		return 1;
	}

	//܇,��------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 5 || Chess_board[cur_click.y][cur_click.x] == 12)
	{    //܇,��
		if (cur_select.y != cur_click.y && cur_select.x != cur_click.x)return 0;    //ֻ����ֱ��
		if (cur_select.y == cur_click.y) {
			for (int i = min(cur_select.x, cur_click.x) + 1; i < max(cur_select.x, cur_click.x); i++) {    //���ܸ�ɽ��ţ�����Է�Ծ
				if (Chess_board[cur_select.y][i])return 0;
			}
		}
		else {
			for (int i = min(cur_select.y, cur_click.y) + 1; i < max(cur_select.y, cur_click.y); i++) {
				if (Chess_board[i][cur_select.x])return 0;
			}
		}
		return 1;
	}

	//��,��------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 6 || Chess_board[cur_click.y][cur_click.x] == 13)
	{    //��,��
		if (cur_select.y != cur_click.y && cur_select.x != cur_click.x)return 0;    //ֻ����ֱ��
		int countt = 0;
		if (cur_select.y == cur_click.y) {
			for (int i = min(cur_select.x, cur_click.x) + 1, j = 0; i < max(cur_select.x, cur_click.x); i++) {    //���Ը�ɽ��ţ���ͷ�Ծ
				if (Chess_board[cur_select.y][i]) countt++;
			}
			if (countt >= 2)return 0;    //�����������ϣ����ܰ��ϸ�
			else if (countt == 1 && Chess_board[cur_select.y][cur_select.x] == 0) return 0;    //�����װ��ǣ����ܰ�
			else if (countt == 0 && Chess_board[cur_select.y][cur_select.x]) return 0;    //û�м��ڣ����ܴ�
			return 1;
		}
		else {
			for (int i = min(cur_select.y, cur_click.y) + 1; i < max(cur_select.y, cur_click.y); i++) {
				if (Chess_board[i][cur_select.x]) countt++;
			}
			if (countt >= 2)return 0;    //�����������ϣ����ܰ��ϸ�
			else if (countt == 1 && Chess_board[cur_select.y][cur_select.x] == 0) return 0;    //�����װ��ǣ����ܰ�
			else if (countt == 0 && Chess_board[cur_select.y][cur_select.x]) return 0;    //û�м��ڣ����ܴ�
			return 1;
		}
	}

	//��,��------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 7 || Chess_board[cur_click.y][cur_click.x] == 14)
	{    //��,��
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 1)return 0;    //ֻ��ֱ����һ��
		if (Chess_board[cur_click.y][cur_click.x] == 7) {
			if (cur_select.y > cur_click.y)return 0;    //�ñ�����ͷ
			if (cur_select.y == cur_click.y && cur_select.y >= 5)return 0;    //δ�����Ų�ת��
		}
		if (Chess_board[cur_click.y][cur_click.x] == 14) {
			if (cur_select.y < cur_click.y)return 0;    //���䲻��ͷ
			if (cur_select.y == cur_click.y && cur_select.y <= 4)return 0;   //δ�����Ų�ת��
		}
		return 1;
	}
	return 0;
}

//------------------------------------------
//           ���������жϣ�δ��ɣ�
//------------------------------------------

/*������⣡*/
int checkmate()
{
	int general_position_x, general_position_y;
	//��ɫ������ɫ
	for (int i = 0; i <= 2; i++) {                   //�ҽ�������
		for (int j = 3; j <= 5; j++) {
			if (Chess_board[i][j] == 8) {
				general_position_x = j;
				general_position_y = i;
				break;
			}
		}
	}

	//��ɫ������ɫ
	return 0;
}

/*������*/
int die_chess()
{
	return 0;
}