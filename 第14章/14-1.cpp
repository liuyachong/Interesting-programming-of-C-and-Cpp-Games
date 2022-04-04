#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"
#define  WIDTH 800  
#define  HEIGHT 600

class Player  // 玩家控制的游戏角色类
{
public:
	IMAGE im_show;  // 当前时刻要显示的图像
	float x_left,y_bottom; // 这两个坐标，因为只要用这两个和地面碰撞就行了
	float vx,vy; // 速度
	float width,height; // 图片的宽度、高度

	void draw()// 显示相关信息	
	{
		putimagePng(x_left,y_bottom-height,&im_show);  // 游戏中显示角色
	}

	void initialize() // 初始化
	{
		loadimage(&im_show, _T("standright.png")); // 导入向右站立图片
		width = im_show.getwidth(); // 获得图像的宽、高，所有动画图片大小一样
		height = im_show.getheight();
		updateXY(WIDTH/2,HEIGHT/2); // 开始将角色放在画面中间
		vx = 10; // 设置初速度
		vy = 10;
	}

	void updateXY(float mx,float my) // 根据输入，更新玩家坐标
	{
		x_left = mx;
		y_bottom = my;
	}
};

// 一些全局变量
IMAGE im_land;  // 地面图像
IMAGE im_bk;  // 背景图像
Player player;  // 定义玩家控制的游戏角色对象

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
}

void updateWithoutInput() // 和输入无关的更新
{
}

void updateWithInput() // 和输入有关的更新
{
	if(kbhit() )  // 如果按键
	{
		char input = getch(); // 获取按键
		if (input=='a') // 向左
			player.x_left -= player.vx;
		if (input=='d') // 向右
			player.x_left += player.vx;
		if (input=='w') // 向上
			player.y_bottom -= player.vy;
		if (input=='s') // 向下
			player.y_bottom += player.vy; 
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
