#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
int main()
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
	int i;

	while (circleNum<1000) // 当圆的个数小于100时，循环运行
	{
		isNewCircleOK = 0; // 假设开始不OK

		while (isNewCircleOK==0) // 当新生成的圆不Ok时，重复生成新圆进行比较
		{
			x = rand() % width; // 新圆的圆心x坐标
			y = rand() % height; // 新圆的圆心y坐标
			r = rand() % (rmax-rmin+1) + rmin; // 新圆的半径

			for (i=0;i<circleNum;i++)   // 对已有圆遍历
			{
				float dist2 = (xArray[i] - x)*(xArray[i] - x) + (yArray[i] - y)*(yArray[i] - y);
				float r2 = (rArray[i]+r) * (rArray[i]+r);
				if (dist2<r2) // 如果已有圆和新圆相交
				{
					break;  // 跳出循环，此时i<circleNum
				}
			}
			if (i==circleNum) // 如果上面for语句都不跳出，说明i等于circleNum
			{
				isNewCircleOK = 1; //  这个新生成的圆和已有圆都不想交
			}
		}
		xArray[circleNum] = x; // 把新圆的圆心坐标添加到数组中
		yArray[circleNum] = y; //
		rArray[circleNum] = r; // 把新圆的半径添加到数组中
		circleNum++; // 圆的个数+1

		setlinecolor(RGB(0,0,0)); // 设置线条颜色
		setfillcolor(RGB(255,255,0)); // 设置填充颜色颜色
		fillcircle(x,y,r); // /绘制新圆

		Sleep(10); // 暂停若干毫秒
	}

	_getch();	// 等待按键输入
	closegraph();  // 关闭窗口
	return 0;
}