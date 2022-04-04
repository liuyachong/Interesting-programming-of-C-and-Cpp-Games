#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#define B_SIZE 60 // 方块大小
#define B_NUM 8 // 方块个数，一共8*8个方块
#define LEVEL_TOTALNUM 5 // 一共多少关卡

struct Player // 结构体，用于记录玩家位置
{
	int i;
	int j;
};
Player player; // 玩家全局变量

// 用字符型三维数组，存储所有关的关卡信息
// e: empty    w: wall    t: target    b: box    a: achieved    p:player
char levels[LEVEL_TOTALNUM][B_NUM][B_NUM+1] = 
{
	{"wwwwwwww","wwwtbeew","weeeeeew","weeeeeew",
	"weeeeeew","wepbteew","weeewwww","wwwwwwww"}, // 第1关
	{"wwwwwwww","wwweewww","wpetbwww","weeebeww",
	"wewteeww","weeeeeww","weepwwww","wwwwwwww"}, // 第2关
	{"wwwwwwww","wwpeewww","weeweeww","webabeww",
	"weeteeww","wwetewww","wwwwwwww","wwwwwwww"}, // 第3关
	{"wwwwwwww","wwwwwwww","weeeewww","weeettew",
	"webbbpew","weewetww","wwwwwwww","wwwwwwww"}, // 第4关
	{"wwwwwwww","wwwwwwww","wwteewww","weewebpw",
	"weewewew","weaeebtw","weeeewww","wwwwwwww"}  // 第5关
};
int currentLevelNum = 0; // 当前玩到第几关
char level[B_NUM][B_NUM+1]; // 当前正在玩的关卡数据
int targetNum,achievedNum; // 目标位置个数、完成目标个数

void startup()  // 初始化函数
{
	initgraph(B_NUM*B_SIZE,B_NUM*B_SIZE); // 新开一个画面
	setbkcolor(RGB(150,150,150)); // 灰色背景
	BeginBatchDraw(); // 开始批量绘图
	int i,j;

	// 首先获得当前关的地图数据
	for (i=0;i<B_NUM;i++)
		for (j=0;j<B_NUM;j++)
			level[i][j] = levels[currentLevelNum][i][j];

	targetNum = 0; // 目标个数初始为0
	achievedNum = 0; // 完成目标个数初始为0
	// 对二维数组遍历
	for (i=0;i<B_NUM;i++)
		for (j=0;j<B_NUM;j++)
		{
			if (level[i][j]=='p') // 找到地图中player位置
			{
				player.i = i; // 设定player位置
				player.j = j; // 
				level[i][j]='e'; // 把地图元素变成空白empty
			}
			else if (level[i][j]=='t' || level[i][j]=='a' ) // 如果元素是target或achieved
				targetNum++; // 目标个数+1
		}
}

void show() // 绘制函数
{
	int i,j;
	cleardevice(); // 以背景颜色清空屏幕
	// 遍历关卡二维数组数据
	for (i=0;i<B_NUM;i++)
	{
		for (j=0;j<B_NUM;j++)
		{
			if (level[i][j]=='e') // empty 元素是空白区域
			{
				setfillcolor(RGB(150,150,150)); // 绘制灰色地面
				setlinecolor(RGB(150,150,150));
				fillrectangle(j*B_SIZE,i*B_SIZE,(j+1)*B_SIZE,(i+1)*B_SIZE);
			}
			else if (level[i][j]=='w')  // wall 元素是墙
			{
				setfillcolor(RGB(155,0,0));
				setlinecolor(RGB(150,150,150)); // 绘制淡红色、灰色线的方框
				fillrectangle(j*B_SIZE,i*B_SIZE,(j+1)*B_SIZE,(i+1)*B_SIZE);
			}
			else if (level[i][j]=='b') // box 元素是可移动的箱子
			{
				setfillcolor(RGB(255,255,0)); // 绘制一个黄色的方块
				setlinecolor(RGB(150,150,150));
				fillrectangle(j*B_SIZE,i*B_SIZE,(j+1)*B_SIZE,(i+1)*B_SIZE);
			}
			else if (level[i][j]=='t') // target 元素是目标
			{
				setfillcolor(RGB(250,250,250)); // 绘制一个白色的小方块
				fillrectangle((j+0.3)*B_SIZE,(i+0.3)*B_SIZE,
					(j+0.7)*B_SIZE,(i+0.7)*B_SIZE);
			}
			else if (level[i][j]=='a') // achieved 元素是已完成目标
			{
				setlinecolor(RGB(150,150,150));
				setfillcolor(RGB(255,255,0)); // 绘制一个黄色的方块
				fillrectangle(j*B_SIZE,i*B_SIZE,(j+1)*B_SIZE,(i+1)*B_SIZE);
				setfillcolor(RGB(250,250,250)); // 绘制一个白色的小方块
				fillrectangle((j+0.3)*B_SIZE,(i+0.3)*B_SIZE,
					(j+0.7)*B_SIZE,(i+0.7)*B_SIZE);
			}		
		}
	}
	// 以下绘制玩家，绘制一个人脸图案
	i = player.i; 
	j = player.j;
	setfillcolor(RGB(255,0,0));
	fillcircle((j+0.5)*B_SIZE,(i+0.5)*B_SIZE,0.4*B_SIZE);//一个红色圆脸
	setfillcolor(RGB(80,80,80));
	setlinecolor(RGB(80,80,80));
	fillcircle((j+0.3)*B_SIZE,(i+0.45)*B_SIZE,0.08*B_SIZE);//两个黑色眼睛
	fillcircle((j+0.7)*B_SIZE,(i+0.45)*B_SIZE,0.08*B_SIZE); 
	setlinestyle(PS_SOLID,3);
	line((j+0.35)*B_SIZE,(i+0.7)*B_SIZE,(j+0.65)*B_SIZE,(i+0.7)*B_SIZE);//深灰色嘴巴
	setlinestyle(PS_SOLID,1);

	if (achievedNum==targetNum) // 如完成目标个数==目标个数
	{
		setbkmode(TRANSPARENT); // 透明显示文字
		settextcolor(RGB(0,255,100)); // 设置字体颜色		
		TCHAR str[20];  // 定义字符数组
		if (currentLevelNum<LEVEL_TOTALNUM-1) // 还有未完成的关卡可以玩
		{			
			settextstyle(50, 0, _T("宋体")); // 设置字体大小、样式
			_stprintf(str, _T("开始第%d关"),currentLevelNum+2); // 提示开始第几关游戏
			outtextxy(120,160,str); // 显示游戏胜利文字
			outtextxy(10,250,_T("按空格键重玩当前关")); // 显示提示文字
		}
		else // 所有关卡都完成了
		{
			settextstyle(80, 0, _T("宋体")); // 设置字体大小、样式
			outtextxy(80,200,_T("游戏胜利")); // 显示游戏胜利文字
		}		
		FlushBatchDraw(); // 开始批量绘制
		Sleep(2500); // 提示信息显示暂停
	}
	FlushBatchDraw(); // 开始批量绘制
}

