#include <graphics.h>  
#include "conio.h"
#include "EasyXPng.h"  // 用于显示带透明通道的png图片
#define  WIDTH 560 // 画面宽度
#define  HEIGHT 800 // 画面高度

int main()
{
	IMAGE im_bk,im_rocket;  // 定义图像对象	
	loadimage(&im_bk, _T("background.png")); // 导入背景图片
	loadimage(&im_rocket, _T("rocket.png")); // 导入火箭图片

	initgraph(WIDTH,HEIGHT); // 新开一个画面
	putimage(0, 0, &im_bk);	// 显示背景
	putimagePng(WIDTH/2, HEIGHT/2, &im_rocket); // 显示火箭
	_getch();
	return 0;
}