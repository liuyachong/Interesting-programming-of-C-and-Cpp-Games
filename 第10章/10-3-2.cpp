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
			// 取随机数，1-ColorTypeNum为彩色，其他为空白色
			// 这样为空白色的比例更高，符合游戏的设定
			int t = rand()%(int(ColorTypeNum*1.5));  // 取随机数
			if (t<ColorTypeNum+1) 
				blocks[i][j].colorId = t; // 小方块的颜色序号
			else // 其他情况，都为空白颜色方块
				blocks[i][j].colorId = 0; // 小方块的颜色序号

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
	int i,j;
	MOUSEMSG m;		
	if (MouseHit())   // 当有鼠标消息时
	{
		m = GetMouseMsg();  	
		if(m.uMsg == WM_LBUTTONDOWN) // 当按下鼠标左键时
		{
			// 通过鼠标位置计算出点击的小方块在二维数组中的下标
			int clicked_i = int(m.y)/BlockSize;
			int clicked_j = int(m.x)/BlockSize;

			// 如果当前点击的不是空白方块，不需要处理，返回
			if (blocks[clicked_i][clicked_j].colorId!=0)
				return;

			// 定义数组存储上、下、左、右四个方向找到第一个不是空白的方块
			Block fourBlocks[4] = {blocks[clicked_i][clicked_j]}; //初始化为点击的方块
			int search; // 寻找下标

			// 向上找到第一个颜色不是空白的方块
			for (search=0;clicked_i-search>=0;search++)
			{
				if (blocks[clicked_i-search][clicked_j].colorId!=0) 
				{
					fourBlocks[0] = blocks[clicked_i-search][clicked_j];//赋给数组元素
					break;
				}
			}
			// 向下找到第一个颜色不是空白的方块
			for (search=0;clicked_i+search<RowNum;search++)
			{
				if (blocks[clicked_i+search][clicked_j].colorId!=0)  
				{
					fourBlocks[1] = blocks[clicked_i+search][clicked_j];//赋给数组元素
					break;
				}
			}
			// 向左找到第一个颜色不是空白的方块
			for (search=0;clicked_j-search>=0;search++)
			{
				if (blocks[clicked_i][clicked_j-search].colorId!=0)
				{
					fourBlocks[2] = blocks[clicked_i][clicked_j-search];//赋给数组元素
					break;
				}
			}
			// 向右找到第一个颜色不是空白的方块
			for (search=0;clicked_j+search<ColNum;search++)
			{
				if (blocks[clicked_i][clicked_j+search].colorId!=0) 
				{
					fourBlocks[3] = blocks[clicked_i][clicked_j+search];//赋给数组元素
					break;
				}
			}

			// 统计fourBlocks的四个小方块，有没有同样颜色数目大于等于2的
			int colorStatistics[ColorTypeNum+1] = {0}; // 初始化个数为0
			for (i=1;i<=ColorTypeNum;i++) // i=0是空白颜色，不要统计
			{
				for (j=0;j<4;j++) // 遍历fourBlocks
				{
					if (fourBlocks[j].colorId==i)
						colorStatistics[i]++; //方块颜色序号i，对应统计个数+1
				}
				if (colorStatistics[i]>=2) // 如果这种颜色方块个数大于等于2
				{					
					// 把对应十字区域要消除的方块颜色改成空白颜色
					for (j=0;j<4;j++) // 遍历fourBlocks
					{
						if (fourBlocks[j].colorId==i)
						{
							// 颜色序号设为0，也就是空白的灰白色
							blocks[fourBlocks[j].i][fourBlocks[j].j].colorId = 0; 
						}
					}
				}				
			}
		} // if 当按下鼠标左键时
	}
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