void update()  // 每帧更新运行
{
	if(kbhit() && (achievedNum<targetNum))  // 如果按键，并且游戏没有胜利
	{
		char input = getch(); // 获取按键
		if (input==' ') // 如果按下空格键，这一关重新开始
			startup(); 
		if (input=='a' || input=='s' || input=='d' || input=='w') // 如果是有效按键
		{
			int goal_i = player.i; // 移动的目标位置
			int goal_j = player.j;
			int goalNext_i = goal_i; // 目标位置再向前的一个位置
			int goalNext_j = goal_j;
			// 根据用户的不同按键输入，获得目标位置、再向前的一个位置
			if (input=='a') // 向左
			{
				goal_j = player.j -1 ; // 目标位置在玩家位置的左边
				goalNext_j = goal_j-1; // 目标的下一个位置，在其再左边
			}
			else if (input=='d') // 向右
			{
				goal_j = player.j +1 ; // 目标位置在玩家位置的右边 
				goalNext_j = goal_j+1; // 目标的下一个位置，在其再右边
			}
			else if (input=='s') // 向下
			{
				goal_i = player.i+1; // 目标位置在玩家位置的下边 
				goalNext_i = goal_i+1; // 目标的下一个位置，在其再下边 
			}
			else if (input=='w') // 向上
			{
				goal_i = player.i-1; // 目标位置在玩家位置的上边 
				goalNext_i = goal_i-1; // 目标的下一个位置，在其再上边 
			}

			// 根据不同地图元素的情况，判断如何移动角色和更新地图元素	
			if (level[goal_i][goal_j]=='e' || level[goal_i][goal_j]=='t' ) 
			{	// 如果目标位置是empty，或者target
				player.i = goal_i; // 玩家移动到目标位置
				player.j = goal_j;  			
			}
			else if (level[goal_i][goal_j]=='b' && level[goalNext_i][goalNext_j]=='e' ) 
			{	// 如果目标位置是box，再前面一个是empty
				player.i = goal_i; // 玩家移动到目标位置
				player.j = goal_j;	  
				level[goal_i][goal_j]='e';  // 目标位置变成empty
				level[goalNext_i][goalNext_j]='b';	 // 再前面变成box
			}
			else if (level[goal_i][goal_j]=='b' && level[goalNext_i][goalNext_j]=='t') 
			{	// 如果目标位置是box，再前面一个是target
				player.i = goal_i; // 玩家移动到目标位置
				player.j = goal_j;	
				level[goal_i][goal_j] = 'e';  // 目标位置变成empty 
				level[goalNext_i][goalNext_j] = 'a';	// 再前面变成achieved
			}
			else if (level[goal_i][goal_j]=='a' && level[goalNext_i][goalNext_j]== 'e') 
			{	// 如果目标位置是achieved，再前面一个是empty
				player.i = goal_i; // 玩家移动到目标位置
				player.j = goal_j;  	
				level[goal_i][goal_j] = 't';  // 目标位置变成target 
				level[goalNext_i][goalNext_j] = 'b'; // 再前面变成box 	
			}
			else if (level[goal_i][goal_j]=='a' && level[goalNext_i][goalNext_j]== 't') 
			{	// 如果目标位置是achieved，再前面一个是target
				player.i = goal_i; // 玩家移动到目标位置
				player.j = goal_j;
				level[goal_i][goal_j] = 't';  // 目标位置变成target  
				level[goalNext_i][goalNext_j] = 'a'; // 再前面变成achieved  	
			}
			else // 其他情况都推不动
				return; // 不做任何处理，函数直接返回
		}

		achievedNum = 0; // 完成目标个数，初始为0
		int i,j;
		for (i=0;i<B_NUM;i++) // 对二维数组遍历
			for (j=0;j<B_NUM;j++) // 
				if (level[i][j]=='a') // 如果元素是achieved
					achievedNum++; // 完成目标个数+1

		if (achievedNum==targetNum) // 如完完成当前关卡了
		{
			show(); // 调用显示信息，显示游戏胜利画面
			if (currentLevelNum<LEVEL_TOTALNUM-1)
			{
				currentLevelNum++;  // 进入下一关
				startup(); // 开始下一关卡的初始化
			}
		}
	}
}

int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 游戏主循环
	{
		show();		// 绘制
		update();   // 更新
	}
	return 0;
}