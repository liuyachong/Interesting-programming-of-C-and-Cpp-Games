#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
int main()
{
	const float Pi = 3.1415926; // Pi常量
	int width = Pi*200; // 画面宽度
	int height = 200; // 画面高度
	initgraph(width,height); // 新开一个画面
	setbkcolor(RGB(255,255,255)); // 背景为白色	
	cleardevice(); // 以背景色清空背景
	setlinecolor(RGB(0,0,0));

	float x;
	float step = Pi/360; 
	for (x=0;x<=2*Pi;x=x+step) 
	{
		float x0 = x*width/(2*Pi);
		float x1 = (x+step)*width/(2*Pi);
		float y0 = height/2 - sin(x)*height/2;
		float y1 = height/2 - sin(x+step)*height/2;
		line(x0,y0,x1,y1); // 画出前后两个采样点之间的连线
	}

	_getch();
	closegraph(); 
	return 0;
}