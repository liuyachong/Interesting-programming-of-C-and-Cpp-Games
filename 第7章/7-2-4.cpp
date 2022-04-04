#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#define BLOCK_SIZE 20 // 每个小格子的长宽大小 
#define HEIGHT 30 // 高度上一共30个小格子
#define WIDTH 40 //  宽度上一共40个小格子 

// 全局变量定义
int Blocks[HEIGHT][WIDTH] = {0}; //  二维数组，用于记录所有的游戏数据

void startup()  //  初始化函数
{
	int i;
	Blocks[HEIGHT/2][WIDTH/2] = 1; // 画面中间画蛇头，数字为1
	for (i=1;i<=4;i++) //  向左依次4个蛇身，数值依次为2,3,4,5
		Blocks[HEIGHT/2][WIDTH/2-i] = i+1;
	initgraph(WIDTH*BLOCK_SIZE,HEIGHT*BLOCK_SIZE); //  新开画面
	setlinecolor(RGB(200,200,200)); // 设置线条颜色
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	cleardevice(); // 清屏
	int i,j;
	for (i=0;i<HEIGHT;i++) //  对二维数组所有元素遍历
	{ 
		for (j=0;j<WIDTH;j++)
		{
			if (Blocks[i][j]>0) // 元素大于0表示是蛇，这里让蛇的身体颜色色调渐变
				setfillcolor(HSVtoRGB(Blocks[i][j]*10,0.9,1));
			else 
				setfillcolor(RGB(150,150,150)); // 元素为0表示为空，颜色为灰色
			// 在对应位置处，以对应颜色绘制小方格
			fillrectangle(j*BLOCK_SIZE,i*BLOCK_SIZE,
				(j+1)*BLOCK_SIZE,(i+1)*BLOCK_SIZE); 
		}
	}
	FlushBatchDraw(); // 批量绘制
}	

void updateWithoutInput() // 与输入无关的更新函数
{
}

void updateWithInput()  // 和输入有关的更新函数
{
}

int main() //  主函数
{
	startup();  // 初始化函数，仅执行一次	
	while (1)   // 一直循环
	{
		show();  // 进行绘制
		updateWithoutInput(); // 和输入无关的更新 
		updateWithInput();    // 和输入有关的更新
	}
	return 0;
}