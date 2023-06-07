#pragma once
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include<stdio.h>
#include<time.h>

/*��Ϸ�߼�ģ��*/

//����ṹ��
typedef struct
{
	int x;
	int y;      // ����
	int shape;  //��̬
	int status; //״̬
	int color;  //��ɫ
}BLOCK;

//1.������Ϸ�ر߿�
void windowPrint(int x, int y);

//2.��Ϸ��ʼ��
void gameInit();

//3.��ӡ����˵��
void printInfo(int n);

//4.��ӡ�����͵ȼ�
void printGradeLevel(int num);

//5.��Ϸ��ʱ����
void gameTime(clock_t start_time);

//6.��ӡ��߿�
void borderLeft();

//7.1��������
void playMusic(int mode, wchar_t* filename);

//7.2ֹͣ����
void stopMusic();

//7.3 խ�ַ���ת��Ϊ���ַ���
wchar_t* narrowToWide(const char* narrowStr);

//7.��ӡ����
void printBlock(int x, int y, int shape, int status, int color);

//8.ɾ������
void deleteBlock(int x, int y, int shape, int status, int color);

//9.������Ϸ��һ������
void startBlock(int n);

//10.������һ������
void nextBlock(int n);

//11.��������
void copyBlock();

//12.�������Ʋ���
//����ֵ����Ƿ����Ƿ���Ϸ�صײ�
int downBlock(int n);

//13.��������ơ����ơ����Ρ�ֱ�����
void leftBlock();

void rightBlock();

void changeBlock();

void bottonBolck(int n);

//14.��ײ���
int crash(int x, int y, int shape, int status);

//15.���淽��
void save();
void save_enter();

//16.ˢ����Ϸ��
void updateGame(int n);

//17.��Ϸ��ͣ
void pause();

//18.���м��
void lineClear();

//19.��������
void lineDown(int line);

//20.��Ϸ��������
void printOver();

//21.��Ϸ���¿�ʼ��ʾ
void printFinish();

//22.���¿�ʼ��Ϸ
void againGame();

//23.��Ϸ��������
void endGame();

//24.��ӡ��ʼͼ��
void printStart(int x, int y);

//25.�����ʼ����
void deleteStart(int x, int y);

//26.����Ч�� -> ��ʱ(�߽�)
void printAnimation();

//27.��Ϸģʽ
void gameMode(float time, int n);

//28.��Ϸģʽѡ�����
void gameModeChoose();

//29.��ȡ��ʷ����
int readHistory(int mode);

//30.д����ʷ����
void writeHistory(int grade, int mode);

#endif // GAME_H_INCLUDED
