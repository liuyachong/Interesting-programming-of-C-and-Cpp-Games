#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float y = 100; // 小球的y坐标
	float vy = 0; // 小球y方向速度
	float g = 0.5; // 小球加速度，y方向
	initgraph(600, 600); // 初始游戏窗口画面，宽600，高600
	while(1) // 一直循环运行
	{		
		cleardevice(); // 清除掉之前绘制的内容
		vy = vy+g; // 利用加速度g更新vy速度
		y = y+vy; // 利用y方向速度vy更新y坐标
		if (y>=580) // 当碰到地面时
			vy = -0.95*vy; // y方向速度改变方向，并受阻尼影响绝对值变小
		if (y>580) // 防止小球越过地面
			y = 580;
		fillcircle(300, y, 20); // 在坐标(300,y)处画一个半径为20的圆
		Sleep(10); // 暂停10毫秒
	}
	_getch(); // 等待按键
	closegraph(); // 关闭窗口
	return 0;
}
