#include <graphics.h>  
#include <conio.h>
#include <vector>
using namespace std;
#define  WIDTH 1000 // 窗口宽度
#define  HEIGHT 700 // 窗口高度

class Point // 定义顶点类
{
public:
	float x,y; // 记录(x,y)坐标
	Point() // 无参数的构造函数
	{
	}
	Point (float ix,float iy) // 有参数的构造函数
	{
		x = ix;
		y = iy;
	}
};

class Path  // 定义轨迹类
{
public:
	vector<Point> keyPoints; //  记录轨迹上的一些关键点，关键点之间以直线相连

	void draw() // 画出轨迹
	{
		setlinecolor(RGB(0,0,0)); // 设置线条颜色
		setfillcolor(RGB(0,0,0)); // 设置填充颜色
		// 关键点处画小圆圈
		for (int i=0;i<keyPoints.size();i++)
			fillcircle(keyPoints[i].x,keyPoints[i].y,8);
		// 画出关键点依次连接形成的多条线段
		for (int i=0;i<keyPoints.size()-1;i++)
			line(keyPoints[i].x,keyPoints[i].y,keyPoints[i+1].x,keyPoints[i+1].y); 
	}
};

// 以下定义一些全局变量
Path path; // 定义轨迹对象

void startup()  // 初始化函数
{	
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	setbkcolor(WHITE); // 设置背景颜色
	cleardevice(); // 清屏

	// 为轨迹类添加一些关键点
	path.keyPoints.push_back(Point(100, 600));
	path.keyPoints.push_back(Point(900, 600));
	path.keyPoints.push_back(Point(900, 100));
	path.keyPoints.push_back(Point(100, 100));

	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	cleardevice(); // 清屏
	path.draw();  // 画出轨迹
	FlushBatchDraw(); // 批量绘制
	Sleep(1); // 延时
}

int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 循环
	{
		show(); // 显示
	}
	return 0;
}