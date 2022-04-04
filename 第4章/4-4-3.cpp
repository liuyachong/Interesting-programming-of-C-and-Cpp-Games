#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600,600); // 打开一个600*600的窗口
	setbkcolor(RGB(255,255,255)); // 设置背景颜色为白色
	cleardevice();  // 以背景颜色清空画布
	int radius; // 圆半径
	for (radius=255;radius>0;radius=radius-10) // 画出一些同心圆
	{
		setlinecolor(RGB(radius,0,0));// 设置线条颜色
		circle(300,300,radius); // 以radius为半径画圆
	}
	_getch();  // 暂停，等待按键输入
	return 0;
}