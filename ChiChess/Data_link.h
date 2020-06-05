#pragma once
#include "data_structure.h"

/*专门用来记录走棋信息
采用双向链表，并且采用栈这个数据结构来描述走棋的先后顺序，
链表类型为不带头节点的双向链表
便于悔棋操作*/

/*New一个新的节点*/
Chess_move_imfo* New_link_node()
{
	Chess_move_imfo* new_link_node = (Chess_move_imfo*)malloc(sizeof(Chess_move_imfo));
	return new_link_node;
}

/*输出链表Debug专用 !Debug*/
void Print_link(Chess_move_imfo* Chess_move_head)
{
	if (Chess_move_head == NULL)return;
	Chess_move_imfo* temp = Chess_move_head;
	while (temp != NULL)
	{
		printf("%d <-eat-> %d\n", temp->move_who_id, temp->ate_who_id);
		temp = temp->down;
	}
	return;
}

/*按要求填满节点信息*/
void Fill_node_date(Chess_move_imfo* new_link_node, int cli_x, int cli_y, int sel_x, int sel_y,int mov_id, int eat_id)
{
	new_link_node->up = new_link_node->down = NULL;    //设置节点的前导和后导指针域为空
	new_link_node->move_who_id = Chess_board[cli_y][cli_x];     //填充移动方的信息
	if (Game_modle == 3)new_link_node->move_who_id = mov_id;    //对回看模式的数据
	new_link_node->move_who_x = cli_x;
	new_link_node->move_who_y = cli_y;
	new_link_node->ate_who_id = Chess_board[sel_y][sel_x];    //填充被吃方的信息
	if (Game_modle == 3)new_link_node->ate_who_id = eat_id;
	new_link_node->ate_who_x = sel_x;
	new_link_node->ate_who_y = sel_y;
	printf("%d%d---\n", new_link_node->move_who_id, new_link_node->ate_who_id);
	return;
}

/*新增栈节点*/
void Push_link_node(Chess_move_imfo** Chess_move_head, Chess_move_imfo** Chess_move_tail, int cli_x, int cli_y, int sel_x, int sel_y, int mov_id, int eat_id)
{
	Chess_move_imfo* new_link_node = New_link_node();    //获取到一个新节点的地址
	Fill_node_date(new_link_node, cli_x, cli_y, sel_x,  sel_y, mov_id, eat_id);                       //填满数据
	//printf("%d%d%d%d----\n",  cli_x, cli_y, sel_x, sel_y);
	if (*Chess_move_head == NULL)    //空头节点的情况
	{
		*Chess_move_head = new_link_node;
		*Chess_move_tail = new_link_node;
	}
	else {                          //非空节点的情况
		(*Chess_move_tail)->down = new_link_node;
		new_link_node->up = *Chess_move_tail;
		*Chess_move_tail = new_link_node;
	}
	Print_link(*Chess_move_head);    //打印出来（Debug时期的代码，后期删除!Debug）
	return;
}

/*从栈顶部POP一个节点*/
void Pop_link_node(Chess_move_imfo** Chess_move_head, Chess_move_imfo** Chess_move_tail)
{
	if (*Chess_move_tail == NULL)return;    //空链表
	Chess_move_imfo* temp_tail = (*Chess_move_tail)->up;
	if ((*Chess_move_tail)->up != NULL)    //防止仅剩一个节点时，违法访问
	{
		(*Chess_move_tail)->up->down = NULL;    //不然就可以进行截断链表操作
	}
	free(*Chess_move_tail);
	*Chess_move_tail = temp_tail;
	if (*Chess_move_tail == NULL)    //如果数据栈空了，就让头也为NULL
	{
		*Chess_move_head = NULL;
	}
	return;
}

/*完全清空链表信息
用于回看模块的清空功能*/
void Clear_link_node(Chess_move_imfo** Chess_move_head, Chess_move_imfo** Chess_move_tail)
{
	if (*Chess_move_head == NULL)return;
	Chess_move_imfo* temp = *Chess_move_head;    //设置临时节点指针
	while (temp != NULL)
	{
		printf("%d <-eat-> %d\n", temp->move_who_id, temp->ate_who_id);
		Chess_move_imfo* temp_2 = temp->down;    //往下走
		free(temp);    //释放内存
		temp = temp_2;    //往下走
	}
	*Chess_move_head = NULL;    //头节点置空
	*Chess_move_tail = NULL;    //设置尾节点为空
	return;
}

/*每次跟新栈顶的信息(还原回去棋盘中)*/
void Update_Chess(Chess_move_imfo* Chess_move_tail)
{
	if (Chess_move_tail == NULL)return;    //如果当前已经没有数据，返回
	Chess_move_imfo* temp = Chess_move_tail;
	Chess_board[temp->move_who_y][temp->move_who_x] = temp->move_who_id;    //逆向更新移动的一方
	Chess_board[temp->ate_who_y][temp->ate_who_x] = temp->ate_who_id;    //逆向更新被吃掉的一方
}

/*悔棋链表操作
规定，自己悔棋放hostman，别人悔棋放!hostman
@parama[hostman] 为悔棋方的编号*/
void Link_regret(Chess_move_imfo** Chess_move_head, Chess_move_imfo** Chess_move_tail, int who_regret)
{
	if (*Chess_move_head == NULL)return;
	Chess_move_imfo* temp = *Chess_move_tail;
	who_regret = (hostman==1) ? who_regret : !who_regret;    //进行反转
	if (who_regret == 1)    //如果当前操作是红方
	{
		if (temp->move_who_id >= 8 && Game_modle == 1)    //如果发现棋子是黑方棋子走棋(在线模式才能悔棋两次)
			//（操作情景是，黑方已经落棋，红方悔棋，需要删除两次，更新两次，才能完成悔棋操作）
		{
			Update_Chess(*Chess_move_tail);                      //更新信息
			Pop_link_node(Chess_move_head, Chess_move_tail);     //删除节点
			Update_Chess(*Chess_move_tail);                      //更新信息
			Pop_link_node(Chess_move_head, Chess_move_tail);     //删除节点
		}
		else
			//否则，仅需删除一次
		{
			Update_Chess(*Chess_move_tail);
			Pop_link_node(Chess_move_head, Chess_move_tail);
		}
	}
	else
	{
		if (temp->move_who_id <= 7 && Game_modle == 1)
			//（操作情景是，红方方已经落棋，黑方悔棋，需要删除两次，更新两次，才能完成悔棋操作）
		{
			Update_Chess(*Chess_move_tail);
			Pop_link_node(Chess_move_head, Chess_move_tail);
			Update_Chess(*Chess_move_tail);
			Pop_link_node(Chess_move_head, Chess_move_tail);
		}
		else
			//否则，仅需删除一次
		{
			Update_Chess(*Chess_move_tail);
			Pop_link_node(Chess_move_head, Chess_move_tail);
		}
	}
	//Print_link(*Chess_move_head);    //Debug专用!Debug
	return;
}
