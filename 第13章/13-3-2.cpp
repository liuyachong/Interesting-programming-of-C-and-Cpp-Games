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
	float sampleInterval; // 对特征点连成的轨迹线，进行均匀采样的间隔
	vector<Point> allPoints; //  所有以采样间隔得到的采样点

	void getAllPoints() // 以采样间隔进行采样，得到所有的采样点
	{
		int i;
		// 对关键点依次连接形成的多条线段进行遍历
		for (i=0;i<keyPoints.size()-1;i++)
		{
			float xd = keyPoints[i+1].x - keyPoints[i].x;
			float yd = keyPoints[i+1].y - keyPoints[i].y;
			float length = sqrt(xd*xd+yd*yd); // 这一段直线段的长度

			int num = length/sampleInterval; // 这一段直线段要被采样的个数
			for (int j=0;j<num;j++)
			{
				float x_sample = keyPoints[i].x + j*xd/num;
				float y_sample = keyPoints[i].y + j*yd/num;
				allPoints.push_back(Point(x_sample,y_sample)); // 添加进去所有的采样点
			}
		}
		// 还有最后一个关键点
		allPoints.push_back(Point(keyPoints[i].x,keyPoints[i].y));
	}

	void draw() // 画出轨迹
	{
		setlinecolor(RGB(0,0,0)); // 设置线条颜色
		setfillcolor(RGB(0,0,0)); // 设置填充颜色
		// 画出关键点依次连接形成的多条线段
		for (int i=0;i<keyPoints.size()-1;i++)
			line(keyPoints[i].x,keyPoints[i].y,keyPoints[i+1].x,keyPoints[i+1].y); 
		// 所有采样点处，分别画一个小圆点
		for (int i=0;i<allPoints.size();i++)
			fillcircle(allPoints[i].x,allPoints[i].y,3); 
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

	path.sampleInterval = 10; // 设置轨迹线的采样间隔
	path.getAllPoints();    // 获得轨迹上的所有采样点

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