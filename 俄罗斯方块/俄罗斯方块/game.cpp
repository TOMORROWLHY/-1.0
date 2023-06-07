#include"game.h"
#include"data.h"
#include"mywindows.h"
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#include<windows.h>
#pragma comment(lib, "winmm.lib")   // 播放音乐头文件

/*游戏逻辑模块实现*/

int grade = 0;     //分数
int historyGrade;
int level = 1;     //等级
int n = 0;   //游戏模式选择项
int one = 0, two = 0, three = 0, four = 0;    //消的行数

//宽字符常量使用的是16位Unicode编码，而普通的字符常量使用的是8位ASCII编码。
const char* backGround = "D:\\C语言学习  代码作业\\俄罗斯方块\\猪猪侠.wav";
wchar_t* BackGroud = narrowToWide(backGround);

const char* effect = "D:\\C语言学习  代码作业\\俄罗斯方块\\消行音乐副本.wav";
wchar_t* Effect = narrowToWide(effect);



clock_t start_time;

BLOCK cur_block;    //当前方块
BLOCK next_block;   //下一个方块

//1.绘制游戏池边框
void windowPrint(int x, int y)
{
    int i, j;
    for (i = 0; i < 25; i++)
    {
        for (j = 0; j < 26; j++)
        {
            if (windowShape[i][j] == 1)
            {
                setColor(0xc0);
                setPos(x + j, y + i);
                printf("%2s", "");
            }
        }
    }
}

//2.游戏初始化
void gameInit()
{
    //初始化句柄
    initHandle();

    // 播放音乐
    //PlaySound(L"D:\\C语言学习  代码作业\\俄罗斯方块\\猪猪侠.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    playMusic(3,BackGroud);
    printAnimation();
    gameModeChoose();
}

//3.打印操作说明
void printInfo(int n)
{
    setColor(12);
    switch (n)
    {
    case 1:
        setPos(33, 9);
        printf("菜鸟模式");
        setPos(31, 11);
        printf("1.方块匀速下落");
        setPos(31, 12);
        printf("2.方块可见");
        break;
    case 2:
        setPos(33, 9);
        printf("高手模式");
        setPos(31, 11);
        printf("1.方块加速下落");
        setPos(31, 12);
        printf("2.方块可见");
        break;
    case 3:
        setPos(33, 9);
        printf("大神模式");
        setPos(31, 11);
        printf("1.方块加速下落");
        setPos(31, 12);
        printf("2.方块不可见");
        break;
    case 4:
        setPos(33, 9);
        printf("脑洞模式");
        setPos(31, 11);
        printf("1.方块较快下落");
        setPos(31, 12);
        printf("2.方块可见");
        setPos(31, 13);
        printf("3.新方块出没！");
        break;
    }

    setColor(0x0a);
    setPos(33, 15);
    printf("操作规则");
    setPos(31, 17);
    printf("1.按A或者←左移");
    setPos(31, 18);
    printf("2.按D或者→右移");
    setPos(31, 19);
    printf("3.按S或者↓下移");
    setPos(31, 20);
    printf("4.按W或者↑变形");
    setPos(31, 21);
    printf("5.按回车直接下落");
    setPos(31, 22);
    printf("6.按空格暂停");
}

