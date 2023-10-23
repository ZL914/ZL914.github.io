#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#define SNAKE_NUM 500//蛇的最大节数 

//蛇的方向 
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//蛇的结构 
struct Snake
{
	int size;//节数 
	int dir;//方向 
	int speed;//速度 
	POINT coor[SNAKE_NUM];//坐标 
}snake;

//食物结构 
struct Food
{
	int x;
	int y;
	int r;
	bool flag;//食物是否被吃 
	DWORD color;//食物颜色 
}food;
void GameInit()//数据初始化 
{
	initgraph(640, 480);//init初始graph窗口 
	srand(GetTickCount());//系统开机时间获取随机数 
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = snake.size - 1; i >= 0; i--)
	{
		snake.coor[i].x = 40 - i * 10;
		snake.coor[i].y = 10;
	}

	//初始化食物，产生一个随机数种子 
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}

void GameDraw()
{
	BeginBatchDraw();//双缓冲绘图 
	setbkcolor(RGB(28, 115, 119));//背景颜色 
	cleardevice();
	//绘制蛇 
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}

	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}

//移动蛇 
void snakeMove()
{
	//身体跟着头移动 
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{

	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y + 10 <= 0)
		{
			snake.coor[0].y = 480;//蛇穿墙 
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y + 10 >= 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x + 10 <= 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x + 10 >= 640)
		{
			snake.coor[0].x = 0;
		}
		break;
	default:
		break;
	}

}

//按键改变蛇的方向 
void keyControl()
{
	if (_kbhit())//判断有没有按键 
	{
		char key = _getch();
		switch (key)
		{
		case 'W':
		case 'w':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}

			break;
		case 'S':
		case 's':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}

			break;
		case 'A':
		case 'a':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}

			break;
		case 'D':
		case 'd':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}

			break;
		}
	}

}

void Eatfood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)//碰到食物即吃 
	{
		food.flag = false;//避免重复吃食物 
		snake.size++;//蛇变长 

	}
	//如果食物消失，则重新生成食物 
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}


int main()
{

	GameInit();

	while (1)
	{
		GameDraw();
		keyControl();
		snakeMove();
		Eatfood();
		Sleep(200);
	}
	return 0;
}