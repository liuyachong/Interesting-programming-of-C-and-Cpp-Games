#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"
#include "Timer.h"
#define  WIDTH 800  
#define  HEIGHT 600

enum PlayerStatus // 枚举类型，游戏角色所有的可能状态
{
	standleft,standright,runleft,runright,jumpleft,jumpright,die
};

class Player  // 玩家控制的游戏角色类
{
public:
	IMAGE im_show;  // 当前时刻要显示的图像
	IMAGE im_standright; // 向右站立图像
	IMAGE im_standleft; // 向左站立图像
	PlayerStatus playerStatus; // 当前的状态

	float x_left,y_bottom; // 这两个坐标，因为只要用这两个和地面碰撞就行了
	float vx,vy; // 速度
	float width,height; // 图片的宽度、高度

	void draw()// 显示相关信息	
	{
		putimagePng(x_left,y_bottom-height,&im_show);  // 游戏中显示角色
	}

	void initialize() // 初始化
	{
		loadimage(&im_standright, _T("standright.png")); // 导入向右站立图片
		loadimage(&im_standleft, _T("standleft.png")); // 导入向左站立图片

		playerStatus = standright; // 初始为向右站立的游戏状态
		im_show = im_standright;  // 初始显示向右站立的图片
		width = im_standright.getwidth(); // 获得图像的宽、高，所有动画图片大小一样
		height = im_standright.getheight();

		updateXY(WIDTH/2,HEIGHT/2); // 开始将角色放在画面中间
		vx = 10; // 设置初速度
		vy = 10;
	}

	void updateXY(float mx,float my) // 根据输入，更新玩家坐标
	{
		x_left = mx;
		y_bottom = my;
	}

	void standStill() // 游戏角色默认为向左或向右静止站立
	{
		if (playerStatus == standleft)
		{
			im_show = im_standleft;
		}
		else if (playerStatus == standright)
		{
			im_show = im_standright;
		}
	}
};

// 一些全局变量
IMAGE im_land;  // 地面图像
IMAGE im_bk;  // 背景图像
Player player;  // 定义玩家控制的游戏角色对象
Timer timer;  // 用于精确延时

void startup()  // 初始化
{	
	player.initialize(); // 玩家角色初始化
	loadimage(&im_land, _T("land.png")); // 导入地面图片
	loadimage(&im_bk,  _T("landscape1.png")); // 导入背景图片

	initgraph(WIDTH,HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 显示
{
	putimage(-100, -100, &im_bk);	// 显示背景	
	putimage(WIDTH/2,HEIGHT/2,&im_land);  // 绘制一个地面
	player.draw();  // 显示玩家相关信息
	FlushBatchDraw(); // 批量绘制
	timer.Sleep(50); // 暂停若干毫秒
}

void updateWithoutInput() // 和输入无关的更新
{
}

void updateWithInput() // 和输入有关的更新
{
	player.standStill(); // 游戏角色默认为向左或向右静止站立

	if (kbhit()) // 当按键时，切换角色显示图片，更改位置
	{
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))  // 按下A键或左方向键
		{
			player.x_left -= player.vx; // 向左移动
			player.playerStatus = standleft; // 切换状态为向左站立
		}
		if (GetAsyncKeyState(VK_RIGHT)  || GetAsyncKeyState('D')) // 按下D键或右方向键
		{
			player.x_left += player.vx; // 向右移动
			player.playerStatus = standright; // 切换状态为向右站立
		}
		if (GetAsyncKeyState(VK_UP)  || GetAsyncKeyState('W'))    // 按下W键或上方向键
		{
			player.y_bottom -= player.vy; // 向上移动
		}
		if (GetAsyncKeyState(VK_DOWN)  || GetAsyncKeyState('S'))  // 按下S键或下方向键
		{
			player.y_bottom += player.vy; // 向下移动
		}
	}
}

int main() // 主函数
{
	startup();  	// 初始化
	while (1)       // 一直循环
	{
		show();  // 显示
		updateWithoutInput(); // 与输入无关的更新
		updateWithInput();    // 与输入有关的更新
	}
	return 0;
}