//4.打印分数和等级
void printGradeLevel(int num)
{
    switch (num)
    {
    case 0:
        break;
    case 1:
        grade += 10; one++; break;
    case 2:
        grade += 40; two++; break;
    case 3:
        grade += 60; three++; break;
    case 4:
        grade += 80; four++; break;
    }

    setColor(0x0e);
    setPos(5, 6);
    printf("分数:%d", grade);

    if (grade < 10)
        level = 1;
    else if (grade >= 10 && grade < 50)
        level = 2;
    else if (grade >= 50 && grade < 100)
        level = 3;
    else if (grade >= 100 && grade < 200)
        level = 4;
    else if (grade >= 200 && grade < 400)
        level = 5;
    else if (grade >= 400 && grade < 800)
        level = 6;
    else if (grade >= 800 && grade < 1600)
        level = 7;
    else if (grade >= 1600)
        level = 8;

    setPos(5, 7);
    switch (level)
    {
    case 1:
        printf("段位:倔强青铜"); break;
    case 2:
        printf("段位:秩序白银"); break;
    case 3:
        printf("段位:荣耀黄金"); break;
    case 4:
        printf("段位:尊贵铂金"); break;
    case 5:
        printf("段位:永恒钻石"); break;
    case 6:
        printf("段位:至尊星耀"); break;
    case 7:
        printf("段位:最强王者"); break;
    case 8:
        printf("段位:荣耀王者"); break;

    }
    setPos(5, 11);
    printf("消除一行 %d次", one);
    setPos(5, 12);
    printf("消除二行 %d次", two);
    setPos(5, 13);
    printf("消除三行 %d次", three);
    setPos(5, 14);
    printf("消除四行 %d次", four);

    time_t timep;
    struct tm timeInfo;
    time(&timep);
    gmtime_s(&timeInfo, &timep);

    setColor(15);
    setPos(3, 18);
    printf("日期：%d/%d", 1900 + timeInfo.tm_year, timeInfo.tm_mon + 1);
    setPos(3, 19);
    printf("时间：%d:%d:%d", 8 + timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    setPos(3, 22);
    printf("此模式历史分数: %d", historyGrade);
}

//5.游戏计时功能
void gameTime(clock_t start_time)
{
    setColor(15);
    setPos(3, 3);
    printf("本次游戏已运行 %ld s", (clock() - start_time) / CLOCKS_PER_SEC);
}

//6.打印左边框
void borderLeft()
{
    setColor(0x09);
    setPos(0, 0);
    printf("□□□□□□□□□□□□□□□\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□□□□□□□□□□□□□□□\n");
}

//7.1 播放音乐 
//循环同步播放为1  单次同步播放为2   循环异步播放为3  单次异步播放为4
void playMusic(int mode, wchar_t* filename)
{
    switch (mode) 
    {

      case 1:
        PlaySound(filename, NULL, SND_FILENAME | SND_SYNC | SND_LOOP);
        break;
      case 2:
        PlaySound(filename, NULL, SND_FILENAME | SND_SYNC );
        break;
      case 3:
        PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        break;
      case 4:
        PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC );
     }
    
}
//7.2 关闭当前正在播放的音乐
void stopMusic() 
{
    PlaySound(NULL, NULL, SND_FILENAME);
}

//7.3  窄字符串转化为宽字符串
//宽字符常量使用的是16位Unicode编码，而普通的字符常量使用的是8位ASCII编码。
wchar_t* narrowToWide(const char* narrowStr)
{
    int wideStrLength = MultiByteToWideChar(CP_ACP, 0, narrowStr, -1, NULL, 0);
    wchar_t* wideStr = (wchar_t*)malloc(wideStrLength * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, narrowStr, -1, wideStr, wideStrLength);
    return wideStr;
}


//7.打印方块
void printBlock(int x, int y, int shape, int status, int color)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[shape][status][i][j] == 1)
            {
                setColor(color);
                setPos(x + j, y + i);
                printf("■");
            }
        }
    }
}
//8.删除方块
void deleteBlock(int x, int y, int shape, int status, int color)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[shape][status][i][j] == 1)
            {
                setColor(color);
                setPos(x + j, y + i);
                printf("%2s", "");  //用""代替■，完成删除效果
            }
        }
    }
}
//9.产生游戏第一个方块
void startBlock(int n)
{
    //第一个方块：形状/形态/颜色->随机，位置固定
    //初始化cur_block
    //设置一个随机数种子，产生不一样的随机数，使用的是时间，因为时间永远不一样
    srand((unsigned)time(NULL));
    cur_block.x = 22;
    cur_block.y = 1;
    switch (n)
    {
    case 1:
        next_block.shape = rand() % 7;
        next_block.status = rand() % 4;
        break;
    case 2:
        next_block.shape = rand() % 7;
        next_block.status = rand() % 4;
        break;
    case 3:
        next_block.shape = rand() % 7;
        next_block.status = rand() % 4;
        break;
    case 4:
        next_block.shape = rand() % 10;
        next_block.status = rand() % 4;
        break;
    }
    
    cur_block.color = rand() % 0x10;

    //如果颜色是黑色则变为白色
    if (cur_block.color == 0x00)
    {
        cur_block.color = 0x0a;
    }
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
}

