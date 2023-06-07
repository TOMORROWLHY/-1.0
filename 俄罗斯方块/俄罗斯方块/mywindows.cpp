#include "mywindows.h"

/*实现系统调用模块*/

HANDLE handle;

//1.初始化句柄
void initHandle()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}

//2.设置颜色
void setColor(int color)
{
    SetConsoleTextAttribute(handle, color);
}
//3.设置光标位置
void setPos(int x, int y)
{
    COORD coord = { x * 2, y };
    SetConsoleCursorPosition(handle, coord);
}

//4.隐藏光标
void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;   //设置光标是否可见
    info.dwSize = 1;         //设置光标宽度（1-100）
    SetConsoleCursorInfo(handle, &info);
}
