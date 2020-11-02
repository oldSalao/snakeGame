#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <winbase.h>
#include <stdlib.h>
#include <time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define DEAD 0
#define HEAD 1
#define BODY 2
#define WALL 3

int worm_body[50][3] = {0}; //�������� �ִ� ������ 2���� ��ǥ,���¸� ������ �迭.2���� ��Ҵ� ���� �������� �� �Ѱ��� �����ϸ� 1���� ��� [0],[1]�� x,y �̰� [2]�� ����
// �Ʒ��� ���� �׸��� ���� �迭
int wall[24][48] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
int food[22][46] = {0}; //���� ��ǥ �迭.
int key = -1; // Ű���� �Է��� ��� ����.
int tail = 0; // ������ ���κ��� �������� �Ǵ��ϴµ� ���� ����.
int last_key = -1; // �ݴ���� ȭ��ǥ Ű�� �Է��� �����ϴµ� ���� ����.
int over = -1; // �������� ���ǿ� ���� ����.
int cnt = 0; // Sleep �Լ��� �Բ� ����Ͽ� �ð��� ���������� �������� �����ϰ� �����Ǵ� ��ɿ� ���� ����.
int l = 0;   // ���̸� ��� ����.
int sl = 26; // ������ġ.

void gotoxy(int x, int y); //�ܼ�â�� Ŀ���� �Էº��� x,y�� ���� �������ִ� �Լ�.
void title();
void worm();
void draw_worm();
void move(int d);
void draw_map();
void body_move();
void game_over();
void game_over_ment();
void food_make();
void food_draw();
void eat();
void crush_check();

typedef enum
{
    NOCURSOR,
    SOLIDCURSOR,
    NORMALCURSOR
} CURSOR_TYPE; //Ŀ�� ����� �Լ��� ���Ǵ� ������

void setcursortype(CURSOR_TYPE c) //Ŀ���� �����ִ� �Լ�
{
    CONSOLE_CURSOR_INFO Curinfo;
    switch (c)
    {
    case NOCURSOR:
        Curinfo.dwSize = 1;
        Curinfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        Curinfo.dwSize = 100;
        Curinfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        Curinfo.dwSize = 20;
        Curinfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
}

int main()
{
    int i, j;
    setcursortype(NOCURSOR); //Ŀ���� ���ش�.
    srand(time(NULL));      
    // �������� �ʱ� ��ġ,���̸� �������ش�.
    worm_body[0][0] = 29;
    worm_body[0][1] = 15;
    worm_body[0][2] = HEAD;
    worm_body[1][0] = 28;
    worm_body[1][1] = 15;
    worm_body[1][2] = BODY;
    worm_body[2][0] = 27;
    worm_body[2][1] = 15;
    worm_body[2][2] = BODY;
    //�������� ������ ������ ���뿡 ���� ��ġ�� �������ش�.
    for (i = 3; i < 50; i++)
    {
        worm_body[i][0] = sl;
        worm_body[i][1] = 15;
        worm_body[i][2] = DEAD;
        sl--;
    }

    draw_worm();

    while (1)
    {
        draw_map();
        food_make();
        food_draw();

        if (kbhit())// ��������� �ݴ���� ȭ��ǥŰ �Է��� �����Ѵ�.
        {
            key = getch();
            if (key == 0 || key == 224)
            {
                key = getch();
            }

            if (key != UP && key != DOWN && key != RIGHT && key != LEFT)
            {
                continue;
            }
            else if (last_key == LEFT && key == RIGHT)
            {
                continue;
            }
            else if (last_key == RIGHT && key == LEFT)
            {
                continue;
            }
            else if (last_key == UP && key == DOWN)
            {
                continue;
            }
            else if (last_key == DOWN && key == UP)
            {
                continue;
            }

            last_key = key;
        }

        move(last_key);
        eat();

        crush_check();

        if (over == 1)
        {
            break;
        }
    }
    game_over_ment();
}

void gotoxy(int x, int y)
{
    COORD pos = {x * 2, y}; //�ܼ� ȭ�� ���ۿ��� ���� ���� ��ǥ�� ������.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw_map()//���� �׷��ִ� �Լ�.
{
    int i, j;

    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 48; j++)
        {
            if (wall[i][j] == 1)
            {
                gotoxy(j + 6, i + 3);
                printf("��");
            }
        }
    }
}

