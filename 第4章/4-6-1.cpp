#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // 圆周率Pi
	initgraph(600,600); // 打开一个600*600的窗口
	setbkcolor(RGB(255,255,255)); // 设置背景颜色为白色
	cleardevice();  // 以背景颜色清空画布

	int centerX = 300; // 圆心坐标
	int centerY = 300;
	int radius = 200; // 圆半径
	int left = centerX - radius; // 圆外切矩形左上角x坐标
	int top = centerY - radius; // 圆外切矩形左上角y坐标
	int right = centerX + radius; // 圆外切矩形右下角x坐标
	int bottom = centerY + radius; // 圆外切矩形右下角y坐标	

	int i;
	int step = 10;
	COLORREF  color; // 定义颜色变量
	for (i=0;i<360;i=i+step) // 绕着旋转一周，绘制扇形区域
	{
		color = HSVtoRGB(i,1,1); // HSV设置的颜色
		setfillcolor(color);// 设置填充颜色为color
		solidpie(left,top,right,bottom,i*Pi/180,(i+step)*Pi/180); // 画填充扇形
	}
	_getch();  // 暂停，等待按键输入
	return 0;
}