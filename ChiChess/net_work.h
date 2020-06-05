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
sockaddr_in server;    //������
HANDLE Recieve_thread; //������Ϣ���߳�
HANDLE Wait_thread;    //ר�����ڵȴ����ӵ��߳�
WSADATA data;    //����
void Ok_back(int flag);

//��ȡID
void get_id(char date[], char requre_id[]) {
	for (int i = 6, j = 0; date[i]; i++) {
		requre_id[j++] = date[i];    //��ȡID
	}
	return;
}

//�������ݷ���----------------------------------------------------
void Date_analyze(char date[])
{
	if (date[0] == '3') {    //�����б���Ϣ
		debug(3, 3);
		Show_online_list(date);    //չʾ�����б���Ϣ
		return;
	}
	else if (date[0] == '5') {    //���ӵ��ƶ���Ϣ
		cur_click_ol.x = (date[6]-'0')*10 + (date[7] - '0');
		cur_click_ol.y = (date[8] - '0') * 10 + (date[9] - '0');
		cur_select_ol.x = (date[10] - '0') * 10 + (date[11] - '0');
		cur_select_ol.y = (date[12] - '0') * 10 + (date[13] - '0');
		Online_date_new = 1;     // �������ݱ�־λΪ�µ�
	}
	else if (date[0] == '6') {    //����������Ϣ
		char requre_id[7];
		memset(requre_id, 0, sizeof requre_id);
		get_id( date, requre_id);
		WCHAR message_modle[] = _T("��������������ӣ�ȷ����");
		WCHAR message_online[20];
		memset(message_online, 0, sizeof message_online);
		int index = 0;
		for (int i = 0; i < 2; i++) {                   //���������
			message_online[index++] = message_modle[i];
		}
		for (int i = 0; requre_id[i]; i++) {
			message_online[index++] = requre_id[i];    //����ID����Ϣ��
		}
		for (int i = 2; message_modle[i]; i++) {
			message_online[index++] = message_modle[i]; //���д��
		}
		outtextxy(100, 50, LPTSTR(message_online));
		if (MessageBox(NULL, LPTSTR(message_online), TEXT("���������ע�⣡"), MB_YESNO) == IDYES) {
			Online_requre = 1;    //ͬ�����ӣ�����
			for (int i = 0; requre_id[i]; i++)To_id[i] = requre_id[i];    //������ID����Ϊ����ID
		}
		else {
			Ok_back(0);    //���Ͳ�ͬ����Ϣ
		}
	}
	else if (date[0] == '7') {    //������Ϣ(�ɹ�������Ϣ)
		for (int i = 6, j =0; j < 5; i++,j++) {
			if (date[i] != To_id[j]) {
				Online_requre = 0;
				Regret_requre = 0;    //��ͬ��
				return;
			}
		}
		Online_requre = 1;      //ͬ�����ӣ�����
		Regret_requre = 1;    //ͬ����壬����
		//Show_enter_button();
		//SomeCode���ڸ����˳�ͼƬ��������Ϸ
	}
	else if (date[0] == '8') {
		if (MessageBox(NULL, TEXT("�Է�������壡�Ƿ�ͬ���أ�QAQ"), TEXT("���������ע�⣡"), MB_YESNO) == IDYES) {
			Ok_back(1);
			whoisturn = !hostman;    //����ָ�����
			Link_regret(&Chess_move_head, &Chess_move_tail, !hostman);    //ִ�л������
		}
		else {
			Ok_back(0);    //���Ͳ�ͬ����Ϣ
		}
	}
	return;
}
//---------------------------------------------------
//---------------------------------------------------
//��ʼ��
void Net_init()
{
	memset(Low_date,0,sizeof Low_date);
	memset(Date, 0, sizeof Date);
	memset(My_id, 0, sizeof My_id);
	memset(To_id, 0, sizeof To_id);   //��ʼ��
	return;
}

