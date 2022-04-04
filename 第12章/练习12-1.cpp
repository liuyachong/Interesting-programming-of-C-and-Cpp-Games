#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"  // 用于显示带透明通道的png图片
#define  WIDTH 560 // 画面宽度
#define  HEIGHT 800 // 画面高度
#define	 MaxBulletNum 200  // 所有子弹个数

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

void startup()  //  初始化函数
{	
	loadimage(&im_bk, _T("background.png")); // 导入背景图片
	loadimage(&im_bullet, _T("bullet.png")); // 导入子弹图片
	for (int i=0;i<MaxBulletNum;i++) // 对所有子弹初始化
	{
		bullet[i].x = WIDTH/2; // 子弹初始位置
		bullet[i].y = 10;
		float angle = (rand()/double(RAND_MAX)-0.5)*0.9*PI;
		float scalar = 2*rand()/double(RAND_MAX) + 2;
		bullet[i].vx = scalar*sin(angle); // 子弹速度
		bullet[i].vy = scalar*cos(angle);
		bullet[i].im_bullet = im_bullet;  // 设置子弹图像
		bullet[i].radius = im_bullet.getwidth()/2; // 设置子弹的半径为其图片宽度的一半
	}
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	putimage(0, 0, &im_bk);	// 显示背景	
	for (int i=0;i<MaxBulletNum;i++)
		bullet[i].draw();  // 显示子弹
	FlushBatchDraw(); // 批量绘制
	Sleep(10); // 暂停
}

void updateWithoutInput() // 和输入无关的更新
{
	for (int i=0;i<MaxBulletNum;i++) // 对所有子弹
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