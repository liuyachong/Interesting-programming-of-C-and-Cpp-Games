#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // 圆周率Pi
	initgraph(600,600); // 打开一个600*600的窗口
	int centerX = 300; // 圆心坐标
	int centerY = 300;
	int radius = 200; // 圆半径
	circle(centerX,centerY,radius); // 画出对应的圆边框
	int left = centerX - radius; // 圆外切矩形左上角x坐标
	int top = centerY - radius; // 圆外切矩形左上角y坐标
	int right = centerX + radius; // 圆外切矩形右下角x坐标
	int bottom = centerY + radius; // 圆外切矩形右下角y坐标	
	solidpie(left,top,right,bottom,Pi/6,Pi/3); // 画填充扇形，角度为Pi/6到Pi/3
	_getch();  // 暂停，等待按键输入
	closegraph();  // 关闭画面
	return 0;
}