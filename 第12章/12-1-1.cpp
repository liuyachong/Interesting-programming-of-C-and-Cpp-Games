#include <graphics.h>  
#include <conio.h>
#define  WIDTH 560 // 画面宽度
#define  HEIGHT 800 // 画面高度

int main()
{
	IMAGE im_bk;  // 定义图像对象	
	loadimage(&im_bk, _T("background.png")); // 导入背景图片
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	putimage(0, 0, &im_bk);	// 显示背景	
	_getch();
	return 0;
}