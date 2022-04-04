#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // 圆周率Pi
	initgraph(800,600); // 打开一个窗口
	setbkcolor(RGB(128,128,128)); // 设置背景颜色为灰色
	cleardevice();  // 以背景颜色清空画布

	int centerX,centerY; // 圆心坐标
	int radius; // 圆半径	
	int i;
	float offset;  // 同一半径各组扇形之间的角度偏移量
	float totalOffset = 0; // 不同半径之间的角度偏移量

	for (centerX = 100;centerX<800;centerX=centerX+200) // 对圆心x坐标循环
	{
		for (centerY = 100;centerY<600;centerY=centerY+200) // 对圆心y坐标循环
		{
			float h = rand()%180; // 随机色调
			COLORREF  color1 = HSVtoRGB(h,0.9,0.8); // 色调1生成的颜色1
			COLORREF  color2 = HSVtoRGB(h+180,0.9,0.8); // 色调2生成的颜色2
			for (radius=100;radius>0;radius=radius-20) // 半径从大到小绘制
			{
				int left = centerX - radius; // 圆外切矩形左上角x坐标
				int top = centerY - radius; // 圆外切矩形左上角y坐标
				int right = centerX + radius; // 圆外切矩形右下角x坐标
				int bottom = centerY + radius; // 圆外切矩形右下角y坐标	
				for (i=0;i<20;i++) // 绕着旋转一周，绘制扇形区域
				{
					offset = i*Pi/10 + totalOffset; // 各组扇形之间偏移的角度
					setfillcolor(color1); // 色调1生成的颜色1
					solidpie(left,top,right,bottom,offset,2*Pi/60+offset); 
					setfillcolor(RGB(255,255,255));// 设置填充颜色为白色
					solidpie(left,top,right,bottom,2*Pi/60+offset,3*Pi/60+offset); 
					setfillcolor(color2); // 色调2生成的颜色2
					solidpie(left,top,right,bottom,3*Pi/60+offset,5*Pi/60+offset); 
					setfillcolor(RGB(0,0,0));// 设置填充颜色为黑色
					solidpie(left,top,right,bottom,5*Pi/60+offset,6*Pi/60+offset); 
				}
				totalOffset = totalOffset + Pi/20; // 不同半径间角度偏移量为Pi/20
			}
		}
	}

	_getch();  // 暂停，等待按键输入
	return 0;
}