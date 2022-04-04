#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
int main()
{
	int width = 600; // 窗口宽度
	int height = 600; // 窗口高度
	initgraph(width,height); // 新开一个窗口
	setbkcolor(RGB(255,255,255)); // 背景颜色为白色
	cleardevice(); // 以背景颜色清空背景
	srand(time(0));  // 随机种子函数

	int xArray[100]; // 数组存储所有圆心的x坐标
	int yArray[100]; // 数组存储所有圆心的y坐标 
	int rArray[100]; // 数组存储所有圆的半径 
	int rmin = 8; // 圆的最小半径
	int rmax = 50; // 圆的最大半径
	int circleNum = 0; // 生成的圆的个数
	float x,y,r; // 新增圆的圆心坐标、半径

	while (circleNum<100) // 当圆的个数小于100时，循环运行
	{
		x = rand() % width; // 新圆的圆心x坐标
		y = rand() % height; // 新圆的圆心y坐标
		r = rand() % (rmax-rmin+1) + rmin; // 新圆的半径

		xArray[circleNum] = x; // 把新圆的圆心坐标添加到数组中
		yArray[circleNum] = y; //
		rArray[circleNum] = r; // 把新圆的半径添加到数组中
		circleNum++; // 圆的个数+1

		setlinecolor(RGB(0,0,0)); // 设置线条颜色
		setfillcolor(RGB(255,255,0)); // 设置填充颜色颜色
		fillcircle(x,y,r); // /绘制新圆

		Sleep(100); // 暂停100毫秒
	}

	_getch();	// 等待按键输入
	closegraph();  // 关闭窗口
	return 0;
}