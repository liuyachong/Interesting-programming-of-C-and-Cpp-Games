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
	int circleNum = 100; // 生成的圆的个数

	int i;
	for (i=0;i<circleNum;i++) // 生成circleNum个圆，把数据保存在数组中
	{
		xArray[i] = rand() % width; // 圆心的x坐标
		yArray[i] = rand() % height;// 圆心的y坐标
		rArray[i] = rand() % (rmax-rmin+1) + rmin; // 圆的半径
	}

	for (i=0;i<circleNum;i++) // 绘制出所有的圆
	{
		setlinecolor(RGB(0,0,0)); // 设置线条颜色
		setfillcolor(RGB(255,255,0)); // 设置填充颜色颜色
		fillcircle(xArray[i],yArray[i],rArray[i]); // 用数组存储的数据绘制圆
	}

	_getch();	// 等待按键输入
	closegraph();  // 关闭窗口
	return 0;
}