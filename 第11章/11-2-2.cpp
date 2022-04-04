#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
#define  PI 3.1415926
#define  WIDTH 800   // 画面宽度
#define  HEIGHT 600  // 画面高度度

float offsetAngle = PI/6; // 左右枝干和父枝干偏离的角度
float shortenRate = 0.65;  // 左右枝干比父枝干变短的倍数

// 枝干生成和绘制递归函数
// 输入参数：枝干起始x y坐标，枝干长度，枝干角度，枝干绘图线条宽度，第几代
void brunch(float x_start,float y_start,float length,float angle,float thickness,int generation)
{
	// 利用三角函数求出当前枝干的终点x,y坐标
	float x_end,y_end; 
	x_end = x_start+ length* cos(angle);
	y_end = y_start+ length* sin(angle);

	setlinestyle(PS_SOLID,thickness); // 设定当前枝干线宽
	setlinecolor(RGB(0,0,0)); // 设定当前枝干颜色 黑色
	line(x_start,y_start,x_end,y_end); //画出当前枝干（画线）

	// 求出子枝干的代数
	int childGeneration = generation + 1;	
	// 生成子枝干的长度，逐渐变短
	float childLength = shortenRate*length;
	
	// 当子枝干长度大于2，并且代数小于等于10，递归调用产生子枝干
	if (childLength>=2 && childGeneration<=9) 
	{		
		// 生成子枝干的粗细，逐渐变细
		float childThickness = thickness*0.8;
		if (childThickness<2) // 枝干绘图最细的线宽为2
			childThickness = 2;
		
		// 产生左右的子枝干
		brunch(x_end,y_end,childLength,angle+offsetAngle,childThickness,childGeneration);
		brunch(x_end,y_end,childLength,angle-offsetAngle,childThickness,childGeneration);
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
	brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1); //递归调用
	FlushBatchDraw(); // 批量绘制
	_getch();
	return 0;
}
