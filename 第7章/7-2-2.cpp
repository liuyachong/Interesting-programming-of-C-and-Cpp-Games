#include <graphics.h>  
#include <conio.h>
#include <stdio.h>

#define BLOCK_SIZE 20 // 每个小格子的长宽大小 
#define HEIGHT 30 // 高度上一共30个小格子
#define WIDTH 40 //  宽度上一共40个小格子 

int main() // 主函数
{
	initgraph(WIDTH*BLOCK_SIZE,HEIGHT*BLOCK_SIZE); //  新开画面
	cleardevice();
	int Blocks[HEIGHT][WIDTH] = {0}; //  二维数组，用于记录所有的游戏数据
	int i,j;

	for (i=0;i<HEIGHT;i++) //  对二维数组所有元素值初始化
		for (j=0;j<WIDTH;j++)
			Blocks[i][j] = rand()%30; // 赋为随机数

	for (i=0;i<HEIGHT;i++) //  对二维数组所有元素遍历
	{ 
		for (j=0;j<WIDTH;j++)
		{
			setlinecolor(RGB(200,200,200));
			setfillcolor(HSVtoRGB(Blocks[i][j]*10,0.9,1)); // 根据元素值设定填充颜色	
			// 在对应位置处，以对应颜色绘制小方格
			fillrectangle(j*BLOCK_SIZE,i*BLOCK_SIZE,(j+1)*BLOCK_SIZE,(i+1)*BLOCK_SIZE); 
		}
	}

	_getch();
	closegraph();
	return 0;
}