//10.产生下一个方块
void nextBlock(int n)
{
    //形状/形态/颜色->随机， 位置固定
    //初始化netx_block
    next_block.x = 33;
    next_block.y = 2;
    deleteBlock(next_block.x, next_block.y, next_block.shape, next_block.status, next_block.color);
    switch (n)
    {
    case 1:
        next_block.shape = rand() % 7;
        next_block.status = rand() % 4;
        break;
    case 2:
        next_block.shape = rand() % 7;
        next_block.status = rand() % 4;
        break;
    case 3:
        next_block.shape = rand() % 7;
        next_block.status = rand() % 4;
        break;
    case 4:
        next_block.shape = rand() % 10;
        next_block.status = rand() % 4;
        break;
    }
    next_block.color = rand() % 0x10;
    //如果颜色是黑色则变为白色
    if (next_block.color == 0x00)
    {
        next_block.color = 0x0a;
    }
    printBlock(next_block.x, next_block.y, next_block.shape, next_block.status, next_block.color);
}
//11.拷贝方块
void copyBlock()
{
    //当前方块=下一个方块，并产生新的下一个方块
    cur_block = next_block;
    cur_block.x = 22;
    cur_block.y = 1;
    printBlock(next_block.x, next_block.y, next_block.shape, next_block.status, next_block.color);
    nextBlock(n);
}
//12.方块下移操作
//返回值：标记方块是否到游戏池底部
int downBlock(int n)
{
    //原理：删除掉现在正在显示的方块，纵坐标+1，重新打印出来
    if (crash(cur_block.x, cur_block.y + 1, cur_block.shape, cur_block.status) == -1)
    {
        //发生了碰撞，方块落到了游戏池底部
        //产生新的方块，下一个方块值->当前正在下落的方块->重新产生下一个方块
        //保存方块->检测消行->打印游戏池->产生新的方块
        save();
        lineClear();
        updateGame(n);
        copyBlock();
        return -1;
    }
    else if (crash(cur_block.x, cur_block.y + 1, cur_block.shape, cur_block.status) == -2)
    {
        //游戏结束
        return -2;
    }
    else
    {
        deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
        cur_block.y += 1;
        printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
        return 0;
    }

}

//13.方块的左移、右移、变形、直接落底
void leftBlock()
{
    if (crash(cur_block.x - 1, cur_block.y, cur_block.shape, cur_block.status) == -1)
    {
        //如果发生碰撞什么都不做，直接返回
        return;
    }
    deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
    cur_block.x -= 1;
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
}

void rightBlock()
{
    if (crash(cur_block.x + 1, cur_block.y, cur_block.shape, cur_block.status) == -1)
    {
        //如果发生碰撞什么都不做，直接返回
        return;
    }
    deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
    cur_block.x += 1;
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
}

void changeBlock()
{
    //通过数组下标+1来获得下一个形态，下标值0-3
    if (crash(cur_block.x, cur_block.y, cur_block.shape, (cur_block.status + 1) % 4) == -1)
    {
        return;
    }
    deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
    cur_block.status = (cur_block.status + 1) % 4;
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
}

//直接落地
void bottonBolck(int n)
{
    while (1)
    {
        if (crash(cur_block.x, cur_block.y, cur_block.shape, cur_block.status) == -1)
        {
            //发生碰撞->保存方块->检测消行->更新游戏池->拷贝方块
            save_enter();
            lineClear();
            updateGame(n);
            copyBlock();
            return;
        }
        else if (crash(cur_block.x, cur_block.y, cur_block.shape, cur_block.status) == -2)
        {
            //游戏结束
            return;
        }
        else
        {
            ++cur_block.y;
        }
    }
}

//14.碰撞检测
int crash(int x, int y, int shape, int status)
{
    //基于下一个位置的检测，参数为下一个位置或者下一个形态
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[shape][status][i][j] == 1)
            {

                if (windowShape[i + y][j + x - 15] == 1)
                {
                    //发生碰撞
                    if (cur_block.x == 22 && cur_block.y == 1)
                    {
                        //方块一产生就发生碰撞，直接游戏结束
                        return -2;
                    }

                    //方块落到了游戏池底部
                    return -1;
                }
            }
        }
    }
    return 0;
}

