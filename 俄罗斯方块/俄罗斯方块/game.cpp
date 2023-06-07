#include"game.h"
#include"data.h"
#include"mywindows.h"
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#include<windows.h>
#pragma comment(lib, "winmm.lib")   // ��������ͷ�ļ�

/*��Ϸ�߼�ģ��ʵ��*/

int grade = 0;     //����
int historyGrade;
int level = 1;     //�ȼ�
int n = 0;   //��Ϸģʽѡ����
int one = 0, two = 0, three = 0, four = 0;    //��������

//���ַ�����ʹ�õ���16λUnicode���룬����ͨ���ַ�����ʹ�õ���8λASCII���롣
const char* backGround = "D:\\C����ѧϰ  ������ҵ\\����˹����\\������.wav";
wchar_t* BackGroud = narrowToWide(backGround);

const char* effect = "D:\\C����ѧϰ  ������ҵ\\����˹����\\�������ָ���.wav";
wchar_t* Effect = narrowToWide(effect);



clock_t start_time;

BLOCK cur_block;    //��ǰ����
BLOCK next_block;   //��һ������

//1.������Ϸ�ر߿�
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

//2.��Ϸ��ʼ��
void gameInit()
{
    //��ʼ�����
    initHandle();

    // ��������
    //PlaySound(L"D:\\C����ѧϰ  ������ҵ\\����˹����\\������.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    playMusic(3,BackGroud);
    printAnimation();
    gameModeChoose();
}

//3.��ӡ����˵��
void printInfo(int n)
{
    setColor(12);
    switch (n)
    {
    case 1:
        setPos(33, 9);
        printf("����ģʽ");
        setPos(31, 11);
        printf("1.������������");
        setPos(31, 12);
        printf("2.����ɼ�");
        break;
    case 2:
        setPos(33, 9);
        printf("����ģʽ");
        setPos(31, 11);
        printf("1.�����������");
        setPos(31, 12);
        printf("2.����ɼ�");
        break;
    case 3:
        setPos(33, 9);
        printf("����ģʽ");
        setPos(31, 11);
        printf("1.�����������");
        setPos(31, 12);
        printf("2.���鲻�ɼ�");
        break;
    case 4:
        setPos(33, 9);
        printf("�Զ�ģʽ");
        setPos(31, 11);
        printf("1.����Ͽ�����");
        setPos(31, 12);
        printf("2.����ɼ�");
        setPos(31, 13);
        printf("3.�·����û��");
        break;
    }

    setColor(0x0a);
    setPos(33, 15);
    printf("��������");
    setPos(31, 17);
    printf("1.��A���ߡ�����");
    setPos(31, 18);
    printf("2.��D���ߡ�����");
    setPos(31, 19);
    printf("3.��S���ߡ�����");
    setPos(31, 20);
    printf("4.��W���ߡ�����");
    setPos(31, 21);
    printf("5.���س�ֱ������");
    setPos(31, 22);
    printf("6.���ո���ͣ");
}

//4.��ӡ�����͵ȼ�
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
    printf("����:%d", grade);

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
        printf("��λ:��ǿ��ͭ"); break;
    case 2:
        printf("��λ:�������"); break;
    case 3:
        printf("��λ:��ҫ�ƽ�"); break;
    case 4:
        printf("��λ:��󲬽�"); break;
    case 5:
        printf("��λ:������ʯ"); break;
    case 6:
        printf("��λ:������ҫ"); break;
    case 7:
        printf("��λ:��ǿ����"); break;
    case 8:
        printf("��λ:��ҫ����"); break;

    }
    setPos(5, 11);
    printf("����һ�� %d��", one);
    setPos(5, 12);
    printf("�������� %d��", two);
    setPos(5, 13);
    printf("�������� %d��", three);
    setPos(5, 14);
    printf("�������� %d��", four);

    time_t timep;
    struct tm timeInfo;
    time(&timep);
    gmtime_s(&timeInfo, &timep);

    setColor(15);
    setPos(3, 18);
    printf("���ڣ�%d/%d", 1900 + timeInfo.tm_year, timeInfo.tm_mon + 1);
    setPos(3, 19);
    printf("ʱ�䣺%d:%d:%d", 8 + timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    setPos(3, 22);
    printf("��ģʽ��ʷ����: %d", historyGrade);
}