//ת��
void i_to_s(int* index, char s[], int number)
{
	if (number <= 9) {    //����δ�ӵ��ڵ��´��������ݴ���
		s[(*index)++] = '0';
	}
	else {
		s[(*index)++] = '1';
	}
	s[(*index)++] = number%10 + '0';
	return;
}

//ʵʱ����
DWORD WINAPI rec(){
	while (Game_modle==1) {    //ֻ������ģʽ���ܴ��ڳ������ӣ������Ϸ�������˳�
		char date[100];
		if (recv(client, date, 100, 0) > 0) {    //���յ�����Ϣ
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

/*�ر�����*/
int Close_socket()
{
	memset(Date, 0, sizeof Date);
	for (int i = 0; i < 5; i++)Date[i + 1] = My_id[i];
	Date[0] = '0';
	send(client, Date, sizeof Date, 0);    //���͹ر�
	Game_modle = -1;    //����ģʽΪ-1
	return 1;
}

/*ע��(����)
1 + 5λID (My_id)*/
int Regist()
{
	memset(Low_date, 0, sizeof Low_date);    //��ʼ��
	memset(Date, 0, sizeof Date);    //��ʼ�����ݰ�
	memset(My_id, 0, sizeof My_id);
	TCHAR s[10];    //���ڽ���InputBox�Ĳ���
	settextcolor(RED);
	outtextxy(100, 50, _T("----�ɹ����ӷ�����----\n"));
	outtextxy(100, 50, _T("-������5λ���ID����:-\n"));
	InputBox(s, 10, _T("������ 5λ ��Ҫע���ID(Ӣ����ĸ������)��"), _T("�й�����"), _T("12345"), 0, 0, false);
	for (int i = 0; i < 5; i++)My_id[i] = s[i];    //���뵽��Ϣ��
	Low_date[0] = '1';
	for (int i = 0; My_id[i]; i++)Low_date[i + 1] = My_id[i];    //����ת������
	send(client, Low_date, sizeof Low_date, 0);    //����ע����Ϣ
	recv(client, Date, 100, 0);    //����ע��Ч��
	for (int i = 0; Net_ok[i]; i++)if (Net_ok[i] != Date[i])return 0;    //����Ƿ�ɹ�
	outtextxy(150, 50, _T("-------ע��ID�ɹ�------\n"));
	return 1;
}

/*������������
2 + 5λID (My_id)*/
int Reconect()
{
	Low_date[0] = '2';
	memset(Date, 0, sizeof Date);
	send(client, Low_date, sizeof Low_date, 0);    //����ע����Ϣ
	recv(client, Date, 100, 0);    //���ܷ�������Ϣ
	for (int i = 0; Net_ok[i]; i++)if (Net_ok[i] != Date[i])return 0;    //����Ƿ�ɹ�
	return 1;
}

/*��ȡ�����б���Ϣ��������
3 + 5λID (My_id)*/
void Get_online()
{
	memset(Date, 0, sizeof Date);
	Date[0] = '3';
	for (int i = 0; i < 5; i++)Date[i + 1] = My_id[i];
	send(client, Date, sizeof Date, 0);    //����ע����Ϣ
	memset(Date, 0, sizeof Date);
	recv(client, Date, 100, 0);    //�����б���Ϣ
	//printf("%s+++\n", Date);
	Date_analyze(Date);
	//debug(2, 2);
	//SomeCode
	return;
}

/*���Ӳ��ԣ�������
4 + 5λID (My_id)*/
int Keep_alive()
{
	memset(Date, 0, sizeof Date);
	Low_date[0] = '4';
	send(client, Low_date, sizeof Low_date, 0);    //����ע����Ϣ
	recv(client, Date, 100, 0);    //�����б���Ϣ
	for (int i = 0; Net_ok[i]; i++)if (Net_ok[i] != Date[i])return 0;    //����Ƿ�ɹ�
	return 1;
}

/*����������Ϣ��������
5 + 5λID (My_id)*/
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
	send(client, Date, sizeof Date, 0);    //������λ��Ϣ
	printf("%s", Date);
	return 1;
}

/*������ң�������
6 + 5λID + 5λID(My_id)*/
int Connect_player()
{
	outtextxy(150, 50, _T("��������Ҫ���Ӷ����ID\n"));
	TCHAR s[10];    //���ڽ���InputBox�Ĳ���
	InputBox(s, 10, _T("������ 5λ �������ӵ�ID��"), _T("�й�����"), _T("12345"), 0, 0, false);
	for (int i = 0; i < 5; i++)To_id[i] = s[i];    //���뵽��Ϣ��
	memset(Date, 0, sizeof Date);
	Date[0] = '6';
	for (int i = 0; i<5; i++)Date[i + 1] = To_id[i];    //����ת������
	for (int i = 0; i<5; i++)Date[i + 6] = My_id[i];    //����ת������
	send(client, Date, sizeof Date, 0);    //����������Ϣ
	recv(client, Date, sizeof Date, 0);    //������Ϣ
	for (int i = 6,j = 0; j < 5; i++, j++) {
		if (Date[i] != To_id[j]) {    //�����ˣ���������Խ��
			outtextxy(100, 50, _T("        ����ʧ�ܣ�  \n"));
			return 0;    //����ʧ�ܣ�������λΪ�Է�ID
		}
	}
	outtextxy(150, 50, _T("        ���ӳɹ���\n"));
	Recieve_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)rec, NULL, 0, NULL);    //��������
	CloseHandle(Recieve_thread);    //�رվ�������ǲ���ֹ�߳�
	Online_date_new = 0;
	hostman = 1;
	return 1;
}

