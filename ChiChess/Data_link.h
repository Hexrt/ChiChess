#pragma once
#include "data_structure.h"

/*ר��������¼������Ϣ
����˫���������Ҳ���ջ������ݽṹ������������Ⱥ�˳��
��������Ϊ����ͷ�ڵ��˫������
���ڻ������*/

/*Newһ���µĽڵ�*/
Chess_move_imfo* New_link_node()
{
	Chess_move_imfo* new_link_node = (Chess_move_imfo*)malloc(sizeof(Chess_move_imfo));
	return new_link_node;
}

/*�������Debugר�� !Debug*/
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

/*��Ҫ�������ڵ���Ϣ*/
void Fill_node_date(Chess_move_imfo* new_link_node, int cli_x, int cli_y, int sel_x, int sel_y,int mov_id, int eat_id)
{
	new_link_node->up = new_link_node->down = NULL;    //���ýڵ��ǰ���ͺ�ָ����Ϊ��
	new_link_node->move_who_id = Chess_board[cli_y][cli_x];     //����ƶ�������Ϣ
	if (Game_modle == 3)new_link_node->move_who_id = mov_id;    //�Իؿ�ģʽ������
	new_link_node->move_who_x = cli_x;
	new_link_node->move_who_y = cli_y;
	new_link_node->ate_who_id = Chess_board[sel_y][sel_x];    //��䱻�Է�����Ϣ
	if (Game_modle == 3)new_link_node->ate_who_id = eat_id;
	new_link_node->ate_who_x = sel_x;
	new_link_node->ate_who_y = sel_y;
	printf("%d%d---\n", new_link_node->move_who_id, new_link_node->ate_who_id);
	return;
}

/*����ջ�ڵ�*/
void Push_link_node(Chess_move_imfo** Chess_move_head, Chess_move_imfo** Chess_move_tail, int cli_x, int cli_y, int sel_x, int sel_y, int mov_id, int eat_id)
{
	Chess_move_imfo* new_link_node = New_link_node();    //��ȡ��һ���½ڵ�ĵ�ַ
	Fill_node_date(new_link_node, cli_x, cli_y, sel_x,  sel_y, mov_id, eat_id);                       //��������
	//printf("%d%d%d%d----\n",  cli_x, cli_y, sel_x, sel_y);
	if (*Chess_move_head == NULL)    //��ͷ�ڵ�����
	{
		*Chess_move_head = new_link_node;
		*Chess_move_tail = new_link_node;
	}
	else {                          //�ǿսڵ�����
		(*Chess_move_tail)->down = new_link_node;
		new_link_node->up = *Chess_move_tail;
		*Chess_move_tail = new_link_node;
	}
	Print_link(*Chess_move_head);    //��ӡ������Debugʱ�ڵĴ��룬����ɾ��!Debug��
	return;
}

/*��ջ����POPһ���ڵ�*/
void Pop_link_node(Chess_move_imfo** Chess_move_head, Chess_move_imfo** Chess_move_tail)
{
	if (*Chess_move_tail == NULL)return;    //������
	Chess_move_imfo* temp_tail = (*Chess_move_tail)->up;
	if ((*Chess_move_tail)->up != NULL)    //��ֹ��ʣһ���ڵ�ʱ��Υ������
	{
		(*Chess_move_tail)->up->down = NULL;    //��Ȼ�Ϳ��Խ��нض��������
	}
	free(*Chess_move_tail);
	*Chess_move_tail = temp_tail;
	if (*Chess_move_tail == NULL)    //�������ջ���ˣ�����ͷҲΪNULL
	{
		*Chess_move_head = NULL;
	}
	return;
}

/*��ȫ���������Ϣ
���ڻؿ�ģ�����չ���*/
void Clear_link_node(Chess_move_imfo** Chess_move_head, Chess_move_imfo** Chess_move_tail)
{
	if (*Chess_move_head == NULL)return;
	Chess_move_imfo* temp = *Chess_move_head;    //������ʱ�ڵ�ָ��
	while (temp != NULL)
	{
		printf("%d <-eat-> %d\n", temp->move_who_id, temp->ate_who_id);
		Chess_move_imfo* temp_2 = temp->down;    //������
		free(temp);    //�ͷ��ڴ�
		temp = temp_2;    //������
	}
	*Chess_move_head = NULL;    //ͷ�ڵ��ÿ�
	*Chess_move_tail = NULL;    //����β�ڵ�Ϊ��
	return;
}

/*ÿ�θ���ջ������Ϣ(��ԭ��ȥ������)*/
void Update_Chess(Chess_move_imfo* Chess_move_tail)
{
	if (Chess_move_tail == NULL)return;    //�����ǰ�Ѿ�û�����ݣ�����
	Chess_move_imfo* temp = Chess_move_tail;
	Chess_board[temp->move_who_y][temp->move_who_x] = temp->move_who_id;    //��������ƶ���һ��
	Chess_board[temp->ate_who_y][temp->ate_who_x] = temp->ate_who_id;    //������±��Ե���һ��
}

/*�����������
�涨���Լ������hostman�����˻����!hostman
@parama[hostman] Ϊ���巽�ı��*/
void Link_regret(Chess_move_imfo** Chess_move_head, Chess_move_imfo** Chess_move_tail, int who_regret)
{
	if (*Chess_move_head == NULL)return;
	Chess_move_imfo* temp = *Chess_move_tail;
	who_regret = (hostman==1) ? who_regret : !who_regret;    //���з�ת
	if (who_regret == 1)    //�����ǰ�����Ǻ췽
	{
		if (temp->move_who_id >= 8 && Game_modle == 1)    //������������Ǻڷ���������(����ģʽ���ܻ�������)
			//�������龰�ǣ��ڷ��Ѿ����壬�췽���壬��Ҫɾ�����Σ��������Σ�������ɻ��������
		{
			Update_Chess(*Chess_move_tail);                      //������Ϣ
			Pop_link_node(Chess_move_head, Chess_move_tail);     //ɾ���ڵ�
			Update_Chess(*Chess_move_tail);                      //������Ϣ
			Pop_link_node(Chess_move_head, Chess_move_tail);     //ɾ���ڵ�
		}
		else
			//���򣬽���ɾ��һ��
		{
			Update_Chess(*Chess_move_tail);
			Pop_link_node(Chess_move_head, Chess_move_tail);
		}
	}
	else
	{
		if (temp->move_who_id <= 7 && Game_modle == 1)
			//�������龰�ǣ��췽���Ѿ����壬�ڷ����壬��Ҫɾ�����Σ��������Σ�������ɻ��������
		{
			Update_Chess(*Chess_move_tail);
			Pop_link_node(Chess_move_head, Chess_move_tail);
			Update_Chess(*Chess_move_tail);
			Pop_link_node(Chess_move_head, Chess_move_tail);
		}
		else
			//���򣬽���ɾ��һ��
		{
			Update_Chess(*Chess_move_tail);
			Pop_link_node(Chess_move_head, Chess_move_tail);
		}
	}
	//Print_link(*Chess_move_head);    //Debugר��!Debug
	return;
}