//15.保存方块
void save()
{
    //根据方块在界面在上的坐标，把坐标对应到游戏池的下标的对应位置来实现保存
    //方块为1的保存到windowShape数组
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[cur_block.shape][cur_block.status][i][j] == 1)
            {
                windowShape[i + cur_block.y][j + cur_block.x - 15] = 1;
            }
        }
    }
}
void save_enter()
{
    //根据方块在界面在上的坐标，把坐标对应到游戏池的下标的对应位置来实现保存
    //方块为1的保存到windowShape数组
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[cur_block.shape][cur_block.status][i][j] == 1)
            {
                windowShape[i + cur_block.y - 1][j + cur_block.x - 15] = 1;
            }
        }
    }
}

//16.刷新游戏池
void updateGame(int n)
{
    int i, j;
    for (i = 23; i > 0; i--)
    {
        for (j = 1; j < 15; j++)
        {
            switch (n)
            {
                //菜鸟模式  下落速度慢
            case 1:
                if (windowShape[i][j] == 1)
                {
                    setColor(0x0e);
                    setPos(15 + j, i);
                    printf("■");
                }
                else
                {
                    setColor(0x00);
                    setPos(15 + j, i);
                    printf("%2s", "");
                }
                break;

                //
            case 2:
                if (windowShape[i][j] == 1)
                {
                    setColor(0x0e);
                    setPos(15 + j, i);
                    printf("■");
                }
                else
                {
                    setColor(0x00);
                    setPos(15 + j, i);
                    printf("%2s", "");
                }
                break;
                //模式3  大神模式  （下落速度快）不可见
            case 3:
                if (windowShape[i][j] == 1)
                {
                    setColor(0x0e);
                    setPos(15 + j, i);
                    printf("%2s", "");
                }
                else
                {
                    setColor(0x00);
                    setPos(15 + j, i);
                    printf("%2s", "");
                }
                break;
                //模式4  创新模式
            case 4:
                if (windowShape[i][j] == 1)
                {
                    setColor(0x0e);
                    setPos(15 + j, i);
                    printf("■");
                }
                else
                {
                    setColor(0x00);
                    setPos(15 + j, i);
                    printf("%2s", "");
                }
                break;
            }


        }
    }
}

//17.游戏暂停
void pause()
{
    while (1)
    {
        if (_getch() == 32)
        {
            break;

        }
    }
}

//18.消行检测
void lineClear()
{
    //遍历windowShape数组判断是否有满行，即这行所有值相加为14
    int i, j;
    int number = 0;
    for (i = 23; i > 0; i--)
    {
        int total = 0;
        for (j = 1; j < 15; j++)
        {
            total += windowShape[i][j];
        }
        if (total == 14)
        {
            lineDown(i);
            i += 1;
            number += 1;
        }
    }
    printGradeLevel(number);
}

//19.消行下移
void lineDown(int line)
{
    //PlaySound(NULL, NULL, SND_FILENAME);
    stopMusic();
    playMusic(4, Effect);
   // PlaySound(L"D:\\C语言学习  代码作业\\俄罗斯方块\\消行音乐副本.wav", NULL, SND_FILENAME | SND_ASYNC);
    //从第line行开始， i=i-1
    int i, j;
    for (i = line; i > 1; i--)  //i>1用来保证边界不被下移
    {
        for (j = 1; j < 15; j++)
        {
            windowShape[i][j] = windowShape[i - 1][j]; //覆盖满行
        }
    }
    Sleep(250);
   // PlaySound(L"D:\\C语言学习  代码作业\\俄罗斯方块\\猪猪侠.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    playMusic(3, BackGroud);
}

//20.游戏结束动画
void printOver()
{
    int i, j;
    for (i = 23; i > 0; i--)
    {
        for (j = 1; j < 15; j++)
        {
            setColor(0x2e);
            setPos(j + 15, i);
            printf("☆");
            Sleep(5);  //稍稍停顿一下
        }
    }
}

//21.游戏重新开始提示
void printFinish()
{
    setColor(0x0f);
    setPos(20, 8);
    printf("游戏结束！");
    setPos(20, 10);
    printf("按Y重新开始 ");
    setPos(20, 11);
    printf("按N结束游戏 ");

    //检测用户按键
    switch (_getch())
    {
    case 'y':
    case 'Y':
        againGame(); break;
    case 'n':
    case 'N':
        mciSendString(TEXT("stop a"), NULL, 0, NULL);
        endGame();
        break;
    default:
        printFinish();
    }
}

