#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
int main()
{
	initgraph(600,400); // 新开一个窗口
	setbkcolor(RGB(255,255,255)); // 背景颜色为白色
	setbkmode(TRANSPARENT); // 透明显示文字
	settextcolor(BLACK);  // 设置字体颜色
	settextstyle(60, 0, _T("宋体")); // 设置文字大小、字体	
	TCHAR str[20]; // 定义字符数组
	clock_t start, now; // 用于计时的变量
	start = clock(); // 记录当前运行时刻

	while (1)// 循环
	{
		now = clock(); // 获得当前时刻
		// 计算程序一共运行了多少秒
		double duration =( double(now - start) / CLOCKS_PER_SEC); 
		_stprintf(str, _T("程序运行了%d秒"),  int(duration)); //转换为字符串
		cleardevice(); // 清屏
		outtextxy(100, 150, str); // 输出文字
		Sleep(20); // 暂停20毫秒
	}	
	return 0;
}