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

int worm_body[50][3] = {0}; //지렁이의 최대 개수와 2개의 좌표,상태를 가지는 배열.2차원 요소는 각각 지렁이의 몸 한개를 차지하며 1차원 요소 [0],[1]은 x,y 이고 [2]는 상태
// 아래는 맵을 그리기 위한 배열
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
int food[22][46] = {0}; //먹이 좌표 배열.
int key = -1; // 키보드 입력을 담는 변수.
int tail = 0; // 몸통의 끝부분이 꼬리인지 판단하는데 쓰일 변수.
int last_key = -1; // 반대방향 화살표 키의 입력을 방지하는데 쓰일 변수.
int over = -1; // 게임종료 조건에 쓰일 변수.
int cnt = 0; // Sleep 함수와 함께 사용하여 시간이 지남에따라 아이템이 랜덤하게 생성되는 기능에 쓰일 변수.
int l = 0;   // 길이를 담는 변수.
int sl = 26; // 시작위치.

void gotoxy(int x, int y); //콘솔창의 커서를 입력변수 x,y에 따라 움직여주는 함수.
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
} CURSOR_TYPE; //커서 숨기는 함수에 사용되는 열거형

void setcursortype(CURSOR_TYPE c) //커서를 숨겨주는 함수
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
    setcursortype(NOCURSOR); //커서를 없앤다.
    srand(time(NULL));      
    // 지렁이의 초기 위치,길이를 설정해준다.
    worm_body[0][0] = 29;
    worm_body[0][1] = 15;
    worm_body[0][2] = HEAD;
    worm_body[1][0] = 28;
    worm_body[1][1] = 15;
    worm_body[1][2] = BODY;
    worm_body[2][0] = 27;
    worm_body[2][1] = 15;
    worm_body[2][2] = BODY;
    //아이템을 먹으면 생성될 몸통에 대한 위치를 지정해준다.
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

        if (kbhit())// 진행방향의 반대방향 화살표키 입력을 방지한다.
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
    COORD pos = {x * 2, y}; //콘솔 화면 버퍼에서 문자 셀의 좌표를 정의함.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw_map()//맵을 그려주는 함수.
{
    int i, j;

    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 48; j++)
        {
            if (wall[i][j] == 1)
            {
                gotoxy(j + 6, i + 3);
                printf("▩");
            }
        }
    }
}

void move(int d)// 키보드 입력에 따라 지렁이의 진행방향이 달라지는 것을 구현한 함수.
{
    int i;

    switch (d) 
    {
    case LEFT:
        gotoxy(worm_body[0][0] - 1, worm_body[0][1]);
        printf("●");
        body_move();
        worm_body[0][0] -= 1;
        Sleep(100);
        cnt++;
        break;
    case RIGHT:
        gotoxy(worm_body[0][0] + 1, worm_body[0][1]);
        printf("●");
        body_move();
        worm_body[0][0] += 1;
        Sleep(100);
        cnt++;
        break;
    case UP:
        gotoxy(worm_body[0][0], worm_body[0][1] - 1);
        printf("●");
        body_move();
        worm_body[0][1] -= 1;
        Sleep(100);
        cnt++;
        break;
    case DOWN:
        gotoxy(worm_body[0][0], worm_body[0][1] + 1);
        printf("●");
        body_move();
        worm_body[0][1] += 1;
        Sleep(100);
        cnt++;
        break;
    }
}

void body_move()//지렁이가 움직이는 것을 구현한 함수.
{
    int i;

    tail = 1;

    for (i = 49; i > 0; i--)
    {
        if (worm_body[i][2] == BODY)
        {
            gotoxy(worm_body[i - 1][0], worm_body[i - 1][1]); // 꼬리가 따라 움직이도록 한다.
            printf("○");

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

void draw_worm() //맵에 지렁이를 나타나게 해주는 함수.
{
    int i, j;

    for (i = 0; i < 50; i++)
    {
        if (worm_body[i][2] == HEAD)
        {
            gotoxy(worm_body[i][0], worm_body[i][1]);
            printf("●");
        }
        else if (worm_body[i][2] == BODY)
        {
            gotoxy(worm_body[i][0], worm_body[i][1]);
            printf("○");
        }
        else if (worm_body[i][2] == DEAD)
        {
            gotoxy(worm_body[i][0], worm_body[i][1]);
            printf("  ");
        }
    }
}

void food_make() // 아이템의 위치를 설정해주는 함수.
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

void food_draw() // 설정된 위치에 아이템 생성.
{
    int i, j;
    for (i = 0; i < 22; i++)
    {
        for (j = 0; j < 46; j++)
        {
            if (food[i][j] == 1)
            {
                gotoxy(j + 7, i + 4);
                printf("♡");
            }
        }
    }
}

void eat() // 아이템 획득시 몸이 길어지는 기능을 구현한 함수
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

void crush_check() //충돌 검사 함수.
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