//22.重新开始游戏
void againGame()
{
    //重置分数/等级/游戏池数据->开始游戏
    level = 1;
    grade = 0;
    one = 0;
    two = 0;
    three = 0;
    four = 0;

    int i, j;
    for (i = 1; i < 24; i++)
    {
        for (j = 1; j < 15; j++)
        {
            windowShape[i][j] = 0;
        }
    }
    system("cls"); //清屏
    gameInit();
}

//23.游戏结束界面边框
void endGame()
{
    system("cls");

    setPos(21, 8);
    setColor(12);
    printf("Game Over!");

    setPos(21, 12);
    printf("分数:%d", grade);

    setPos(21, 12);
    switch (level)
    {
    case 1:
        printf("段位：倔强青铜"); break;
    case 2:
        printf("段位：秩序白银"); break;
    case 3:
        printf("段位：荣耀黄金"); break;
    case 4:
        printf("段位：尊贵铂金"); break;
    case 5:
        printf("段位：永恒钻石"); break;
    case 6:
        printf("段位：至尊星耀"); break;
    case 7:
        printf("段位：最强王者"); break;
    case 8:
        printf("段位：荣耀王者"); break;
    }

    setPos(21, 14);
    printf("消除一行 %d次", one);
    setPos(21, 16);
    printf("消除二行 %d次", two);
    setPos(21, 18);
    printf("消除三行 %d次", three);
    setPos(21, 20);
    printf("消除四行 %d次", four);

    setPos(21, 22);
    printf("本次游戏运行共用时 %ld s", (clock() - start_time) / CLOCKS_PER_SEC);

    int i;
    setPos(23, 2);
    setColor(6);
    printf("\\\\\\|///");

    setPos(22, 3);
    setColor(6);
    printf("\\\\\\|///");

    setPos(24, 3);
    setColor(15);
    printf(".-.-");

    setPos(27, 3);
    setColor(6);
    printf("//");

    setPos(22, 4);
    setColor(14);
    printf("(");

    setPos(24, 4);
    setColor(15);
    printf(".@.@");

    setPos(27, 4);
    setColor(14);
    printf(")");

    setPos(8, 5);
    setColor(11);
    printf("+------------------------");

    setPos(17, 5);
    setColor(14);
    printf("o00o");

    setPos(19, 5);
    setColor(11);
    printf("---------");

    setPos(24, 5);
    setColor(14);
    printf("(_)");

    setPos(26, 5);
    setColor(11);
    printf("---------");

    setPos(31, 5);
    setColor(14);
    printf("o00o");

    setPos(33, 5);
    setColor(11);
    printf("----------------+");

    for (i = 6; i <= 24; i++)
    {
        setPos(8, i);
        printf("|");
        setPos(41, i);
        printf("|");
    }

    setPos(8, 25);
    printf("+----------------------------");

    setPos(23, 25);
    setColor(14);
    printf("☆ ☆ ☆");

    setPos(28, 25);
    setColor(11);
    printf("--------------------------+\n\n");

    _getch(); // 任意键退出
    exit(0);
}

//24.打印开始图案
void printStart(int x, int y)
{
    // 随机图案颜色
    int color = rand() % 0x10;
    if (color == 0x00)
    {
        color = 0x0f;
    }
    //绘制图案
    setColor(color);
    setPos(x, y);
    printf("■■■■■   ■■■■■  ■■■■■  ■■■■■   ■■■   ■■■■");
    setPos(x, y + 1);
    printf("    ■       ■              ■      ■      ■     ■    ■");
    setPos(x, y + 2);
    printf("    ■       ■■■■        ■      ■■■■■     ■      ■■■");
    setPos(x, y + 3);
    printf("    ■       ■              ■      ■  ■         ■            ■");
    setPos(x, y + 4);
    printf("    ■       ■■■■■      ■      ■     ■■  ■■■   ■■■■");


    setPos(25, 15);
    printf("按Enter键开始游戏！");
}

//25.清除开始动画
void deleteStart(int x, int y)
{
    int i, j;
    for (i = y; i <= y + 5; i++)
    {
        for (j = x; j < x + 35; j++)
        {
            setPos(j, i);
            printf("%2s", "");
        }
    }
}