void move(int d)// Ű���� �Է¿� ���� �������� ��������� �޶����� ���� ������ �Լ�.
{
    int i;

    switch (d) 
    {
    case LEFT:
        gotoxy(worm_body[0][0] - 1, worm_body[0][1]);
        printf("��");
        body_move();
        worm_body[0][0] -= 1;
        Sleep(100);
        cnt++;
        break;
    case RIGHT:
        gotoxy(worm_body[0][0] + 1, worm_body[0][1]);
        printf("��");
        body_move();
        worm_body[0][0] += 1;
        Sleep(100);
        cnt++;
        break;
    case UP:
        gotoxy(worm_body[0][0], worm_body[0][1] - 1);
        printf("��");
        body_move();
        worm_body[0][1] -= 1;
        Sleep(100);
        cnt++;
        break;
    case DOWN:
        gotoxy(worm_body[0][0], worm_body[0][1] + 1);
        printf("��");
        body_move();
        worm_body[0][1] += 1;
        Sleep(100);
        cnt++;
        break;
    }
}

void body_move()//�����̰� �����̴� ���� ������ �Լ�.
{
    int i;

    tail = 1;

    for (i = 49; i > 0; i--)
    {
        if (worm_body[i][2] == BODY)
        {
            gotoxy(worm_body[i - 1][0], worm_body[i - 1][1]); // ������ ���� �����̵��� �Ѵ�.
            printf("��");

            if (tail == 1)
            {
                gotoxy(worm_body[i][0], worm_body[i][1]);
                printf("  ");
                tail = 0;
            }
            worm_body[i][0] = worm_body[i - 1][0];
            worm_body[i][1] = worm_body[i - 1][1];
        }
    }
}

void draw_worm() //�ʿ� �����̸� ��Ÿ���� ���ִ� �Լ�.
{
    int i, j;

    for (i = 0; i < 50; i++)
    {
        if (worm_body[i][2] == HEAD)
        {
            gotoxy(worm_body[i][0], worm_body[i][1]);
            printf("��");
        }
        else if (worm_body[i][2] == BODY)
        {
            gotoxy(worm_body[i][0], worm_body[i][1]);
            printf("��");
        }
        else if (worm_body[i][2] == DEAD)
        {
            gotoxy(worm_body[i][0], worm_body[i][1]);
            printf("  ");
        }
    }
}

void food_make() // �������� ��ġ�� �������ִ� �Լ�.
{
    int fx, fy;
    if (cnt == 20)
    {
        fx = rand() % 46;
        fy = rand() % 22;
        food[fy][fx] = 1;
        cnt = 0;
    }
}

void food_draw() // ������ ��ġ�� ������ ����.
{
    int i, j;
    for (i = 0; i < 22; i++)
    {
        for (j = 0; j < 46; j++)
        {
            if (food[i][j] == 1)
            {
                gotoxy(j + 7, i + 4);
                printf("��");
            }
        }
    }
}

void eat() // ������ ȹ��� ���� ������� ����� ������ �Լ�
{
    int i, j;

    for (i = 0; i < 22; i++)
    {
        for (j = 0; j < 46; j++)
        {
            if (food[i][j] == 1)
            {
                if ((worm_body[0][0] == (j + 7)) && (worm_body[0][1] == (i + 4)))
                {
                    food[i][j] = 0;
                    gotoxy(j + 7, i + 4);
                    printf("  ");
                    l++;
                }
            }
        }
    }
    worm_body[l + 2][2] = BODY;
}

void crush_check() //�浹 �˻� �Լ�.
{
    int i, j;

    for (i = 1; i < 50; i++)
    {
        if ((worm_body[0][0] == worm_body[i][0])&&(worm_body[0][1]==worm_body[i][1])&&worm_body[i][2]==BODY)
        {
            game_over();
        }
    }

    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 48; j++)
        {
            if (wall[i][j] == 1)
            {
                if ((worm_body[0][0] == (j + 6)) && (worm_body[0][1] == (i + 3)))
                {
                    game_over();
                }
            }
        }
    }
}

void game_over()
{
    over = 1;
}

void game_over_ment()
{
    system("cls");
    gotoxy(27, 15);
    printf("Game Over.");
    system("pause>null");
    if (kbhit())
    {
        exit(0);
    }
}