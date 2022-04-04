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
// 全局变量定义
Round rounds[5][5]; // 结构体二维数组

void startup()  // 初始化函数
{
	initgraph(600,700); // 新建画面
	setbkcolor(RGB(50,50,50)); // 设置背景颜色
	setlinestyle(PS_SOLID,3); //  设置线条样式、线宽
	cleardevice(); // 清空背景
	BeginBatchDraw(); // 开始批量绘制

	int i,j;
	// 初始化 设定5*5共25个小圆圈
	for (i=0;i<5;i++)
	{
		for (j=0;j<5;j++)
		{
			rounds[i][j].x = 100 + j*100; // 设定小圆圈的圆心坐标
			rounds[i][j].y = 200 + i*100; // 
			rounds[i][j].r = 30; // 设定小圆圈的半径
			rounds[i][j].angleNum = 1; // 开始都是PI/2角度，也就是都是向上
		}
	}
}

void show() // 绘制函数
{
	int i,j;
	float angle; // 
	cleardevice();
	// 对所有小圆圈遍历
	for (i=0;i<5;i++)
	{
		for (j=0;j<5;j++)
		{
			setlinecolor(RGB(200,200,200));  // 设置圆圈为白灰色
			circle(rounds[i][j].x,rounds[i][j].y,rounds[i][j].r); // 画小圆圈
			setlinecolor(RGB(255,0,0)); // 设置角度指示线为红色
			angle = rounds[i][j].angleNum * PI/2; // 通过数组记录的变量设定对应的角度
			// 用三角函数，画出这根红线
			line(rounds[i][j].x, rounds[i][j].y,	
				rounds[i][j].x + rounds[i][j].r * cos(-angle),
				rounds[i][j].y + rounds[i][j].r * sin(-angle));
		}
	}
	FlushBatchDraw(); // 开始批量绘制
}

void update()  // 更新函数
{
}

int main() // 主函数
{
	startup();  // 初始化
	while (1)   // 重复循环
	{
		show();  // 绘制
		update();  // 更新
	}
	return 0;
}