//26.动画效果 -> 定时(边界)
void printAnimation()
{
    clock_t time1, time2;
    time1 = clock();
    int x = 5;
    printStart(x, 5);
    while (1)
    {
        time2 = clock();
        if (time2 - time1 > 200)  //时间间隔200ms
        {
            time1 = time2;
            deleteStart(x, 5);
          
            printStart(++x, 5);
            if (x == 22)
            {
                deleteStart(x, 5);
               
                x = 5;
            }
        }
        //按Enter键开始游戏，退出动画
        if (_kbhit())
        {
            if (_getch() == 13)
            {
                break;
            }
            else
            {
                setPos(22, 17);
                //随机图案颜色
                int color = rand() % 0x10;
                if (color == 0x00)
                {
                    color = 0x0f;
                }
                printf("输入有误！请按Enter键开始游戏！");
                _getch();
                system("cls");
            }
        }
    }
    system("cls");
}

//27.游戏模式
void gameMode(float time, int n)
{
    //游戏开始时间
    clock_t startTime = clock();

    //定时器
    clock_t time1, time2;
    time1 = clock();

    while (1)
    {
        //检测是否有按键按下
        if (_kbhit())
        {
            switch (_getch())
            {
                //方块变形
            case 'w':
            case 'W':
            case 72:
                changeBlock(); 
                break;
                //方块左移
            case 'a':
            case 'A':
            case 75:
                leftBlock();
                break;
                //方块右移
            case 'd':
            case 'D':
            case 77:
                rightBlock();
                break;
                //方块下移
            case 's':
            case 'S':
            case 80:
                downBlock(n); 
                break;
                //空格:暂停
            case 32:
                pause(); 
                break;
                //Enter:方块落底
            case 13:
                bottonBolck(n);
                break;
            }
        }
        time2 = clock();
        //每0.65s下落一次
        //clock()获得的时间转为秒需要除以CLOCKS_PER_SEC
        if (time2 - time1 > time * CLOCKS_PER_SEC)
        {
            //游戏计时
            gameTime(startTime);
            if (downBlock(n) == -2)
            {
                break;
            }
            time1 = time2;
        }
    }
}

//28.游戏模式选择界面
void gameModeChoose()
{
    system("cls");

    int i;
    setPos(23, 2);
    setColor(6);
    printf("\\\\\\|///");

    setPos(22, 3);
    printf("\\\\");

    setPos(24, 3);
    setColor(15);
    printf(".-.-");

    setPos(27, 3);
    setColor(15);
    printf("//");

    setPos(22, 4);
    setColor(14);
    printf("(");

    setPos(24, 4);
    setColor(15);
    printf(".@.@");

    setPos(27, 4);
    setColor(14);
    printf(")");

    setPos(8, 5);
    setColor(11);
    printf("+------------------------");

    setPos(17, 5);
    setColor(14);
    printf("o00o");

    setPos(19, 5);
    setColor(11);
    printf("---------");

    setPos(24, 5);
    setColor(14);
    printf("(_)");

    setPos(26, 5);
    setColor(11);
    printf("---------");

    setPos(31, 5);
    setColor(14);
    printf("o00o");

    setPos(33, 5);
    setColor(11);
    printf("----------------+");

    for (i = 6; i <= 24; i++)
    {
        setPos(8, i);
        printf("|");
        setPos(41, i);
        printf("|");
    }

    setPos(8, 25);
    printf("+----------------------------");

    setPos(23, 25);
    setColor(14);
    printf("☆ ☆ ☆");

    setPos(28, 25);
    setColor(11);
    printf("--------------------------+\n\n");

    setPos(20, 9);
    setColor(11);
    printf("俄罗斯方块模式选择");

    setColor(12);
    setPos(9, 15);
    printf("1.菜鸟模式");
    setPos(18, 15);
    printf("2.高手模式");
    setPos(28, 15);
    printf("3.大神模式");
    setPos(36, 15);
    printf("4.脑洞模式");


    setPos(21, 22);
    setColor(3);
    printf("请选择 1 2 3 4");
    setColor(14);

    
    scanf_s("%d", &n);
    switch (n)
    {
    case 1:
        historyGrade = readHistory(1);
        system("cls");

        windowPrint(15, 0);
        printInfo(n);
        borderLeft(); //左边框

        printGradeLevel(0);
        startBlock(n);
        nextBlock(n);
        gameMode(0.65, 1);
        if (grade > historyGrade) {
            writeHistory(grade, 1);
        }
        printOver();
        printFinish();

        break;
    case 2:
        historyGrade = readHistory(2);
        system("cls");

        windowPrint(15, 0);
        printInfo(n);
        borderLeft(); //左边框

        printGradeLevel(0);
        startBlock(n);
        nextBlock(n);
        gameMode(0.15, 2);
        if (grade > historyGrade) {
            writeHistory(grade, 2);
        }
        printOver();
        printFinish();

        break;
    case 3:
        historyGrade = readHistory(3);
        system("cls");

        windowPrint(15, 0);
        printInfo(n);
        borderLeft(); //左边框

        printGradeLevel(0);
        startBlock(n);
        nextBlock(n);
        gameMode(0.15, 3);
        if (grade > historyGrade) {
            writeHistory(grade, 3);
        }
        printOver();
        printFinish();

        break;
    case 4:
        historyGrade = readHistory(2);
        system("cls");

        windowPrint(15, 0);
        printInfo(n);
        borderLeft(); //左边框

        printGradeLevel(0);
        startBlock(n);
        nextBlock(n);
        gameMode(0.35, 4);
        if (grade > historyGrade) {
            writeHistory(grade, 2);
        }
        printOver();
        printFinish();

        break;
    default:
        setColor(12);
        setPos(21, 23);
        printf("请输入1-4之间的数!");
        _getch();
        system("cls");
        gameModeChoose();
    }

}


