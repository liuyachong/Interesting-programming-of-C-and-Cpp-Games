#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

# define BlockSize 40 // 小方块的长宽大小
# define ColorTypeNum 9 // 除了空白方块外，其他方块的颜色的个数

struct Block // 小方块结构体
{
	int x,y; // x y坐标
	int colorId; // 对应颜色的下标
	int i,j;  // 小方块在二维数组中的i j下标
};

// 全局变量
int RowNum; // 游戏画面一共RowNum行小方块
int ColNum; // 游戏画面一共ColNum列小方块
Block **blocks = NULL; // 动态二维数组指针，存储所有方块数据
COLORREF  colors[ColorTypeNum+1]; // 颜色数组，小方块可能的几种颜色
int score; // 得分数，也就是消去的方块的个数
float maxTime; // 这一关游戏的总时长
float totalTime; // 减去扣分项后的游戏总时长
float remainTime; // 剩余时间
clock_t start, finish; // 用于计时的变量
int level = 1; // 当前关卡序号
int noZeroBlockNum; // 非空白区域的砖块的个数

void drawBlockHint(int i,int j,COLORREF color,int isfill) // 绘制出一个提示线框出来
{
	setlinecolor(color);
	setfillcolor(color);
	if (isfill==1) // 鼠标点击中的方块，画填充方块提示
		fillrectangle(blocks[i][j].x,blocks[i][j].y,blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
	if (isfill==0) // 上下左右四个方向找到的4个方块，画线框提示
		rectangle(blocks[i][j].x,blocks[i][j].y,blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
}


void writeRecordFile(int recordScore)  //保存最高分数据文件
{ 
	FILE *fp;
	fp = fopen(".\\gameRecord.dat","w");
	fprintf(fp,"%d",recordScore);
	fclose(fp);
}

int readRecordFile()  //读取最高分数据文件
{ 
	int recordScore;
	FILE *fp;
	fp = fopen(".\\gameRecord.dat","r");

	// 如果打不开的话，就新建一个文件，其得分记录为0分
	if (fp==NULL)
	{
		writeRecordFile(0);
		return 0;
	}
	else // 能打开这个文件，就读取下最高分记录
	{
		fscanf(fp,"%d",&recordScore);
		fclose(fp);
		return recordScore;
	}
}

void startup() // 初始化函数
{
	int i,j;
	start = clock(); // 记录当前运行时刻

	if (level>1) // 如果不是第1关，则先清除二维数组内存，再重新开辟内存空间
	{
		for (i=0;i<RowNum;i++)
			free(blocks[i]);
		free(blocks);
	}

	// 根据是第几关，调整这一关对应的游戏画面的大小
	RowNum = 12 + level/2;  // 行数添加的慢一些，是一个长方形的形状
	ColNum = 20 + level;

	// 开辟动态二维数组
	blocks = (Block **) malloc(RowNum*sizeof(Block *));
	for (i=0;i<RowNum;i++)
		blocks[i] = (Block *) malloc(ColNum*sizeof(Block));

	maxTime = 200 + level*10; // 这一关游戏设定的总时长，每关时长+10秒
	totalTime = maxTime; // 游戏总时长，每次出错，会扣10秒钟

	int width = BlockSize*ColNum;      // 设定游戏画面的大小
	int height = BlockSize*(RowNum+3); // 最下面用来显示一些提示信息
	initgraph(width,height);
	setbkcolor(RGB(220,220,220));
	setlinestyle(PS_SOLID,2);
	cleardevice();
	srand(time(0));
	BeginBatchDraw(); // 开始批量绘制

	score = 0; // 得分数，也就是消去的方块的个数
	noZeroBlockNum = 0; // 非空白区域的砖块的个数

	colors[0] = RGB(220,220,220); // 颜色数组第一种颜色为灰白色，表示空白小方块
	for (i=1;i<ColorTypeNum+1;i++) // 其他几种颜色为彩色
		colors[i] = HSVtoRGB((i-1)*40,0.6,0.8);

	// 对blocks二维数组进行初始化
	for (i=0;i<RowNum;i++)
	{
		for (j=0;j<ColNum;j++)
		{
			// 取随机数，1-6设为彩色色块，其他为空白色块，这样为空白色块的几率高一些
			// 初始化时，空白色块多一些，符合游戏的设定
			int t = rand()%(int(ColorTypeNum*1.5));  // 取随机数
			if (t<ColorTypeNum+1) 
				blocks[i][j].colorId = t; // 小方块的颜色序号
			else // 其他情况，都为空白颜色方块
				blocks[i][j].colorId = 0; // 小方块的颜色序号
			blocks[i][j].x = j*BlockSize; // 小方块左上角坐标
			blocks[i][j].y = i*BlockSize; // 
			blocks[i][j].i = i;   // 存储当前小方块在二维数组中的下标
			blocks[i][j].j = j; 
			if (blocks[i][j].colorId != 0)
				noZeroBlockNum++; // 统计随机产生的方块中，非零方块的个数
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
			fillrectangle(blocks[i][j].x,blocks[i][j].y,blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
		}
	}

	// 根据剩余时间，绘制一个倒计时进度条，进度条按最大时间maxTime秒绘制
	setlinecolor(RGB(255,0,0));
	setfillcolor(RGB(255,0,0));
	fillrectangle(0,BlockSize*(RowNum+0.2),remainTime*BlockSize*ColNum/maxTime,BlockSize*(RowNum+0.8));

	// 输出得分文字
	TCHAR s[80];
	setbkmode(TRANSPARENT);
	_stprintf(s, _T("%d"), score);	
	settextcolor(RGB(0,0,0)); 
	settextstyle(22, 0, _T("宋体"));
	outtextxy(BlockSize*(ColNum/2-0.1), BlockSize*(RowNum+0.2), s);
	// 输出一些游戏提示信息
	_stprintf(s, _T("点击空白方块，其十字区域有两个或以上相同颜色方块则消除；不能消除扣时间"));	
	outtextxy(BlockSize*(ColNum/15.0), BlockSize*(RowNum+1.2), s);
	_stprintf(s, _T("目前第 %d 关，时间结束前得分达到 %d 可进入下一关"),level,int(noZeroBlockNum*0.9));	
	outtextxy(BlockSize*(ColNum/5.0), BlockSize*(RowNum+2.2), s);

	FlushBatchDraw(); // 批量绘制
}	

void updateWithoutInput() // 和输入无关的更新
{
	// 倒计时减少
	finish = clock(); // 当前时刻
	// 从startup运行后，这一关游戏运行了多少秒
	double duration = (double)(finish - start) / CLOCKS_PER_SEC; 
	remainTime = totalTime-duration; // 游戏剩余的时间

	// 如果时间到了
	if (remainTime<=0) 
	{
		// 读一下文件记录，如果当前得分超过记录
		if (score > readRecordFile())
		{
			// 更新下得分记录
			writeRecordFile(score);

			// 显示恭喜超过记录
			show();
			settextcolor(RGB(255,0,0)); 
			settextstyle(100, 0, _T("黑体"));
			outtextxy(BlockSize*(ColNum/30.0), BlockSize*(RowNum/3.0), _T("恭喜打破得分记录"));
			FlushBatchDraw(); // 批量绘制
			Sleep(2000);
		}

		if (score>=int(noZeroBlockNum*0.9))
		{
			level ++; // 如果得分达到要求，消除掉非空白方块数目的90%，关卡加1
		}
		startup(); // 调用初始化函数，重新开始游戏
		return;
	}
}

void updateWithInput() // 和输入有关的更新
{
	if (remainTime<=0) // 时间到了，不要操作
		return;

	int i,j;
	MOUSEMSG m;		
	if (MouseHit())  
	{
		m = GetMouseMsg();  	
		if(m.uMsg == WM_LBUTTONDOWN) // 当按下鼠标左键时
		{
			// 获得点击的小方块的下标
			int clicked_i = int(m.y)/BlockSize;
			int clicked_j = int(m.x)/BlockSize;
			// 点击到下面提示部分了，不用处理，函数返回
			if (clicked_i>=RowNum) 
				return; 
			// 如果当前点击的不是空白方块，不需要处理，返回
			if (blocks[clicked_i][clicked_j].colorId!=0)
				return;

			show(); // 先显示其他方块，再绘制提示框，后绘制的在最前面
			// 被点击到的空白方块，绘制下填充灰色方块提示框
			drawBlockHint(clicked_i,clicked_j,RGB(100,100,100),1);			

			// 定义数组，存储上、下、左、右四个方向找到第一个不是空白的方块
			Block fourBlocks[4] = {blocks[clicked_i][clicked_j]}; // 初始化为这个空白的点击的方块
			int search; // 寻找下标

			// 向上找
			for (search=0;clicked_i-search>=0;search++)
			{
				if (blocks[clicked_i-search][clicked_j].colorId!=0) // 找到第一个颜色不是空白的方块
				{
					fourBlocks[0] = blocks[clicked_i-search][clicked_j]; // 赋给这个存储的数组
					break;
				}
			}
			// 向下找
			for (search=0;clicked_i+search<RowNum;search++)
			{
				if (blocks[clicked_i+search][clicked_j].colorId!=0) // 找到第一个颜色不是空白的方块
				{
					fourBlocks[1] = blocks[clicked_i+search][clicked_j]; // 赋给这个存储的数组
					break;
				}
			}
			// 向左找
			for (search=0;clicked_j-search>=0;search++)
			{
				if (blocks[clicked_i][clicked_j-search].colorId!=0) // 找到第一个颜色不是空白的方块
				{
					fourBlocks[2] = blocks[clicked_i][clicked_j-search]; // 赋给这个存储的数组
					break;
				}
			}
			// 向右找
			for (search=0;clicked_j+search<ColNum;search++)
			{
				if (blocks[clicked_i][clicked_j+search].colorId!=0) // 找到第一个颜色不是空白的方块
				{
					fourBlocks[3] = blocks[clicked_i][clicked_j+search]; // 赋给这个存储的数组
					break;
				}
			}

			// 统计fourBlocks的四个小方块，有没有同样颜色数目大于等于2的
			int colorStatistics[ColorTypeNum+1] = {0}; // 初始化个数为0
			int isBadClick = 1; // 假设点击的方块不合适，十字区域没有有效消除的方块
			for (i=1;i<ColorTypeNum+1;i++) // i=0是空白颜色，不要统计
			{
				for (j=0;j<4;j++) // 遍历fourBlocks
				{
					if (fourBlocks[j].colorId==i)
						colorStatistics[i]++; // 方块颜色为非零的i的话，把对应的统计个数+1
				}
				if (colorStatistics[i]>=2) // 如果这种颜色方块个数大于等于2
				{					
					isBadClick = 0; // 能消除了，这次点击是好的操作
					// 把对应十字区域要消除的方块颜色改成空白颜色
					for (j=0;j<4;j++) // 遍历fourBlocks
					{
						if (fourBlocks[j].colorId==i)
						{
							// 要消除的方块区域绘制提示框							
							drawBlockHint(fourBlocks[j].i,fourBlocks[j].j,RGB(0,0,0),0);	
							// 颜色序号设为0，也就是空白的灰白色
							blocks[fourBlocks[j].i][fourBlocks[j].j].colorId = 0; 
						}
					}
					score += colorStatistics[i]; // 得分加上消除的方块数
				}				
			}

			// 点击的方块，十字区域没有能消除的方块，为错误点击，减去10秒钟时间
			if (isBadClick==1) 
				totalTime -= 10; 

			FlushBatchDraw(); // 批量绘制
			Sleep(300); // 绘制好提示框后暂停300毫秒

		} // while 当按下鼠标左键时
	}
}

int main() // 主函数运行
{
	startup();  	
	while (1) 
	{
		show(); 
		updateWithoutInput(); 
		updateWithInput();  

	}
	closegraph(); 
	return 0;
}
