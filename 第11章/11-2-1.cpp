#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
#define  PI 3.1415926
#define  WIDTH 800   // 画面宽度
#define  HEIGHT 600  // 画面高度度

// 枝干生成和绘制递归函数
// 输入参数：枝干起始x,y坐标，枝干角度，第几代
void brunch(float x_start,float y_start,float angle,int generation)
{
	// 利用三角函数求出当前枝干的终点x,y坐标
	float x_end,y_end; 
	x_end = x_start+ 150* cos(angle);
	y_end = y_start+ 150* sin(angle);

	line(x_start,y_start,x_end,y_end); // 画出当前枝干（画线）		

	// 求出子枝干的代数
	int childGeneration = generation + 1;		
	// 当子枝干并且代数小于等于4，画出当前枝干，并递归调用产生子枝干
	if (childGeneration<=4) 
	{						
		// 产生左右的子枝干
		brunch(x_end,y_end,angle+PI/6,childGeneration);
		brunch(x_end,y_end,angle-PI/6,childGeneration);
	}
}

int main() // 主函数
{
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	setbkcolor(RGB(255,255,255)); // 白色背景
	setlinecolor(RGB(0,0,0)); // 设定线条颜色为黑色
	setlinestyle(PS_SOLID,3); // 设定线宽
	cleardevice(); // 清屏
	BeginBatchDraw(); // 开始批量绘制
	brunch(WIDTH/2,HEIGHT,-PI/2,1); // 递归函数调用
	FlushBatchDraw(); // 批量绘制
	_getch();
	return 0;
}
