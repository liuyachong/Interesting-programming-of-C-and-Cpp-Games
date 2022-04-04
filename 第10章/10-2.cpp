#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
# define BlockSize 40 // 小方块的长宽大小
# define RowNum 13 // 游戏画面一共RowNum行小方块
# define ColNum 21 // 游戏画面一共ColNum列小方块
# define ColorTypeNum 9 // 方块彩色颜色的个数

struct Block // 小方块结构体
{
	int x,y; // 小方块在画面中的x,y坐标
	int i,j;  // 小方块在二维数组中的i,j下标
	int colorId; // 对应颜色的下标
};

// 全局变量
Block blocks[RowNum][ColNum]; // 构建二维数组，存储所有数据
COLORREF  colors[ColorTypeNum+1]; // 颜色数组，小方块可能的几种颜色

void startup() // 初始化函数
{
	int i,j;

	int width = BlockSize*ColNum;   // 设定游戏画面的大小
	int height = BlockSize*RowNum; 
	initgraph(width,height);		// 新开窗口
	setbkcolor(RGB(220,220,220));   // 设置背景颜色
	setfillcolor(RGB(255,0,0));    // 设置填充色
	setlinestyle(PS_SOLID,2);      // 设置线型、线宽
	cleardevice();    // 以背景颜色清屏
	BeginBatchDraw(); // 开始批量绘制
	srand(time(0)); // 随机种子初始化

	colors[0] = RGB(220,220,220); // 颜色数组第一种颜色为灰白色，表示空白小方块
	for (i=1;i<ColorTypeNum+1;i++) // 其他几种颜色为彩色
		colors[i] = HSVtoRGB((i-1)*40,0.6,0.8);
	
	// 对blocks二维数组进行初始化
	for (i=0;i<RowNum;i++)
	{
		for (j=0;j<ColNum;j++)
		{	
			int t = rand()%(ColorTypeNum+1);  // 取随机数
			blocks[i][j].colorId = t; // 小方块的颜色序号
			blocks[i][j].x = j*BlockSize; // 小方块左上角的坐标
			blocks[i][j].y = i*BlockSize; 
			blocks[i][j].i = i;   // 存储当前小方块在二维数组中的下标
			blocks[i][j].j = j; 
		}
	}
}

void show() // 绘制函数
{
	cleardevice(); // 清屏
	setlinecolor(RGB(255,255,255)); // 白色线条
	int i,j;
	for (i=0;i<RowNum;i++)
	{
		for (j=0;j<ColNum;j++)
		{
			// 以对应的颜色、坐标画出所有的小方块
			setfillcolor(colors[blocks[i][j].colorId]);
			fillrectangle(blocks[i][j].x,blocks[i][j].y,
						blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
		}
	}
	FlushBatchDraw(); // 开始批量绘制
}	

void updateWithoutInput() // 和输入无关的更新
{
}

void updateWithInput() // 和输入有关的更新
{
}

int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 循环执行
	{
		show();  // 绘制
		updateWithoutInput(); // 和输入无关的更新
		updateWithInput();   // 和输入有关的更新
	}
	return 0;
}