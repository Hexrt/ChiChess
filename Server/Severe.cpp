//-std=c99 -pthread
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
#define PORT 10086
#define date_size 100

const long long int MAX_CON = 100;
using namespace std;

/*
2020年2月22日13点45分更新
采用了多线程发送，避免堵塞现象造成服务器的所有接口瘫痪
同时能够有成效的管理好计算机的资源 
*/
/*配置信息-------------------------------------------------------------------*/ 
	map<string, int>M;                     //使用map通过stringID来进行定位 
	vector<string>online_client;
	int client_all[MAX_CON];     //记录ID对应的客户端
	pthread_t threads[MAX_CON];    //线程 
	const char Net_ok[] = "OK!";
	int client_count = 1;
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serv_addr;
	typedef struct _message{
		pthread_t p;
		char date[100];
		string id;
	}message;
/*配置信息--------------------------------------------------------------------*/

void Thread_send(string, char s[]);     //多线程发送启动器 

/*获取ID*/
string get_id(char s[]){
	string ss = "";
	for (int i = 1; i < 6; i++){
		ss += s[i];
	}
	return ss;
}

//清除在线数据 
void clear_date(string to_id)
{
	int len = online_client.size();
	for (int i = 0; i < len; i++){
		if (online_client[i] == to_id){
			online_client[i] = online_client[len-1];
			online_client[len-1] = to_id;
			online_client.pop_back();
			return;
		}
	}
	return;
}

//获取列表信息 
void get_list_imfo(char date[])
{
	int index = 3;    //初始化位2 
	memset(date, 0 , date_size);    //清空数据列表 
	int online_count = online_client.size();    //获取在线人数 
	map<string, int>De_repeat;
	for (int i = 0; i < online_count; i++){   //写入数据 
		if (De_repeat[online_client[i]]){
			clear_date(online_client[i]);     //查询的时候顺便删除
			continue;
		}
		De_repeat[online_client[i]] = 1;
		for (int j = 0;online_client[i][j]; j++){
			date[index++] = online_client[i][j];    //遍历写入 
		}
	}
	online_count = online_client.size();    //获取真实在线人数 
	date[0] = '3';          
	date[1] = online_count/10 + '0';
	date[2] = online_count%10 + '0';
	return;
}

/*数据分析(接受数据)*/
int Date_analyze(char date[])
{
	if (date[0] == '1' || date[0] == '2' ||date[0] == '4'){    //直接发送OK！ 
		string to_id = get_id(date);
		write(client_all[M[to_id]], Net_ok, 4);                //OK!
		return 1;
		///
	}
	else if (date[0] == '3'){                                  //获取列表信息 
		string to_id = get_id(date);
		get_list_imfo(date);
		Thread_send(to_id, date);         //处理后转发 3+xx+xxxxxxxxx
		return 1;
		///
	}
	else if (date[0] == '5'){                                  //发送棋盘信息 
		string to_id = get_id(date);
		Thread_send(to_id, date);         //直接转发 5+
		return 1;
		///
	}
	else if (date[0] == '6'){                                  //连接对方  A -> B 
		string to_id = get_id(date);
		Thread_send(to_id, date);         //直接转发              6+对方+自己/返回编码(OK!, NO!) 
		return 1;
		///
	}
	else if (date[0] == '7'){                                //建立连接消息 B -> A 
		string to_id = get_id(date);
		Thread_send(to_id, date); 
		return 1; 
		///
	}
	else if (date[0] == '8'){                                 //悔棋信息
	 string to_id = get_id(date);
	 Thread_send(to_id, date); 
	 return 1;
	 ///
	}
	else if (date[0] == '0'){
		string to_id = get_id(date);
		//write(client_all[M[to_id]], "Close!", 7);        //关闭连接线程 Close!
		clear_date(to_id);
		return 0;
		///
	}
	
	return 1;
}


/*发送信息0失败，1成功*/
int sen(string to_id, char s[]){
	cout<<to_id<<":"<<M[to_id]<<":"<<s<<endl;
	return (write(client_all[M[to_id]], s, 100));
}


/*循环监听*/
void* thread_listen(void* arg){
	int id = client_count++;
	printf("succuss listen\n");
	while (1){
		char date[100];
		memset(date, 0, sizeof (date));    // 
		if (read(client_all[id], date, date_size )<= 0)break; 
		if (Date_analyze(date)==0)break;
	}
	close(id);
	return NULL;
}

/*多线程发送*/
void* thread_send(void* arg)
{
	message* Messa = (message*)arg;
	write(client_all[M[Messa->id]], Messa->date, date_size);
	free(Messa);   //回收内存 
	return NULL;
}

/*多线程启动*/
void Thread_send(string id, char date[])
{
	message* Messa = (message*)malloc(sizeof (_message));
	memset(Messa->date, 0, date_size);
	Messa->id = id;
	for (int i = 0; date[i]; i++){
		Messa->date[i] = date[i];
	}
	pthread_create(&threads[Messa->p], NULL, thread_send, Messa);
	return;
}

void mk_pro(){
	pthread_create(&threads[client_count], NULL, thread_listen, NULL);
}

/*0 断开连接，1 请求连接， 2请求转发数据，*/
int is_new_client(){
	struct sockaddr_in temp_addr;
	socklen_t temp_size = sizeof(temp_addr);
	//接受新的请求 
	int temp_sock = accept(serv_sock, (struct sockaddr*)&temp_addr, &temp_size ); 
	if (temp_sock == -1)return 0;    //没有请求退出 
	char c_temp[date_size];
	memset(c_temp, 0, date_size);    //初始化数据 
	read(temp_sock, c_temp, date_size);
	char type = c_temp[0];    //获取请求类型 
	if (type == '1'){
		write(temp_sock, Net_ok, 4);    //连接成功 
		string s = get_id(c_temp);    //获取ID 
		online_client.push_back(s);    //加入在线列表 
		M[s] = client_count;
		client_all[client_count] = temp_sock;    //保存 
		mk_pro();    //创建监听 
		cout<<s<<":"<<client_count<<endl;
		return 1;
	}
	return 0;
}


int main()
{
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;                     //绑定协议簇 
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 	    //绑定所有本机IP(网卡) 
	serv_addr.sin_port = htons(PORT);         //绑定端口
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	listen(serv_sock, 20);
	memset(client_all, 0, sizeof date_size);   //初始化清楚数据 
	while(1)
	{
		if (is_new_client()){
			printf("new%d\n", client_count);
		}
	}
	return 0;
}
