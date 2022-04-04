#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include <vector>
using namespace std;
#define  WIDTH 1000 // 窗口宽度
#define  HEIGHT 700 // 窗口高度
#define  Radius 25 //  小球半径
#define  ColorNum 5 //  小球颜色种类数目
COLORREF  colors[ColorNum] = {RED,BLUE,GREEN,YELLOW,MAGENTA}; // 定义数组保存所有的颜色

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
			fillcircle(allPoints[i].x,allPoints[i].y,2); 
	}

	~Path()  // 析构函数
	{
		keyPoints.clear(); // 清除vector的内存空间
		allPoints.clear();
	}
};

class Ball // 定义小球类
{
public:	
	Point center; // 圆心坐标
	float radius; // 半径
	int colorId;  // 小球的颜色序号，具体颜色在colors数组中取
	int indexInPath; // 小球位置在Path的allPoints中的对应序号
	int direction; // 小球移动方向，1向终点，-1向起点，0暂停

	void draw() // 画出小球
	{
		setlinecolor(colors[colorId]);
		setfillcolor(colors[colorId]);
		fillcircle(center.x,center.y,radius); 
	}

	void movetoIndexInPath(Path path)
	{
		// 让小球移动到 Path的allPoints中的indexInPath序号位置
		center = path.allPoints[indexInPath];
	}

	void initiate(Path path) // 初始化小球到path最开始的位置上
	{
		radius = Radius; //  半径
		indexInPath = 0; // 初始化序号
		direction = 0; // 初始静止
		movetoIndexInPath(path); // 移动到Path上面的对应序号采样点位置		
		colorId = rand() % ColorNum; // 随机颜色序号
	}

	// 让小球沿着轨迹Path移动,注意不要越界
	// direction为0暂时不动,direction为1向着终点移动，direction为-1向着起点移动
	void changeIndexbyDirection(Path path) 
	{
		if (direction==1 && indexInPath+1<path.allPoints.size())
			indexInPath++;
		else if (direction==-1 && indexInPath-1>=0)
			indexInPath--;
	}
};

// 以下定义一些全局变量
Path path; // 定义轨迹对象
vector <Ball> balls; // 记录多个小球

void startup()  // 初始化函数
{	
	srand(time(0)); // 随机初始化种子
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	setbkcolor(WHITE); // 设置背景颜色
	cleardevice(); // 清屏

	// 为轨迹类添加一些关键点
	path.keyPoints.push_back(Point(100, 600));
	path.keyPoints.push_back(Point(900, 600));
	path.keyPoints.push_back(Point(900, 100));
	path.keyPoints.push_back(Point(100, 100));

	path.sampleInterval = Radius/5; // 设置轨迹线的采样间隔，需被Radius整除以便处理
	path.getAllPoints();    // 获得轨迹上的所有采样点

	// 先添加一些小球，两部分小球之间有间隔
	for (int i=15;i>=10;i--)
	{
		Ball ball;  // 定义一个小球对象
		ball.initiate(path); // 初始化小球到path最开始的位置上	
		// 设置序号，正好保证两个相邻小球相切
		ball.indexInPath = i* (2*ball.radius/path.sampleInterval); 
		ball.movetoIndexInPath(path);
		balls.push_back(ball); // 把小球ball添加到balls中
	}
	for (int i=5;i>=0;i--)
	{
		Ball ball;  // 定义一个小球对象
		ball.initiate(path); // 初始化小球到path最开始的位置上	
		// 设置序号，正好保证两个相邻小球相切
		ball.indexInPath = i* (2*ball.radius/path.sampleInterval); 
		ball.movetoIndexInPath(path);
		balls.push_back(ball); // 把小球ball添加到balls中
	}

	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	cleardevice(); // 清屏
	path.draw();  // 画出轨迹
	for (int i=0;i<balls.size();i++)
		balls[i].draw();  // 画出所有小球
	FlushBatchDraw(); // 批量绘制
	Sleep(1); // 延时
}

void updateWithoutInput() // 和输入无关的更新
{	
	// 第一个球跑到终点了，游戏失败
	if (balls[0].indexInPath >= path.allPoints.size()-1)
		return;

	int i;	
	for (i=0;i<balls.size();i++)
		balls[i].direction = 0; // 先让所有小球的速度设为0

	//balls向前移动的源动力来自最后面一个小球，最后一个小球direction=1
	//如果终点方向前面一个小球和这个小球正好相切，则其direction也为1，否则direction为0
	i = balls.size() - 1; // 最后一个小球
	balls[i].direction = 1; // 最后一个小球向前运动

	while (i>0)  // 一直向前判断，还没有遍历到最前面一个小球
	{
		// 如果前后两个小球正好相切
		if (balls[i-1].indexInPath-balls[i].indexInPath <= 2*Radius/path.sampleInterval)
		{
			balls[i-1].direction = 1; // 前一个小球的方向也是向前
			// 对前一个小球的indexInPath进行规则化，确保正好相切
			balls[i-1].indexInPath = balls[i].indexInPath+2*Radius/path.sampleInterval; 
			i--;
		}
		else // 有一个小球不直接接触，就停止向前速度的传递
			break; // 跳出循环
	}

	for (int i=0;i<balls.size();i++)  // 每一个小球根据其direction更新他的位置
	{
		balls[i].movetoIndexInPath(path);
		balls[i].changeIndexbyDirection(path);
	}

	Sleep(50); // 暂停若干毫秒
}

void gameover() // 游戏结束时的处理
{
	balls.clear(); // 清除vector的内存空间
}

int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 循环
	{
		show(); // 显示
		updateWithoutInput();  // 和输入无关的更新
	}
	gameover(); // 游戏结束时的处理
	return 0;
}