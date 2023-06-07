#include "mywindows.h"

/*ʵ��ϵͳ����ģ��*/

HANDLE handle;

//1.��ʼ�����
void initHandle()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}

//2.������ɫ
void setColor(int color)
{
    SetConsoleTextAttribute(handle, color);
}
//3.���ù��λ��
void setPos(int x, int y)
{
    COORD coord = { x * 2, y };
    SetConsoleCursorPosition(handle, coord);
}

//4.���ع��
void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;   //���ù���Ƿ�ɼ�
    info.dwSize = 1;         //���ù���ȣ�1-100��
    SetConsoleCursorInfo(handle, &info);
}
