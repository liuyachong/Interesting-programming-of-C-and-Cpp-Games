#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#define Width 600
#define Height 600

struct Ball // 定义小球结构体
{
	float x; // 小球的x坐标
	float y; // 小球的y坐标
	float vx; // 小球x方向速度
	float vy; // 小球y方向速度
	float r; // 小球半径
};

int main()
{
	Ball ball;  // 定义小球结构体变量
	ball.x = 100; // 小球的x坐标
	ball.y = 200; // 小球的y坐标
	ball.vx = 8; // 小球x方向速度
	ball.vy = 0; // 小球y方向速度
	ball.r = 20; // 小球半径
	float g = 0.5; // 重力加速度，y方向
	initgraph(Width, Height); // 初始游戏窗口画面
	while(1) // 一直循环运行
	{		
		cleardevice(); // 清除掉之前绘制的内容
		ball.vy = ball.vy + g; // 利用加速度g更新vy速度
		ball.x = ball.x + ball.vx; // 利用x方向速度vx更新x坐标
		ball.y = ball.y + ball.vy; // 利用y方向速度vy更新y坐标
		if (ball.y>=Height-ball.r) // 当碰到地面时
		{
			ball.vx = 0.98 * ball.vx; // x方向速度受阻尼影响变小
			ball.vy = -0.95 * ball.vy; // y方向速度改变方向，并受阻尼影响变小
		}
		if (ball.y>Height-ball.r) // 防止小球越过地面
			ball.y = Height-ball.r;
		if (ball.x>=Width-ball.r) // 碰到右边墙，小球x方向速度反向
			ball.vx = -ball.vx;
		if (ball.x<=ball.r) // 碰到左边墙，小球x方向速度反向
			ball.vx = -ball.vx;
		fillcircle(ball.x, ball.y, ball.r); // 在坐标(x,y)处画一个半径r的圆
		Sleep(15); // 暂停若干毫秒
	}
	_getch(); // 等待按键
	closegraph(); // 关闭窗口
	return 0;
}