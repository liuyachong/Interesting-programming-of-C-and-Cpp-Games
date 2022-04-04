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

	int i;
	float offset; 
	for (i=0;i<20;i++) // 绕着旋转一周，绘制扇形区域
	{
		offset = i*Pi/10; // 各组扇形之间偏移的角度
		setfillcolor(RGB(0,240,220));// 设置填充颜色为青色
		solidpie(left,top,right,bottom,offset,2*Pi/60+offset); // 画填充扇形
		setfillcolor(RGB(255,255,255));// 设置填充颜色为白色
		solidpie(left,top,right,bottom,2*Pi/60+offset,3*Pi/60+offset); // 画填充扇形
		setfillcolor(RGB(200,0,0));// 设置填充颜色为红色
		solidpie(left,top,right,bottom,3*Pi/60+offset,5*Pi/60+offset); // 画填充扇形
		setfillcolor(RGB(0,0,0));// 设置填充颜色为黑色
		solidpie(left,top,right,bottom,5*Pi/60+offset,6*Pi/60+offset); // 画填充扇形
	}
	_getch();  // 暂停，等待按键输入
	return 0;
}