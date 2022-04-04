#include <graphics.h>  
#include <conio.h>
#include <math.h>
#define PI 3.14159 // PI宏定义

struct Round // 定义结构体，用来表示带角度指示的小圆圈
{
	float x,y; // 小圆的圆心坐标
	float r; // 小圆半径
	int angleNum;  // 对应的角度，这里只能是0,1,2,3。表示乘以 PI/2 后对应的四个角度值
};

int main() // 主函数
{
	initgraph(600,600); // 新建画面
	setbkcolor(RGB(50,50,50)); // 设置背景颜色
	setlinestyle(PS_SOLID,3); //  设置线条样式、线宽
	cleardevice(); // 清空背景

	Round round; // 定义结构体变量
	round.x = 300; // 设定小圆圈的圆心坐标
	round.y = 300; // 
	round.r = 30; // 设定小圆圈的半径
	round.angleNum = 1; // 1*PI/2角度，也就是向上

	setlinecolor(RGB(200,200,200));  // 设置圆圈为白灰色
	circle(round.x,round.y,round.r); // 画小圆圈
	setlinecolor(RGB(255,0,0)); // 设置角度指示线为红色
	float angle = round.angleNum * PI/2; // 通过数组记录的变量设定对应的角度
	// 用三角函数，画出这根红线线
	line(round.x,round.y,round.x + round.r*cos(-angle),round.y + round.r*sin(-angle));

	_getch();
	closegraph();
	return 0;
}