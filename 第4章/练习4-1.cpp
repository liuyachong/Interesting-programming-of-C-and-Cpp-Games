#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // 圆周率Pi
	initgraph(600,600); // 打开一个600*600的窗口
	setbkcolor(RGB(128,128,128)); // 设置背景颜色为灰色
	cleardevice();  // 以背景颜色清空画布
	
	int centerX = 300; // 圆心坐标
	int centerY = 300;
	int radius = 200; // 圆半径
	int left = centerX - radius; // 圆外切矩形左上角x坐标
	int top = centerY - radius; // 圆外切矩形左上角y坐标
	int right = centerX + radius; // 圆外切矩形右下角x坐标
	int bottom = centerY + radius; // 圆外切矩形右下角y坐标	

	setfillcolor(RGB(0,255,0));// 设置填充颜色为绿色
	solidpie(left,top,right,bottom,0*Pi/2,1*Pi/2); // 画填充扇形
	setfillcolor(RGB(255,255,255));// 设置填充颜色为白色
	solidpie(left,top,right,bottom,1*Pi/2,2*Pi/2); // 画填充扇形
	setfillcolor(RGB(255,0,0));// 设置填充颜色为红色
	solidpie(left,top,right,bottom,2*Pi/2,3*Pi/2); // 画填充扇形
	setfillcolor(RGB(0,0,0));// 设置填充颜色为黑色
	solidpie(left,top,right,bottom,3*Pi/2,4*Pi/2); // 画填充扇形

	_getch();  // 暂停，等待按键输入
	return 0;
}