//5.��Ϸ��ʱ����
void gameTime(clock_t start_time)
{
    setColor(15);
    setPos(3, 3);
    printf("������Ϸ������ %ld s", (clock() - start_time) / CLOCKS_PER_SEC);
}

//6.��ӡ��߿�
void borderLeft()
{
    setColor(0x09);
    setPos(0, 0);
    printf("������������������������������\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("��                          ��\n");
    printf("������������������������������\n");
}

//7.1 �������� 
//ѭ��ͬ������Ϊ1  ����ͬ������Ϊ2   ѭ���첽����Ϊ3  �����첽����Ϊ4
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
//7.2 �رյ�ǰ���ڲ��ŵ�����
void stopMusic() 
{
    PlaySound(NULL, NULL, SND_FILENAME);
}

//7.3  խ�ַ���ת��Ϊ���ַ���
//���ַ�����ʹ�õ���16λUnicode���룬����ͨ���ַ�����ʹ�õ���8λASCII���롣
wchar_t* narrowToWide(const char* narrowStr)
{
    int wideStrLength = MultiByteToWideChar(CP_ACP, 0, narrowStr, -1, NULL, 0);
    wchar_t* wideStr = (wchar_t*)malloc(wideStrLength * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, narrowStr, -1, wideStr, wideStrLength);
    return wideStr;
}


//7.��ӡ����
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
                printf("��");
            }
        }
    }
}
//8.ɾ������
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
                printf("%2s", "");  //��""����������ɾ��Ч��
            }
        }
    }
}
//9.������Ϸ��һ������
void startBlock(int n)
{
    //��һ�����飺��״/��̬/��ɫ->�����λ�ù̶�
    //��ʼ��cur_block
    //����һ����������ӣ�������һ�����������ʹ�õ���ʱ�䣬��Ϊʱ����Զ��һ��
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

    //�����ɫ�Ǻ�ɫ���Ϊ��ɫ
    if (cur_block.color == 0x00)
    {
        cur_block.color = 0x0a;
    }
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
}

//10.������һ������
void nextBlock(int n)
{
    //��״/��̬/��ɫ->����� λ�ù̶�
    //��ʼ��netx_block
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
    //�����ɫ�Ǻ�ɫ���Ϊ��ɫ
    if (next_block.color == 0x00)
    {
        next_block.color = 0x0a;
    }
    printBlock(next_block.x, next_block.y, next_block.shape, next_block.status, next_block.color);
}
//11.��������
void copyBlock()
{
    //��ǰ����=��һ�����飬�������µ���һ������
    cur_block = next_block;
    cur_block.x = 22;
    cur_block.y = 1;
    printBlock(next_block.x, next_block.y, next_block.shape, next_block.status, next_block.color);
    nextBlock(n);
}
//12.�������Ʋ���
//����ֵ����Ƿ����Ƿ���Ϸ�صײ�
int downBlock(int n)
{
    //ԭ��ɾ��������������ʾ�ķ��飬������+1�����´�ӡ����
    if (crash(cur_block.x, cur_block.y + 1, cur_block.shape, cur_block.status) == -1)
    {
        //��������ײ�������䵽����Ϸ�صײ�
        //�����µķ��飬��һ������ֵ->��ǰ��������ķ���->���²�����һ������
        //���淽��->�������->��ӡ��Ϸ��->�����µķ���
        save();
        lineClear();
        updateGame(n);
        copyBlock();
        return -1;
    }
    else if (crash(cur_block.x, cur_block.y + 1, cur_block.shape, cur_block.status) == -2)
    {
        //��Ϸ����
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

//13.��������ơ����ơ����Ρ�ֱ�����
void leftBlock()
{
    if (crash(cur_block.x - 1, cur_block.y, cur_block.shape, cur_block.status) == -1)
    {
        //���������ײʲô��������ֱ�ӷ���
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
        //���������ײʲô��������ֱ�ӷ���
        return;
    }
    deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
    cur_block.x += 1;
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
}

void changeBlock()
{
    //ͨ�������±�+1�������һ����̬���±�ֵ0-3
    if (crash(cur_block.x, cur_block.y, cur_block.shape, (cur_block.status + 1) % 4) == -1)
    {
        return;
    }
    deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
    cur_block.status = (cur_block.status + 1) % 4;
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.status, cur_block.color);
}

//ֱ�����
void bottonBolck(int n)
{
    while (1)
    {
        if (crash(cur_block.x, cur_block.y, cur_block.shape, cur_block.status) == -1)
        {
            //������ײ->���淽��->�������->������Ϸ��->��������
            save_enter();
            lineClear();
            updateGame(n);
            copyBlock();
            return;
        }
        else if (crash(cur_block.x, cur_block.y, cur_block.shape, cur_block.status) == -2)
        {
            //��Ϸ����
            return;
        }
        else
        {
            ++cur_block.y;
        }
    }
}

//14.��ײ���
int crash(int x, int y, int shape, int status)
{
    //������һ��λ�õļ�⣬����Ϊ��һ��λ�û�����һ����̬
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[shape][status][i][j] == 1)
            {

                if (windowShape[i + y][j + x - 15] == 1)
                {
                    //������ײ
                    if (cur_block.x == 22 && cur_block.y == 1)
                    {
                        //����һ�����ͷ�����ײ��ֱ����Ϸ����
                        return -2;
                    }

                    //�����䵽����Ϸ�صײ�
                    return -1;
                }
            }
        }
    }
    return 0;
}