/*
7 + 5λID + 5λID
��Ӧ������ڳɹ����ӵĶ��η���(���ݺ�6�е�����һ��)
@parama[flag] ���ڱ�־�Ƿ�ͬ������ı�־λ1ͬ�⣬0��ͬ��*/
void Ok_back(int flag)
{
	memset(Date, 0, sizeof Date);
	Date[0] = '7';
	for (int i = 0; i < 5; i++)Date[i + 1] = To_id[i];    //����ת������
	for (int i = 0; i < 5; i++)Date[i + 6] = My_id[i];    //����ת������
	if (!flag)Date[8] = '@';    //����һ�����������ڷ��ط���Ϣ
	send(client, Date, sizeof Date, 0);    //����������Ϣ
	return;
}


/*������Ϣ
8 + 5λID + 5λID(My_id)*/
void request_regret()
{
	memset(Date, 0, sizeof Date);
	for (int i = 0; i < 5; i++)Low_date[i + 1] = To_id[i];
	Low_date[0] = '8';
	send(client, Low_date, sizeof Low_date, 0);    //���ͻ�����Ϣ
	//SomeCode
	return;
}


/*���������ݽ�������ݹ��������Ľ������
* ��Contro�����ڿ�һ�������߳�*/
void Online_add_thread()
{
	Recieve_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)rec, NULL, 0, NULL);    //��������
	CloseHandle(Recieve_thread);    //�رվ�������ǲ���ֹ�߳�
	return;
}


/*�ȴ�������*/
void Waite_connect()
{
	outtextxy(100, 50, _T("���ڵȴ��������ӣ�\n"));
	Wait_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Online_waite, NULL, 0, NULL);    //��������
	CloseHandle(Wait_thread);    //�رվ�������ǲ���ֹ�߳�
	return;
}


/*��������������ӣ�������*/
int Connect_server()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSAStartup(sockVersion, &data);
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&server, 0, sizeof server);    //Clear and fill up with zero
	server.sin_family = AF_INET;                                 //Э���
	server.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);    //��IP
	server.sin_port = htons(SERVER_PORT);    //�󶨶˿�
	connect(client, (sockaddr*)&server, sizeof server);    //���ӷ�����
	Net_init();   //��ʼ��
	return 0;
}
