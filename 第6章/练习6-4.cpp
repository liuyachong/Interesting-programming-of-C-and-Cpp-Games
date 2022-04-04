#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// 求解两个点之间的距离
float Dist2Points(float x1,float y1,float x2,float y2)
{
	float result;
	result	= sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return result;
}

// 判断两个圆是否相交
int isTwoCirclesIntersect(float x1,float y1,float r1,float x2,float y2,float r2)
{
	if (Dist2Points(x1,y1,x2,y2)<r1+r2)
		return 1;
	return 0;
}

// 填充黄色圆绘制
void DrawCircles1(float x,float y,float r)
{
	setlinecolor(RGB(0,0,0));
	setfillcolor(RGB(255,255,0));
	fillcircle(x,y,r);
}

// 填充随机颜色圆绘制
void DrawCircles2(float x,float y,float r)
{
	float h = rand()%360;
	COLORREF  color = HSVtoRGB(h,0.6,0.8);
	setlinecolor(RGB(255,255,255));
	setfillcolor(color);
	fillcircle(x,y,r);
}

// 填充随机颜色同心圆绘制
void DrawCircles3(float x,float y,float r)
{
	while (r>0)
	{
		float h = rand()%360;
		COLORREF  color = HSVtoRGB(h,0.6,0.8);
		setlinecolor(RGB(255,255,255));
		setfillcolor(color);
		fillcircle(x,y,r);
		r=r-5;
	}
}

// 随机颜色同心圆线条绘制
void DrawCircles4(float x,float y,float r)
{
	while (r>0)
	{
		float h = rand()%360;
		COLORREF  color = HSVtoRGB(h,0.9,0.8);
		setlinecolor(color);
		circle(x,y,r);
		r=r-5;
	}
}

int main() // 主函数
{
	int width = 600; // 窗口宽度
	int height = 600; // 窗口高度
	initgraph(width,height); // 新开一个窗口
	setbkcolor(RGB(255,255,255)); // 背景颜色为白色
	cleardevice(); // 以背景颜色清空背景
	srand(time(0));  // 随机种子函数

	int xArray[1000]; // 数组存储所有圆心的x坐标
	int yArray[1000]; // 数组存储所有圆心的y坐标 
	int rArray[1000]; // 数组存储所有圆的半径 
	int rmin = 8; // 圆的最小半径
	int rmax = 50; // 圆的最大半径
	int circleNum = 0; // 生成的圆的个数
	float x,y,r; // 新增圆的圆心坐标、半径
	int isNewCircleOK; // 用于判断新生成的圆是否可以了
	int i,j;
	int drawMode = 3; // 用于设定4种不同的绘制模式，开始设为3

	while (circleNum<1000) // 当圆的个数小于100时，循环运行
	{
		isNewCircleOK = 0; // 假设开始不OK

		while (isNewCircleOK==0) // 当新生成的圆不Ok时，重复生成新圆进行比较
		{
			if (kbhit()) // 当按键时
			{
				char input = _getch(); // 获得用户按键
				if (input==' ') // 空格键
				{
					circleNum = 0; // 圆的个数为0，相当于画面清除所有已有的圆圈
					cleardevice(); // 清屏
				}
				if (input=='1') // 1，设置为绘图模式1
					drawMode = 1;
				if (input=='2') // 2，设置为绘图模式2 
					drawMode = 2;
				if (input=='3') // 3，设置为绘图模式3 
					drawMode = 3;
				if (input=='4') // 4，设置为绘图模式4 
					drawMode = 4;
			}

			x = rand() % width; // 新圆的圆心x坐标
			y = rand() % height; // 新圆的圆心y坐标
			r = rmin; // 新圆的半径开始设为最小半径

			for (i=0;i<circleNum;i++)   // 对已有圆遍历
				if (isTwoCirclesIntersect(xArray[i],yArray[i],rArray[i],x,y,r))
					break; // 如果已有圆和新圆相交,跳出循环，此时i<circleNum

			if (i==circleNum) // 如果上面for语句都不跳出，说明i等于circleNum
				isNewCircleOK = 1; //  这个新生成的圆和已有圆都不相交
		}

		isNewCircleOK = 0; // 继续设为不OK，下面要让这个新圆的半径最大
		while (isNewCircleOK==0 && r<rmax) // 当不ok，并且新圆的半径小于最大半径时
		{
			r++; // 让半径+1
			for (j=0;j<circleNum;j++) // 对所有旧圆遍历
			{
				if (isTwoCirclesIntersect(xArray[j],yArray[j],rArray[j],x,y,r))
				{
					isNewCircleOK = 1; // 一旦和一个旧圆相交，这时新圆Ok
					break; // 因为新圆半径已经达到最大的情况，这时跳出循环
				}
			}
		}

		xArray[circleNum] = x; // 把新圆的圆心坐标添加到数组中
		yArray[circleNum] = y; //
		rArray[circleNum] = r; // 把新圆的半径添加到数组中
		circleNum++; // 圆的个数+1

		// 根据不同绘图模式进行绘制		
		if (drawMode==1)
			DrawCircles1(x,y,r);
		if (drawMode==2)
			DrawCircles2(x,y,r);
		if (drawMode==3)
			DrawCircles3(x,y,r);
		if (drawMode==4)
			DrawCircles4(x,y,r);

		Sleep(10); // 暂停若干毫秒
	}

	_getch();	// 等待按键输入
	closegraph();  // 关闭窗口
	return 0;
}