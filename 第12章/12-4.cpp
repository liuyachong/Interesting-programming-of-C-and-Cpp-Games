#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"  // 用于显示带透明通道的png图片
#define  WIDTH 560 // 画面宽度
#define  HEIGHT 800 // 画面高度
#define	 MaxBulletNum 200  // 最多子弹个数

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
};

IMAGE im_bk,im_bullet;  // 定义图像对象	
Bullet bullet[MaxBulletNum]; // 定义子弹对象数组
int bulletNum = 0; // 已有子弹的个数

void startup()  //  初始化函数
{	
	srand(time(0)); // 初始化随机种子
	loadimage(&im_bk, _T("background.png")); // 导入背景图片
	loadimage(&im_bullet, _T("bullet.png")); // 导入子弹图片
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	putimage(0, 0, &im_bk);	// 显示背景	
	for (int i=0;i<bulletNum;i++)
		bullet[i].draw();  // 显示已有的子弹
	FlushBatchDraw(); // 批量绘制
	Sleep(10); // 暂停
}

void updateWithoutInput() // 和输入无关的更新
{
	static int lastSecond = 0; // 记录前一次程序运行了多少秒
	static int nowSecond = 0; // 记录当前程序运行了多少秒
	static clock_t start = clock(); // 记录第一次运行时刻
	clock_t now = clock(); // 获得当前时刻
	// 计算程序目前一共运行了多少秒
	nowSecond =( int(now - start) / CLOCKS_PER_SEC);
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
		bullet[i].update(); // 更新子弹的位置、速度
}

int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 重复运行
	{
		show();  // 绘制
		updateWithoutInput();  // 和输入无关的更新
	}
	return 0;
}