//15.���淽��
void save()
{
    //���ݷ����ڽ������ϵ����꣬�������Ӧ����Ϸ�ص��±�Ķ�Ӧλ����ʵ�ֱ���
    //����Ϊ1�ı��浽windowShape����
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
    //���ݷ����ڽ������ϵ����꣬�������Ӧ����Ϸ�ص��±�Ķ�Ӧλ����ʵ�ֱ���
    //����Ϊ1�ı��浽windowShape����
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

//16.ˢ����Ϸ��
void updateGame(int n)
{
    int i, j;
    for (i = 23; i > 0; i--)
    {
        for (j = 1; j < 15; j++)
        {
            switch (n)
            {
                //����ģʽ  �����ٶ���
            case 1:
                if (windowShape[i][j] == 1)
                {
                    setColor(0x0e);
                    setPos(15 + j, i);
                    printf("��");
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
                    printf("��");
                }
                else
                {
                    setColor(0x00);
                    setPos(15 + j, i);
                    printf("%2s", "");
                }
                break;
                //ģʽ3  ����ģʽ  �������ٶȿ죩���ɼ�
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
                //ģʽ4  ����ģʽ
            case 4:
                if (windowShape[i][j] == 1)
                {
                    setColor(0x0e);
                    setPos(15 + j, i);
                    printf("��");
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

//17.��Ϸ��ͣ
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

//18.���м��
void lineClear()
{
    //����windowShape�����ж��Ƿ������У�����������ֵ���Ϊ14
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

//19.��������
void lineDown(int line)
{
    //PlaySound(NULL, NULL, SND_FILENAME);
    stopMusic();
    playMusic(4, Effect);
   // PlaySound(L"D:\\C����ѧϰ  ������ҵ\\����˹����\\�������ָ���.wav", NULL, SND_FILENAME | SND_ASYNC);
    //�ӵ�line�п�ʼ�� i=i-1
    int i, j;
    for (i = line; i > 1; i--)  //i>1������֤�߽粻������
    {
        for (j = 1; j < 15; j++)
        {
            windowShape[i][j] = windowShape[i - 1][j]; //��������
        }
    }
    Sleep(250);
   // PlaySound(L"D:\\C����ѧϰ  ������ҵ\\����˹����\\������.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    playMusic(3, BackGroud);
}

//20.��Ϸ��������
void printOver()
{
    int i, j;
    for (i = 23; i > 0; i--)
    {
        for (j = 1; j < 15; j++)
        {
            setColor(0x2e);
            setPos(j + 15, i);
            printf("��");
            Sleep(5);  //����ͣ��һ��
        }
    }
}

//21.��Ϸ���¿�ʼ��ʾ
void printFinish()
{
    setColor(0x0f);
    setPos(20, 8);
    printf("��Ϸ������");
    setPos(20, 10);
    printf("��Y���¿�ʼ ");
    setPos(20, 11);
    printf("��N������Ϸ ");

    //����û�����
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

//22.���¿�ʼ��Ϸ
void againGame()
{
    //���÷���/�ȼ�/��Ϸ������->��ʼ��Ϸ
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
    system("cls"); //����
    gameInit();
}

//23.��Ϸ��������߿�
void endGame()
{
    system("cls");

    setPos(21, 8);
    setColor(12);
    printf("Game Over!");

    setPos(21, 12);
    printf("����:%d", grade);

    setPos(21, 12);
    switch (level)
    {
    case 1:
        printf("��λ����ǿ��ͭ"); break;
    case 2:
        printf("��λ���������"); break;
    case 3:
        printf("��λ����ҫ�ƽ�"); break;
    case 4:
        printf("��λ����󲬽�"); break;
    case 5:
        printf("��λ��������ʯ"); break;
    case 6:
        printf("��λ��������ҫ"); break;
    case 7:
        printf("��λ����ǿ����"); break;
    case 8:
        printf("��λ����ҫ����"); break;
    }

    setPos(21, 14);
    printf("����һ�� %d��", one);
    setPos(21, 16);
    printf("�������� %d��", two);
    setPos(21, 18);
    printf("�������� %d��", three);
    setPos(21, 20);
    printf("�������� %d��", four);

    setPos(21, 22);
    printf("������Ϸ���й���ʱ %ld s", (clock() - start_time) / CLOCKS_PER_SEC);

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
    printf("�� �� ��");

    setPos(28, 25);
    setColor(11);
    printf("--------------------------+\n\n");

    _getch(); // ������˳�
    exit(0);
}

//24.��ӡ��ʼͼ��
void printStart(int x, int y)
{
    // ���ͼ����ɫ
    int color = rand() % 0x10;
    if (color == 0x00)
    {
        color = 0x0f;
    }
    //����ͼ��
    setColor(color);
    setPos(x, y);
    printf("����������   ����������  ����������  ����������   ������   ��������");
    setPos(x, y + 1);
    printf("    ��       ��              ��      ��      ��     ��    ��");
    setPos(x, y + 2);
    printf("    ��       ��������        ��      ����������     ��      ������");
    setPos(x, y + 3);
    printf("    ��       ��              ��      ��  ��         ��            ��");
    setPos(x, y + 4);
    printf("    ��       ����������      ��      ��     ����  ������   ��������");


    setPos(25, 15);
    printf("��Enter����ʼ��Ϸ��");
}

//25.�����ʼ����
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

//26.����Ч�� -> ��ʱ(�߽�)
void printAnimation()
{
    clock_t time1, time2;
    time1 = clock();
    int x = 5;
    printStart(x, 5);
    while (1)
    {
        time2 = clock();
        if (time2 - time1 > 200)  //ʱ����200ms
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
        //��Enter����ʼ��Ϸ���˳�����
        if (_kbhit())
        {
            if (_getch() == 13)
            {
                break;
            }
            else
            {
                setPos(22, 17);
                //���ͼ����ɫ
                int color = rand() % 0x10;
                if (color == 0x00)
                {
                    color = 0x0f;
                }
                printf("���������밴Enter����ʼ��Ϸ��");
                _getch();
                system("cls");
            }
        }
    }
    system("cls");
}

//27.��Ϸģʽ
void gameMode(float time, int n)
{
    //��Ϸ��ʼʱ��
    clock_t startTime = clock();

    //��ʱ��
    clock_t time1, time2;
    time1 = clock();

    while (1)
    {
        //����Ƿ��а�������
        if (_kbhit())
        {
            switch (_getch())
            {
                //�������
            case 'w':
            case 'W':
            case 72:
                changeBlock(); 
                break;
                //��������
            case 'a':
            case 'A':
            case 75:
                leftBlock();
                break;
                //��������
            case 'd':
            case 'D':
            case 77:
                rightBlock();
                break;
                //��������
            case 's':
            case 'S':
            case 80:
                downBlock(n); 
                break;
                //�ո�:��ͣ
            case 32:
                pause(); 
                break;
                //Enter:�������
            case 13:
                bottonBolck(n);
                break;
            }
        }
        time2 = clock();
        //ÿ0.65s����һ��
        //clock()��õ�ʱ��תΪ����Ҫ����CLOCKS_PER_SEC
        if (time2 - time1 > time * CLOCKS_PER_SEC)
        {
            //��Ϸ��ʱ
            gameTime(startTime);
            if (downBlock(n) == -2)
            {
                break;
            }
            time1 = time2;
        }
    }
}

//28.��Ϸģʽѡ�����
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
    printf("�� �� ��");

    setPos(28, 25);
    setColor(11);
    printf("--------------------------+\n\n");

    setPos(20, 9);
    setColor(11);
    printf("����˹����ģʽѡ��");

    setColor(12);
    setPos(9, 15);
    printf("1.����ģʽ");
    setPos(18, 15);
    printf("2.����ģʽ");
    setPos(28, 15);
    printf("3.����ģʽ");
    setPos(36, 15);
    printf("4.�Զ�ģʽ");


    setPos(21, 22);
    setColor(3);
    printf("��ѡ�� 1 2 3 4");
    setColor(14);

    
    scanf_s("%d", &n);
    switch (n)
    {
    case 1:
        historyGrade = readHistory(1);
        system("cls");

        windowPrint(15, 0);
        printInfo(n);
        borderLeft(); //��߿�

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
        borderLeft(); //��߿�

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
        borderLeft(); //��߿�

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
        borderLeft(); //��߿�

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
        printf("������1-4֮�����!");
        _getch();
        system("cls");
        gameModeChoose();
    }

}


//29.����ʷ��¼
int readHistory(int mode)
{
    FILE* file;
    int grade;
    switch (mode) {
    case 1:
        fopen_s(&file, "grade1.txt", "r");

        if (file == NULL) {
            printf("�޷����ļ�\n");
            return -1;
        }

        if (fscanf_s(file, "%d", &grade) != 1) {
            printf("�ļ����ݲ�����Ҫ��\n");
            return -1;
        }

        fclose(file);

        break;
    case 2:
        fopen_s(&file, "grade2.txt", "r");

        if (file == NULL) {
            printf("�޷����ļ�\n");
            return -1;
        }

        if (fscanf_s(file, "%d", &grade) != 1) {
            printf("�ļ����ݲ�����Ҫ��\n");
            return -1;
        }

        fclose(file);

        break;

    case 3:
        fopen_s(&file, "grade3.txt", "r");

        if (file == NULL) {
            printf("�޷����ļ�\n");
            return -1;
        }

        if (fscanf_s(file, "%d", &grade) != 1) {
            printf("�ļ����ݲ�����Ҫ��\n");
            return -1;
        }

        fclose(file);

        break;
    case 4:
        fopen_s(&file, "grade4.txt", "r");

        if (file == NULL) {
            printf("�޷����ļ�\n");
            return -1;
        }

        if (fscanf_s(file, "%d", &grade) != 1) {
            printf("�ļ����ݲ�����Ҫ��\n");
            return -1;
        }

        fclose(file);
        break;
    }
    return grade;
}

//30.д��ʷ��¼
void writeHistory(int grade, int mode)
{
    FILE* file;
    switch (mode) {
    case 1:
    {
        fopen_s(&file, "grade1.txt", "w");

        if (file == NULL) {
            printf("�޷����ļ�\n");
            return;
        }

        fprintf(file, "%d\n", grade); // д���������ļ���

        fclose(file);

        break;
    }
    case 2:
    {
        fopen_s(&file, "grade2.txt", "w");

        if (file == NULL) {
            printf("�޷����ļ�\n");
            return;
        }

        fprintf(file, "%d\n", grade); // д���������ļ���

        fclose(file);

        break;
    }
    case 3:
    {
        fopen_s(&file, "grade3.txt", "w");

        if (file == NULL) {
            printf("�޷����ļ�\n");
            return;
        }

        fprintf(file, "%d\n", grade); // д���������ļ���

        fclose(file);

        break;
    }
    case 4:
    {
        fopen_s(&file, "grade4.txt", "w");

        if (file == NULL) {
            printf("�޷����ļ�\n");
            return;
        }

        fprintf(file, "%d\n", grade); // д���������ļ���

        fclose(file);
        break;
    }
    }
}
