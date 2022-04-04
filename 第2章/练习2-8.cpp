#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float x,y,vx,vy,g; // 定义一些变量
	x = 100; // 小球的x坐标
	y = 200; // 小球的y坐标
	vx = 8; // 小球x方向速度
	vy = 0; // 小球y方向速度
	g = 0.5; // 小球加速度，y方向
	initgraph(600, 600); // 初始游戏窗口画面，宽600，高600
	while(1) // 一直循环运行
	{		
		cleardevice(); // 清除掉之前绘制的内容
		vy = vy+g; // 利用加速度g更新vy速度
		x = x + vx; // 利用x方向速度vx更新x坐标
		y = y+vy; // 利用y方向速度vy更新y坐标
		if (y>=580) // 当碰到地面时
		{
			vx = 0.98*vx; // x方向速度受阻尼影响变小
			vy = -0.95*vy; // y方向速度改变方向，并受阻尼影响变小
		}
		if (y>580) // 防止小球越过地面
			y = 580;
		if (x>=580) // 碰到右边墙，小球x方向速度反向
			vx = -vx;
		if (x<=20) // 碰到左边墙，小球x方向速度反向
			vx = -vx;
		fillcircle(x, y, 20); // 在坐标(x,y)处画一个半径为20的圆
		Sleep(10); // 暂停10毫秒
	}
	_getch(); // 等待按键
	closegraph(); // 关闭窗口
	return 0;
}
