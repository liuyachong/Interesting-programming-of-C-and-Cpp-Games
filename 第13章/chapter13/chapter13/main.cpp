#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include <vector>
#include <algorithm>
#pragma comment(lib,"Winmm.lib")
using namespace std;
#define  WIDTH 1000 // 窗口宽度
#define  HEIGHT 700 // 窗口高度
#define  Radius 25 //  小球半径
#define  ColorNum 5 //  小球颜色种类数目
COLORREF  colors[ColorNum] = {RED,BLUE,GREEN,YELLOW,MAGENTA}; // 定义数组保存所有的颜色

// 求两点之间的距离函数
float Distance(float x1,float y1,float x2,float y2)
{
	float xd = x1 - x2;
	float yd = y1 - y2;
	float length = sqrt(xd*xd+yd*yd); 
	return length;
}

void sleep(DWORD ms)  // 精确延时函数
{
	static DWORD oldtime = GetTickCount();
	while(GetTickCount() - oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}

void PlayMusicOnce(TCHAR fileName[80]) // 播放一次音乐函数
{
	TCHAR cmdString1[50];
	_stprintf(cmdString1, _T("open %s alias tmpmusic"), fileName); // 生成命令字符串
	mciSendString(_T("close tmpmusic"), NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString(cmdString1, NULL, 0, NULL); // 打开音乐
	mciSendString(_T("play tmpmusic"), NULL, 0, NULL); // 仅播放一次
}

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

class Cannon // 炮台类，包括角色图片，还有一个小球
{
public:
	IMAGE im; // 角色图片
	IMAGE im_rotate; // 角色旋转后的图片
	float x,y; // 中心坐标
	Ball ball;  // 一个可以绕着中心旋转，变颜色的小球
	float angle; // 旋转角度

	void draw() // 一些绘制函数
	{
		rotateimage(&im_rotate,&im,angle,RGB(160,211,255),false,false);//旋转角色图片
		putimage(x-im.getwidth()/2,y-im.getheight()/2,&im_rotate); // 显示旋转后角色图片
		ball.draw(); // 绘制这个待发射的小球
	}

	void setBallPosition() // 生成炮台小球的坐标
	{
		ball.center.x = x + 100 * cos(angle);
		ball.center.y = y + 100 * sin(angle);
	}	

	void updateWithMouseMOVE(int mx,int my) // 根据鼠标的移动位置来更新
	{
		// 求出炮台到鼠标的角度
		float xs = mx - x;
		float ys = my - y;
		float length = sqrt(xs*xs+ys*ys);
		if (length>4) // 鼠标距离中心位置过近，不处理
		{
			angle = atan2(-ys,xs); // 求出炮台旋转角度

			// 也顺便求出炮台附带的球的位置
			ball.center.x = x + 100 * xs/length;
			ball.center.y = y + 100 * ys/length;
		}
	}	

	void updateWithRButtonDown() // 当鼠标右键点击时，改变小球的颜色
	{
		// 更改炮台要发射的小球的颜色
		ball.colorId +=1;
		if (ball.colorId==ColorNum)
			ball.colorId =0;
	}
};

// 在Balls中序号i位置球，寻找其前后有没有和他颜色一样，且多余个连续靠近的球
// 如果有的话，就删除掉,返回的结果是删除掉的小球的个数
// 如果一个没有删除，就返回0
int eraseSameColorBalls(int i,Ball fireball,Path &path,vector <Ball> &balls)
{
	// 记录下前后和插入的小球颜色一样的序号，后面去重复，得到对应的要删除的序号
	vector<int> sameColorIndexes;  
	int forward = i; 
	int backward = i; 
	sameColorIndexes.push_back(i); // 首先把i添加到vector中

	// 向Path终点方向寻找，也就是向最开始加入的球方向寻找
	while(forward>0 &&  balls[forward].colorId==fireball.colorId)
	{
		sameColorIndexes.push_back(forward);
		if (balls[forward-1].indexInPath - balls[forward].indexInPath>2*Radius/path.sampleInterval)
			break; // 前面一个球和这个球间距过大，跳出循环
		forward--;
	}
	if (forward==0 && balls[0].colorId==fireball.colorId) // 处理特殊情况，最接近终点的那个球
		sameColorIndexes.push_back(forward);

	// 向Path起点方向寻找，也就是最后加入的球的方向寻找
	while (backward<balls.size()-1 && balls[backward].colorId==fireball.colorId) // 还没有找到最后一个加入的球
	{
		sameColorIndexes.push_back(backward);
		if (balls[backward].indexInPath - balls[backward+1].indexInPath>2*Radius/path.sampleInterval)
			break; // 前面一个球和这个球间距过大，跳出循环
		backward++;
	}
	if (backward==balls.size()-1 && balls[balls.size()-1].colorId==fireball.colorId) // 处理特殊情况，最接近起点的那个球
		sameColorIndexes.push_back(backward);

	// 去除同样颜色小球中重复的序号
	sort(sameColorIndexes.begin(), sameColorIndexes.end());
	vector<int>::iterator ite = unique(sameColorIndexes.begin(), sameColorIndexes.end());
	sameColorIndexes.erase(ite, sameColorIndexes.end());

	int NumSameColors = sameColorIndexes.size();
	if (NumSameColors>=3) // 相同颜色的球达到3个或以上
	{
		int minIndex = sameColorIndexes[0];
		int maxIndex = sameColorIndexes[NumSameColors-1];
		// 把这些球给删掉						
		balls.erase(balls.begin()+minIndex,balls.begin()+maxIndex+1);
		return NumSameColors; // 消除了，返回消除小球数目
	}
	return 0; // 没有消除，返回0
}

// 以下定义一些全局变量
Path path; // 定义轨迹对象
vector <Ball> balls; // 记录多个小球
IMAGE im_role,im_house,im_bk; // 一些图片
Cannon cannon;  // 定义炮台对象
int gameStatus = 0;  // 游戏状态，-1失败，0正常，1胜利

void startup()  // 初始化函数
{	
	mciSendString(_T("open game_music.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // 循环播放
	srand(time(0)); // 随机初始化种子
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	cleardevice(); // 清屏
	loadimage(&im_bk, _T("bk.jpg")); // 导入背景图片
	loadimage(&im_role, _T("role.jpg")); // 导入角色图片
	loadimage(&im_house, _T("house.jpg")); // 导入家图片

	// 为轨迹类添加一些关键点
	path.keyPoints.push_back(Point(50, 300));
	path.keyPoints.push_back(Point(50, 600));
	path.keyPoints.push_back(Point(100, 650));
	path.keyPoints.push_back(Point(700, 650));
	path.keyPoints.push_back(Point(700, 550));
	path.keyPoints.push_back(Point(250, 550));
	path.keyPoints.push_back(Point(200, 500));
	path.keyPoints.push_back(Point(200, 200));
	path.keyPoints.push_back(Point(250, 150));
	path.keyPoints.push_back(Point(800, 150));
	path.keyPoints.push_back(Point(850, 200));
	path.keyPoints.push_back(Point(850, 650));
	path.keyPoints.push_back(Point(950, 650));
	path.keyPoints.push_back(Point(950, 100));
	path.keyPoints.push_back(Point(900, 50));
	path.keyPoints.push_back(Point(150, 50));

	path.sampleInterval = Radius/5; // 设置轨迹线的采样间隔，需被Radius整除以便处理
	path.getAllPoints();    // 获得轨迹上的所有采样点

	// 炮台做一些初始化
	cannon.im = im_role; // 炮台角色图片
	cannon.angle = 0; // 初始角度
	cannon.x = 500;  // 中心坐标
	cannon.y = 350;
	cannon.ball.radius = Radius; // 炮台带的小球的半径
	cannon.ball.colorId = rand()%ColorNum; // 炮台小球颜色
	cannon.setBallPosition(); // 设置炮台小球的坐标

	// 先添加一些小球
	for (int i=0;i<15;i++)
	{
		Ball ball;  // 定义一个小球对象
		ball.initiate(path); // 初始化小球到path最开始的位置上	
		balls.push_back(ball); // 把小球ball添加到balls中
	}

	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	putimage(0,0,&im_bk); // 显示背景图片
	putimage(30,10,&im_house); // 显示房子图片
	//path.draw();  // 画出轨迹
	cannon.draw(); // 画出炮台	
	for (int i=0;i<balls.size();i++)
		balls[i].draw();  // 画出所有小球

	// 设置字体显示属性
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255,0,0)); 
	settextstyle(60, 0, _T("宋体"));
	if (gameStatus==1) // 输出游戏胜利
		outtextxy(WIDTH*0.35, HEIGHT*0.35, _T("游戏胜利 :)"));
	else if (gameStatus==-1) // 输出游戏失败
		outtextxy(WIDTH*0.35, HEIGHT*0.35, _T("游戏失败 :("));

	FlushBatchDraw(); // 批量绘制
}

void updateWithoutInput() // 和输入无关的更新
{	
	static clock_t start = clock(); // 记录第一次运行时刻
	clock_t now = clock(); // 获得当前时刻
	// 计算程序目前一共运行了多少秒
	int nowSecond =( int(now - start) / CLOCKS_PER_SEC);
	// 100秒内，时间每过20秒钟，新增一批小球
	if (nowSecond%20==10 && nowSecond<=100 && gameStatus==0) 
	{
		Ball ball;  // 定义一个小球对象
		ball.initiate(path); // 初始化小球到path最开始的位置上
		balls.push_back(ball); // 把小球ball添加到balls中
	}
	if (balls.size()==0) // 小球清空完了
	{
		if (nowSecond>100) // 时间到了，游戏胜利
			gameStatus = 1; // 游戏胜利
		return; // 没有到截止时间，小球清空了，等到到时间后产生新的小球
	}
	// 第一个球跑到终点了，游戏失败
	if (balls[0].indexInPath >= path.allPoints.size()-1)
	{
		gameStatus = -1; // 游戏失败
		return;
	}

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

	sleep(30); // 暂停若干毫秒
}

void updateWithInput()  // 和输入相关的更新
{
	if (gameStatus!=0) // 游戏胜利或失败，不需要用户再输入，函数直接返回
		return;

	int i,j;
	MOUSEMSG m;		// 定义鼠标消息
	while (MouseHit())  // 检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if(m.uMsg == WM_MOUSEMOVE)  // 鼠标移动时			
		{
			cannon.updateWithMouseMOVE(m.x,m.y); // 炮台旋转，小球也移动到对应位置上
		}
		else if(m.uMsg == WM_RBUTTONDOWN)  // 鼠标右键点击时，更改炮台要发射的小球的颜色		
		{
			cannon.updateWithRButtonDown();
		}
		else if(m.uMsg == WM_LBUTTONDOWN)  // 鼠标左键点击时			
		{	
			cannon.updateWithMouseMOVE(m.x,m.y); //  先更新下炮台旋转角度、炮台小球的坐标
			float vx = (cannon.ball.center.x - cannon.x)/5; // 炮台小球移动速度
			float vy = (cannon.ball.center.y - cannon.y)/5;			
			int isCollider = 0; // 假设balls中没有小球和炮台小球碰撞
			// 沿着发射的方向炮台小球逐步移动，判断有balls有没有小球和炮台小球碰撞
			while (isCollider==0 && cannon.ball.center.y>0 && cannon.ball.center.y < HEIGHT
				&& cannon.ball.center.x>0  && cannon.ball.center.x < WIDTH ) // 炮台小球超出边界就不用处理了
			{
				cannon.ball.center.x += vx; // 更新发射小球的位置
				cannon.ball.center.y += vy;
				show(); // 显示下炮台小球的运动轨迹

				// balls中所有小球和炮台小球坐标判断，看看是否有相交的
				for (i=0;i<balls.size();i++)
				{
					float distance = Distance(balls[i].center.x, balls[i].center.y,cannon.ball.center.x,cannon.ball.center.y); 
					if (distance<Radius) // 找到和炮台小球碰撞的小球
					{			
						isCollider = 1; // 设为找到碰撞小球了						
						cannon.updateWithMouseMOVE(m.x,m.y); // 把炮台小球的位置移动回去

						// 下面复制一份小球，插入到这个地方
						Ball fireball = balls[i];
						fireball.colorId = cannon.ball.colorId; // 将插入小球变成炮台小球的颜色
						balls.insert(balls.begin()+i,fireball); // 复制一个小球，插入到vector中

						// 在Balls中序号i位置球，寻找其前后有没有和他颜色一样，且多余3个连续靠近的球
						// 如果是的话，就删除掉,返回的结果是删除掉的小球的个数
						// 如果一个没有删除，就返回0
						int count = eraseSameColorBalls(i,fireball,path,balls);
						if (count>=3)
							PlayMusicOnce(_T("coin.mp3"));  // 播放一次金币音效
						if (count==0)// 如果没有消除的话
						{
							for (j=i;j>=0;j--) // 移动前面的小球，留出空间放下新插入的小球
							{
								if (balls[j].indexInPath - balls[j+1].indexInPath <=0)
									balls[j].indexInPath = balls[j+1].indexInPath + 2*Radius/path.sampleInterval;
								else
									break; // 前面小球间有空隙，不用再处理了
							}
						}
						return; // 找到一个和炮台碰撞的小球了，后面的不用再找了
					}
				}  // for (i=0;i<balls.size();i++)
			} // 炮台小球逐步移动，和balls数组中所有小球进行判断
		} // 鼠标左键点击时	
	} 
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
		updateWithInput();  // 和输入相关的更新
	}
	gameover(); // 游戏结束时的处理
	return 0;
}