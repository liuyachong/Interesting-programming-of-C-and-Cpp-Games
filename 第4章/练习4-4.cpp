#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600, 600);; // 打开一个窗口
	setbkcolor(YELLOW); // 设置背景颜色为黄色
	cleardevice();  // 以背景颜色清空画布
	setlinecolor(RGB(0,0,0));  // 设置线条为黑色
	int i;
	int step = 30;
	for(i=1; i<=19; i++)  // 画横线和竖线
	{
		line(i*step, 1*step, i*step,  19*step);
		line(1*step, i*step, 19*step, i*step);
	}
	_getch();  // 暂停，等待按键输入
	return 0;
}