#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
int main()
{
	const float Pi = 3.1415926; // Pi常量
	int width = 800; // 画面宽度
	int height = 600; // 画面高度
	initgraph(width,height); // 新开一个画面
	setbkcolor(RGB(255,255,255)); // 背景为白色	
	setlinestyle(PS_SOLID,3); // 线宽为3，这样针看起来更明显

	float lineLength = 160; // 针的长度
	float xEnd,yEnd; // 针的终点位置坐标（针起始位置为圆心）
	float rotateSpeed = Pi/360; // 针的旋转速度
	int lineNum = 0;  // 在旋转的针的个数
	float Angles[1000]; // 浮点数数组，存储所有针的旋转角度，最多1000根针
	int i;

	BeginBatchDraw(); // 开始批量绘制
	while (1) // 重复循环
	{
		cleardevice(); // 以背景色清空背景
		setlinecolor(RGB(0,0,0)); // 设置针颜色为黑色
		line(0,height/2,lineLength,height/2); // 左边发射区域的一根针

		for (i=0;i<lineNum;i++) // 对所有旋转针进行遍历
		{
			Angles[i] = Angles[i] + rotateSpeed; // 角度增加
			if (Angles[i]>2*Pi) // 如果超过2*Pi，就减去2*Pi，防止角度数据无限增加
				Angles[i] = Angles[i] - 2*Pi; //
			xEnd = lineLength*cos(-Angles[i]) +width/2; // 计算针的末端坐标
			yEnd = lineLength*sin(-Angles[i]) +height/2;
			line(width/2,height/2,xEnd,yEnd); // 绘制一根针
		}

		if (kbhit()) // 如果按键
		{
			char input = _getch(); // 获得用户按键输入
			if (input==' ') // 如果为空格键
			{
				lineNum++; // 针的个数加1
				Angles[lineNum-1] = Pi; // 这根新增加针的初始角度
				xEnd = lineLength*cos(-Angles[lineNum-1]) +width/2; //新增针的末端坐标
				yEnd = lineLength*sin(-Angles[lineNum-1]) +height/2;	 		
				line(width/2,height/2,xEnd,yEnd); // 绘制出这根新增加的针
			}
		}

		setlinecolor(HSVtoRGB(0,0.9,0.8)); // 设置圆盘线条颜色为红色
		circle(width/2,height/2,60); // 绘制中间的圆盘
		FlushBatchDraw(); // 批量绘制
		Sleep(10); // 暂停10毫秒
	}
	closegraph();  // 关闭画面
	return 0;
}