//29.读历史记录
int readHistory(int mode)
{
    FILE* file;
    int grade;
    switch (mode) {
    case 1:
        fopen_s(&file, "grade1.txt", "r");

        if (file == NULL) {
            printf("无法打开文件\n");
            return -1;
        }

        if (fscanf_s(file, "%d", &grade) != 1) {
            printf("文件内容不符合要求\n");
            return -1;
        }

        fclose(file);

        break;
    case 2:
        fopen_s(&file, "grade2.txt", "r");

        if (file == NULL) {
            printf("无法打开文件\n");
            return -1;
        }

        if (fscanf_s(file, "%d", &grade) != 1) {
            printf("文件内容不符合要求\n");
            return -1;
        }

        fclose(file);

        break;

    case 3:
        fopen_s(&file, "grade3.txt", "r");

        if (file == NULL) {
            printf("无法打开文件\n");
            return -1;
        }

        if (fscanf_s(file, "%d", &grade) != 1) {
            printf("文件内容不符合要求\n");
            return -1;
        }

        fclose(file);

        break;
    case 4:
        fopen_s(&file, "grade4.txt", "r");

        if (file == NULL) {
            printf("无法打开文件\n");
            return -1;
        }

        if (fscanf_s(file, "%d", &grade) != 1) {
            printf("文件内容不符合要求\n");
            return -1;
        }

        fclose(file);
        break;
    }
    return grade;
}

//30.写历史记录
void writeHistory(int grade, int mode)
{
    FILE* file;
    switch (mode) {
    case 1:
    {
        fopen_s(&file, "grade1.txt", "w");

        if (file == NULL) {
            printf("无法打开文件\n");
            return;
        }

        fprintf(file, "%d\n", grade); // 写入整数到文件中

        fclose(file);

        break;
    }
    case 2:
    {
        fopen_s(&file, "grade2.txt", "w");

        if (file == NULL) {
            printf("无法打开文件\n");
            return;
        }

        fprintf(file, "%d\n", grade); // 写入整数到文件中

        fclose(file);

        break;
    }
    case 3:
    {
        fopen_s(&file, "grade3.txt", "w");

        if (file == NULL) {
            printf("无法打开文件\n");
            return;
        }

        fprintf(file, "%d\n", grade); // 写入整数到文件中

        fclose(file);

        break;
    }
    case 4:
    {
        fopen_s(&file, "grade4.txt", "w");

        if (file == NULL) {
            printf("无法打开文件\n");
            return;
        }

        fprintf(file, "%d\n", grade); // 写入整数到文件中

        fclose(file);
        break;
    }
    }
}
