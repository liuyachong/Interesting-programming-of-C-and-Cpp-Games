#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600,350); // 新开一个窗口
	setbkcolor(RGB(255,255,255)); // 背景颜色为白色
	cleardevice(); // 以背景颜色清空背景	
	setbkmode(TRANSPARENT); // 透明显示文字

	settextcolor(RED);  // 设置字体颜色
	settextstyle(50, 0, _T("宋体")); // 设置文字大小、字体	
	outtextxy(50, 30, _T("你好")); // 输出文字

	TCHAR str1[20] = _T("这是输出文字测试"); // 定义字符数组
	settextcolor(GREEN);  // 设置字体颜色
	settextstyle(40, 0, _T("黑体")); // 设置文字大小、字体	
	outtextxy(50, 130, str1); // 输出文字

	TCHAR str2[20];  // 定义字符数组
	int score = 10;  // 得分整型变量	
	_stprintf(str2, _T("得分：%d"),  score); // 将score转换为字符串
	settextcolor(BLUE);  // 设置字体颜色
	settextstyle(60, 0, _T("隶书")); // 设置文字大小、字体	
	outtextxy(50, 230, str2); // 输出文字

	_getch();
	return 0;
}