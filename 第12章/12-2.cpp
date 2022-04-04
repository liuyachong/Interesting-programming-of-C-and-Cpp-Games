#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"  // 用于显示带透明通道的png图片
#define  WIDTH 560 // 画面宽度
#define  HEIGHT 800 // 画面高度

struct Bullet  // 子弹结构体
{
	IMAGE im_bullet; // 子弹图像
	float x,y; // 子弹坐标
	float vx,vy; // 子弹速度
	float radius; // 接近球体的子弹半径大小
};

IMAGE im_bk,im_bullet;  // 定义图像对象	
Bullet bullet; // 定义子弹结构体变量

void startup()  //  初始化函数
{	
	loadimage(&im_bk, _T("background.png")); // 导入背景图片
	loadimage(&im_bullet, _T("bullet.png")); // 导入子弹图片
	bullet.x = WIDTH/2; // 子弹初始位置
	bullet.y = HEIGHT/2;
	bullet.vx = 2;  // 子弹速度
	bullet.vy = 2;
	bullet.im_bullet = im_bullet;  // 设置子弹图像
	bullet.radius = im_bullet.getwidth()/2; // 设置子弹的半径为其图片宽度的一半

	initgraph(WIDTH,HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	putimage(0, 0, &im_bk);	// 显示背景	
	putimagePng(bullet.x - bullet.radius,bullet.y-bullet.radius,&bullet.im_bullet); // 显示子弹
	FlushBatchDraw(); // 批量绘制
	Sleep(10); // 暂停
}

void updateWithoutInput() // 和输入无关的更新
{
	// 更新子弹的位置、速度
	bullet.x += bullet.vx;
	bullet.y += bullet.vy;
	if (bullet.x<=0 || bullet.x>=WIDTH)
		bullet.vx = -bullet.vx;
	if (bullet.y<=0 || bullet.y>=HEIGHT)
		bullet.vy = -bullet.vy;
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