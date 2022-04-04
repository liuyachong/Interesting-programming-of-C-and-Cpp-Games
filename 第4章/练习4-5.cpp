#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(750,500); // 新开画面
	setbkcolor(RGB(255,255,255)); // 背景白色
	cleardevice();
	int x,xStart,xEnd; // x起始、终止坐标
	int c,cStart,cEnd; //  起始颜色、终止颜色
	xStart = 50; // x起始坐标为50

	while (xStart<600) // 当x起始坐标小于600时
	{
		xEnd = xStart+50; // 这一段的x终止坐标+50，也就是画一共50像素的块
		cStart = 255; // 初始为全紫色
		cEnd = 128; //  最后为暗紫色
		for (x=xStart;x<xEnd;x++) // 渐变颜色，绘制这么多根线条，绘制紫色过渡区域 
		{
			c = (x-xStart)*(cEnd-cStart)/(xEnd-xStart)+cStart; // 
			setlinecolor(RGB(c,0,c)); // 设定颜色 
			line(x, 50, x, 100); // 第一大行
			line(x, 250, x, 300); // 第三大行
		}

		xStart = xEnd;  
		xEnd = xStart+100; 
		cStart = 0; 
		cEnd = 255;  
		for (x=xStart;x<xEnd;x++) // 绘制多根线条，黑色到黄色渐变区域
		{
			c = (x-xStart)*(cEnd-cStart)/(xEnd-xStart)+cStart; // 
			setlinecolor(RGB(c,c,0)); // 设定颜色
			line(x, 50, x, 100); // 第一大行 
			line(x, 250, x, 300); //  第三大行
		}		
		xStart = xEnd + 20; // 还隔了一点白色区域
	} // 循环，继续绘制下面一段

	xStart = 50; // 下面反向绘制，第二大行、第四大行的图案
	while (xStart<600) // 
	{
		xEnd = xStart+100; 
		cStart = 255;  
		cEnd = 0;
		for (x=xStart;x<xEnd;x++)  
		{
			c = (x-xStart)*(cEnd-cStart)/(xEnd-xStart)+cStart;  
			setlinecolor(RGB(c,c,0)); 
			line(x, 150, x, 200);  
			line(x, 350, x, 400); 
		}

		xStart = xEnd; 
		xEnd = xStart+50; 
		cStart = 128; 
		cEnd = 255; 
		for (x=xStart;x<xEnd;x++) 
		{
			c = (x-xStart)*(cEnd-cStart)/(xEnd-xStart)+cStart; 
			setlinecolor(RGB(c,0,c)); 
			line(x, 150, x, 200); 
			line(x, 350, x, 400);  
		}
		xStart = xEnd + 20; 
	}	

	_getch(); 
	closegraph(); 
	return 0;
}