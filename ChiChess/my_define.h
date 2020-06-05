#pragma once
/**
*这是定义的部分**/
//Chi_与游戏全局全局相关,Chess_与棋子相关



#define Chi_square 50    //棋盘正方形方形格子的边长

#define Chi_width 500    //界面宽度

#define Chi_height 650    //界面长度

#define Chi_bor_left 1    //棋盘距左边距
#define Chi_bor_top 2    //棋盘距顶部边距
#define Chi_bor_button 2    //棋盘距底部边距
#define Chi_bor_right 1    //棋盘距右边边距

#define Chess_radius 20    //棋子的半径

#define debug(a, b) printf("%d-%d\n", a, b)    //Debug测试

#define pause getchar();getchar()   //这是暂停界面，不让闪退

#define Timer_loop 60

//服务器配置

#define SERVER_IP "localhost"
#define SERVER_PORT 6666
