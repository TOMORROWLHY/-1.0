#pragma once
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include<stdio.h>
#include<time.h>

/*游戏逻辑模块*/

//方块结构体
typedef struct
{
	int x;
	int y;      // 坐标
	int shape;  //形态
	int status; //状态
	int color;  //颜色
}BLOCK;

//1.绘制游戏池边框
void windowPrint(int x, int y);

//2.游戏初始化
void gameInit();

//3.打印操作说明
void printInfo(int n);

//4.打印分数和等级
void printGradeLevel(int num);

//5.游戏计时功能
void gameTime(clock_t start_time);

//6.打印左边框
void borderLeft();

//7.1播放音乐
void playMusic(int mode, wchar_t* filename);

//7.2停止音乐
void stopMusic();

//7.3 窄字符串转换为宽字符串
wchar_t* narrowToWide(const char* narrowStr);

//7.打印方块
void printBlock(int x, int y, int shape, int status, int color);

//8.删除方块
void deleteBlock(int x, int y, int shape, int status, int color);

//9.产生游戏第一个方块
void startBlock(int n);

//10.产生下一个方块
void nextBlock(int n);

//11.拷贝方块
void copyBlock();

//12.方块下移操作
//返回值：标记方块是否到游戏池底部
int downBlock(int n);

//13.方块的左移、右移、变形、直接落底
void leftBlock();

void rightBlock();

void changeBlock();

void bottonBolck(int n);

//14.碰撞检测
int crash(int x, int y, int shape, int status);

//15.保存方块
void save();
void save_enter();

//16.刷新游戏池
void updateGame(int n);

//17.游戏暂停
void pause();

//18.消行检测
void lineClear();

//19.消行下移
void lineDown(int line);

//20.游戏结束动画
void printOver();

//21.游戏重新开始提示
void printFinish();

//22.重新开始游戏
void againGame();

//23.游戏结束界面
void endGame();

//24.打印开始图案
void printStart(int x, int y);

//25.清除开始动画
void deleteStart(int x, int y);

//26.动画效果 -> 定时(边界)
void printAnimation();

//27.游戏模式
void gameMode(float time, int n);

//28.游戏模式选择界面
void gameModeChoose();

//29.读取历史分数
int readHistory(int mode);

//30.写入历史分数
void writeHistory(int grade, int mode);

#endif // GAME_H_INCLUDED
