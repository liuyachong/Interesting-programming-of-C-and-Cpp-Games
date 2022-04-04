#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"  // 用于显示带透明通道的png图片
#define  WIDTH 560 // 画面宽度
#define  HEIGHT 800 // 画面高度
#define	 MaxBulletNum 200  // 最多子弹个数

void sleep(DWORD ms)  // 精确延时函数
{
	static DWORD oldtime = GetTickCount();
	while(GetTickCount() - oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}

class Rocket  // 定义火箭类
{
public:
	IMAGE im_rocket; // 火箭图像
	IMAGE im_blowup; // 爆炸图像
	float x,y; // 火箭坐标
	float width,height; // 火箭图片的宽度、高度
	int liveSecond; // 火箭存活了多长时间
	int life;  // 火箭有几条命

	void draw() // 显示火箭相关信息	
	{
		// 窗口左上角显示life个火箭图片，表示火箭生命数
		for (int i=0;i<life;i++)
			putimagePng(i*width*0.9,0,&im_rocket);

		// 窗口正上方显示坚持了多少秒
		TCHAR s[20];
		setbkmode(TRANSPARENT); // 文字字体透明
		_stprintf(s, _T("%d秒"), liveSecond);	
		settextcolor(WHITE); // 设定文字颜色
		settextstyle(40, 0, _T("黑体"));//  设定文字大小、样式
		outtextxy(WIDTH*0.85, 20, s); //  输出文字内容

		if (life>0) // 根据有命没命，显示不同的图片
			putimagePng(x - width/2,y-height/2,&im_rocket);  // 游戏中显示火箭图片
		else
			putimagePng(x - width/2,y-height/2,&im_blowup);  // 游戏中显示爆炸图片
	}

	void update(float mx,float my) // 根据输入的坐标更新火箭的位置
	{
		x = mx;
		y = my;
	}

	void updateWhenLifeLost() // 当火箭减命时执行的操作
	{
		life --; // 生命减少
	}
};

class Bullet  // 定义子弹类
{
public:
	IMAGE im_bullet; // 子弹图像
	float x,y; // 子弹坐标
	float vx,vy; // 子弹速度
	float radius; // 接近球体的子弹半径大小

	void draw()// 显示子弹	
	{
		putimagePng(x - radius,y-radius,&im_bullet);  
	}

	void update() // 更新子弹的位置、速度
	{
		x += vx;
		y += vy;
		if (x<=0 || x>=WIDTH)
			vx = -vx;
		if (y<=0 || y>=HEIGHT)
			vy = -vy;
	}

	int isCollideRocket(Rocket rocket) // 判断子弹是否和火箭碰撞
	{
		float distance_x = abs(rocket.x - x);
		float distance_y = abs(rocket.y - y);
		if ( distance_x < rocket.width/2 && distance_y < rocket.height/2 )
			return 1; // 发生碰撞返回1
		else
			return 0; // 不碰撞返回0	
	}
};

IMAGE im_bk,im_bullet,im_rocket,im_blowup;  // 定义图像对象	
Bullet bullet[MaxBulletNum]; // 定义子弹对象数组
Rocket rocket;  // 定义火箭对象
int bulletNum = 0; // 已有子弹的个数

void startup()  //  初始化函数
{	
	srand(time(0)); // 初始化随机种子
	loadimage(&im_bk, _T("background.png")); // 导入背景图片
	loadimage(&im_bullet, _T("bullet.png")); // 导入子弹图片
	loadimage(&im_rocket, _T("rocket.png")); // 导入火箭图片
	loadimage(&im_blowup, _T("blowup.png")); // 导入爆炸图片
	// 对rocket一些成员变量初始化
	rocket.im_rocket = im_rocket;  // 设置火箭图片
	rocket.im_blowup = im_blowup;  // 设置火箭爆炸图片
	rocket.width = im_rocket.getwidth(); // 设置火箭宽度
	rocket.height = im_rocket.getheight(); // 设置火箭高度
	rocket.life = 5; // 火箭初始5条命 

	initgraph(WIDTH,HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	putimage(0, 0, &im_bk);	// 显示背景	
	for (int i=0;i<bulletNum;i++)
		bullet[i].draw();  // 显示已有的子弹
	rocket.draw();  // 显示火箭及相关信息
	FlushBatchDraw(); // 批量绘制
	sleep(10); // 暂停
}

void updateWithoutInput() // 和输入无关的更新
{
	if (rocket.life<=0) // 火箭没有命了，不处理
		return; // 直接返回

	static int lastSecond = 0; // 记录前一次程序运行了多少秒
	static int nowSecond = 0; // 记录当前程序运行了多少秒
	static clock_t start = clock(); // 记录第一次运行时刻
	clock_t now = clock(); // 获得当前时刻
	// 计算程序目前一共运行了多少秒
	nowSecond =( int(now - start) / CLOCKS_PER_SEC);
	rocket.liveSecond = nowSecond; // 火箭生成了多少秒赋值
	if (nowSecond==lastSecond+2) // 时间过了2秒钟，新增一颗子弹
	{
		lastSecond = nowSecond; // 更新下lastSecond变量
		// 如果没有超出最大子弹数目的限制，增加一颗新的子弹
		if (bulletNum<MaxBulletNum)
		{
			bullet[bulletNum].x = WIDTH/2; // 子弹初始位置
			bullet[bulletNum].y = 10;
			float angle = (rand()/double(RAND_MAX)-0.5)*0.9*PI;
			float scalar = 2*rand()/double(RAND_MAX) + 2;
			bullet[bulletNum].vx = scalar*sin(angle); // 子弹随机速度
			bullet[bulletNum].vy = scalar*cos(angle);
			bullet[bulletNum].im_bullet = im_bullet;  // 设置子弹图像
			bullet[bulletNum].radius = im_bullet.getwidth()/2; // 子弹半径为图片宽度一半
		}
		bulletNum++; // 子弹数目加一
	}

	for (int i=0;i<bulletNum;i++) // 对所有已有的子弹
	{
		bullet[i].update(); // 更新子弹的位置、速度		
		if (bullet[i].isCollideRocket(rocket)) // 判断子弹是否和火箭碰撞
		{
			rocket.updateWhenLifeLost(); // 火箭减命相关操作
			bullet[i].x = 5; // 当前子弹移开，防止重复碰撞
			bullet[i].y = 5; 
			break; // 火箭已炸，不用再和其他子弹比较了
		}
	}
}

void updateWithInput()  // 和输入相关的更新
{
	if (rocket.life<=0) // 火箭没有命了，不处理
		return; // 直接返回

	MOUSEMSG m;		// 定义鼠标消息
	while (MouseHit())  // 检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if(m.uMsg == WM_MOUSEMOVE)  // 到鼠标移动时			
			rocket.update(m.x,m.y); // 火箭的位置等于鼠标所在的位置
	}	
}

int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 重复运行
	{
		show();  // 绘制
		updateWithoutInput();  // 和输入无关的更新
		updateWithInput();  // 和输入相关的更新
	}
	return 0;
}