#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(800,600); // 打开一个窗口
	setbkcolor(WHITE); // 设置背景颜色为白色
	cleardevice();  // 以背景颜色清空画布
	while (1)
	{
		MOUSEMSG m;		 //定义鼠标消息
		if (MouseHit())   // 如果有鼠标消息
		{
			m = GetMouseMsg();  	 // 获得鼠标消息
			if (m.uMsg == WM_LBUTTONDOWN) // 如果按下鼠标左键
			{
				// 在鼠标点击位置画一个红色圆圈
				setfillcolor(RED);
				fillcircle(m.x,m.y,30);
			}
		}
	}
	return 0;
}