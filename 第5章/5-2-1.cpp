#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
int main()
{
	float Pi = 3.1415926;
	int width = 800; // 画面宽度
	int height = 600; // 画面高度
	initgraph(width,height); // 新开一个画面
	setbkcolor(RGB(255,255,255)); // 背景为白色
	cleardevice(); // 以背景色清空背景

	float lineLength = 160; // 针的长度
	float xEnd,yEnd; // 针的终点位置坐标（针起始位置为圆心）
	float angle = Pi/3; // 针的旋转角度

	setlinestyle(PS_SOLID,3); // 线宽为3，这样针看起来更明显
	setlinecolor(RGB(0,0,0)); // 设置针颜色为黑色
	xEnd = lineLength*cos(-angle) +width/2; // 计算针的末端坐标
	yEnd = lineLength*sin(-angle) +height/2;
	line(width/2,height/2,xEnd,yEnd); // 绘制一根针
	
	setlinecolor(HSVtoRGB(0,0.9,0.8)); // 设置圆盘线条颜色为红色
	circle(width/2,height/2,60); // 绘制中间的圆盘

	_getch();	
	closegraph(); 
	return 0;
}