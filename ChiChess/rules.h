#pragma once
#include "my_define.h"
#include "data_structure.h"

/*走棋规则*/
char rules() {
	if (Chess_board[cur_click.y][cur_click.x] <= 7 && Chess_board[cur_select.y][cur_select.x] <= 7 && Chess_board[cur_select.y][cur_select.x] > 0)return 0;    //自己方的棋子在选择的地方(上方)
	if (Chess_board[cur_click.y][cur_click.x] >= 8 && Chess_board[cur_select.y][cur_select.x] >= 8)return 0;    //同上(下方)
	//将，帅-----------------------------------------------------------------------------------------------------------------------
	if (Chess_board[cur_click.y][cur_click.x] == 1 || Chess_board[cur_click.y][cur_click.x] == 8)
	{    //将，帅
		if ((Chess_board[cur_click.y][cur_click.x] == 1 && Chess_board[cur_select.y][cur_select.x] == 8) || (Chess_board[cur_click.y][cur_click.x] == 8 && Chess_board[cur_select.y][cur_select.x] == 1)) {    //直接飞杀
			if ((cur_click.x == cur_select.x)) {
				for (int i = min(cur_select.y, cur_click.y) + 1; i < max(cur_select.y, cur_click.y); i++) {
					if (Chess_board[i][cur_click.x]) return 0;
				}
			}
			return 1;
		}
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 1)return 0;    //只能直的走一个
		if ((cur_select.x > 5 || cur_select.x < 3 || cur_select.y > 2) && Chess_board[cur_click.y][cur_click.x] == 8)return 0;    //限制上九宫格
		if ((cur_select.x > 5 || cur_select.x < 3 || cur_select.y < 7) && Chess_board[cur_click.y][cur_click.x] == 1)return 0;    //限制下九宫格
		return 1;
	}

	//士,士------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 2 || Chess_board[cur_click.y][cur_click.x] == 9)
	{    //士,士
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 2)return 0;    //只能走斜线
		if ((cur_select.x > 5 || cur_select.x < 3 || cur_select.y > 2) && Chess_board[cur_click.y][cur_click.x] == 9)return 0;    //限制上九宫格
		if ((cur_select.x > 5 || cur_select.x < 3 || cur_select.y < 7) && Chess_board[cur_click.y][cur_click.x] == 2)return 0;    //限制下九宫格
		return 1;
	}

	//相,象------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 3 || Chess_board[cur_click.y][cur_click.x] == 10)
	{    //相,象
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 8)return 0;    //只能斜走两格
		if (cur_select.y > 4 && Chess_board[cur_click.y][cur_click.x] == 10)return 0;    //限制上方地盘
		if (cur_select.y < 4 && Chess_board[cur_click.y][cur_click.x] == 3)return 0;    //限制下方地盘
		if (Chess_board[(cur_select.y + cur_click.y) / 2][(cur_select.x + cur_click.x) / 2])return 0;    //堵象眼
		return 1;
	}

	//馬,马------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 4 || Chess_board[cur_click.y][cur_click.x] == 11)
	{    //馬,马
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 5)return 0;    //只能走ri
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) == 1 && Chess_board[cur_click.y][(cur_select.x + cur_click.x) / 2])return 0;    //横向蹩马脚咯！
		if ((cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) == 1 && Chess_board[(cur_select.y + cur_click.y) / 2][cur_click.x])return 0;    //纵向蹩马脚
		return 1;
	}

	//車,车------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 5 || Chess_board[cur_click.y][cur_click.x] == 12)
	{    //車,车
		if (cur_select.y != cur_click.y && cur_select.x != cur_click.x)return 0;    //只能走直线
		if (cur_select.y == cur_click.y) {
			for (int i = min(cur_select.x, cur_click.x) + 1; i < max(cur_select.x, cur_click.x); i++) {    //不能隔山打牛，可以飞跃
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

	//炮,炮------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 6 || Chess_board[cur_click.y][cur_click.x] == 13)
	{    //炮,炮
		if (cur_select.y != cur_click.y && cur_select.x != cur_click.x)return 0;    //只能走直线
		int countt = 0;
		if (cur_select.y == cur_click.y) {
			for (int i = min(cur_select.x, cur_click.x) + 1, j = 0; i < max(cur_select.x, cur_click.x); i++) {    //可以隔山打牛，和飞跃
				if (Chess_board[cur_select.y][i]) countt++;
			}
			if (countt >= 2)return 0;    //隔了两个以上，不能啊老哥
			else if (countt == 1 && Chess_board[cur_select.y][cur_select.x] == 0) return 0;    //空手套白狼，不能啊
			else if (countt == 0 && Chess_board[cur_select.y][cur_select.x]) return 0;    //没有架炮，不能打
			return 1;
		}
		else {
			for (int i = min(cur_select.y, cur_click.y) + 1; i < max(cur_select.y, cur_click.y); i++) {
				if (Chess_board[i][cur_select.x]) countt++;
			}
			if (countt >= 2)return 0;    //隔了两个以上，不能啊老哥
			else if (countt == 1 && Chess_board[cur_select.y][cur_select.x] == 0) return 0;    //空手套白狼，不能啊
			else if (countt == 0 && Chess_board[cur_select.y][cur_select.x]) return 0;    //没有架炮，不能打
			return 1;
		}
	}

	//兵,卒------------------------------------------------------------------------------------------------------------------------
	else if (Chess_board[cur_click.y][cur_click.x] == 7 || Chess_board[cur_click.y][cur_click.x] == 14)
	{    //兵,卒
		if ((cur_select.y - cur_click.y) * (cur_select.y - cur_click.y) + (cur_select.x - cur_click.x) * (cur_select.x - cur_click.x) != 1)return 0;    //只能直的走一个
		if (Chess_board[cur_click.y][cur_click.x] == 7) {
			if (cur_select.y > cur_click.y)return 0;    //好兵不回头
			if (cur_select.y == cur_click.y && cur_select.y >= 5)return 0;    //未出家门不转弯
		}
		if (Chess_board[cur_click.y][cur_click.x] == 14) {
			if (cur_select.y < cur_click.y)return 0;    //好卒不回头
			if (cur_select.y == cur_click.y && cur_select.y <= 4)return 0;   //未出家门不转弯
		}
		return 1;
	}
	return 0;
}

//------------------------------------------
//           象棋的棋局判断（未完成）
//------------------------------------------

/*将军检测！*/
int checkmate()
{
	int general_position_x, general_position_y;
	//红色将军黑色
	for (int i = 0; i <= 2; i++) {                   //找将在哪里
		for (int j = 3; j <= 5; j++) {
			if (Chess_board[i][j] == 8) {
				general_position_x = j;
				general_position_y = i;
				break;
			}
		}
	}

	//黑色将军红色
	return 0;
}

/*死棋检测*/
int die_chess()
{
	return 0;
}