#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
using namespace std;

#define  WIDTH 800  
#define  HEIGHT 600

enum PlayerStatus // 枚举类型，游戏角色所有的可能状态
{
	standleft,standright,runleft,runright,jumpleft,jumpright,die
};

class Player  // 玩家控制的游戏角色类
{
public:
	IMAGE im_show;  // 当前时刻要显示的图像
	IMAGE im_standright; // 向右站立图像
	IMAGE im_standleft; // 向左站立图像
	IMAGE im_jumpright; // 向右方向跳跃图像
	IMAGE im_jumpleft; // 向左方向跳跃图像
	vector <IMAGE> ims_runright; // 向右奔跑的图像序列
	vector <IMAGE> ims_runleft; // 向左奔跑的图像序列
	int animId;  // 用于循环动画播放的id
	PlayerStatus playerStatus; // 当前的状态
	float x_left,y_bottom; // 这两个坐标，因为只要用这两个和地面碰撞就行了
	float vx,vy; // 速度
	float gravity; // 重力加速度
	float width,height; // 图片的宽度、高度

	void draw()// 显示相关信息	
	{
		putimagePng(x_left,y_bottom-height,&im_show);  // 游戏中显示角色
	}

	void initialize() // 初始化
	{
		ims_runleft.clear(); // 先清空掉vector
		ims_runright.clear();
		loadimage(&im_standright, _T("standright.png")); // 导入向右站立图片
		loadimage(&im_standleft, _T("standleft.png")); // 导入向左站立图片
		loadimage(&im_jumpright, _T("jumpright.png")); // 导入向右方向跳跃图像
		loadimage(&im_jumpleft, _T("jumpleft.png")); // 导入向左方向跳跃图像
		
		playerStatus = standright; // 初始为向右站立的游戏状态
		im_show = im_standright;  // 初始显示向右站立的图片
		width = im_standright.getwidth(); // 获得图像的宽、高，所有动画图片大小一样
		height = im_standright.getheight();

		TCHAR filename[80];		
		for (int i=0;i<=7;i++) // 把向右奔跑的八张图片对象添加到ims_runright中
		{
			_stprintf(filename, _T("runright%d.png"),i);	
			IMAGE im;
			loadimage(&im,filename);
			ims_runright.push_back(im);
		}
		for (int i=0;i<=7;i++) // 把向左奔跑的八张图片对象添加到ims_runright中
		{
			_stprintf(filename, _T("runleft%d.png"),i);	
			IMAGE im;
			loadimage(&im,filename);
			ims_runleft.push_back(im);
		}

		animId = 0; // 动画id开始设为0

		updateXY(WIDTH/2,HEIGHT/2); // 开始将角色放在画面中间
		vx = 10; // 水平方向初速度
		vy = 0;  // 竖直方向速度初始为0
		gravity = 3;  // 设定重力加速度
	}

	void updateXY(float mx,float my) // 根据输入，更新玩家坐标
	{
		x_left = mx;
		y_bottom = my;
	}

	void runRight() // 游戏角色向右奔跑
	{
		x_left += vx; // 横坐标增加，向右移动
		if (playerStatus == jumpleft || playerStatus==jumpright) // 如果是起跳状态
		{
			im_show = im_jumpright; // 改变造型为向右起跳造型
		}
		else 
		{
			if (playerStatus != runright) // 如果之前角色状态不是向右奔跑
			{
				playerStatus = runright; // 切换为向右奔跑状态
				animId = 0; // 动画播放id初始化为0
			}
			else // 表示之前就是向右奔跑状态了
			{
				animId++; // 动画图片开始切换
				if (animId>=ims_runright.size()) // 循环切换
					animId = 0;
			}
			im_show = ims_runright[animId];	 // 设置要显示的对应图片	 
		}
	}

	void runLeft() // 游戏角色向左奔跑
	{
		x_left -= vx; // 横坐标减少，向左移动
		if (playerStatus == jumpleft || playerStatus==jumpright) // 如果是起跳状态
		{
			im_show = im_jumpleft; // 改变造型为向左起跳造型
		}
		else 
		{
			if (playerStatus != runleft) // 如果之前角色状态不是向左奔跑
			{
				playerStatus = runleft; // 切换为向左奔跑状态
				animId = 0; // 动画播放id初始化为0
			}
			else // 之前就是向左奔跑状态了
			{
				animId++; // 动画图片开始切换
				if (animId>=ims_runleft.size()) // 循环切换
					animId = 0;
			}
			im_show = ims_runleft[animId];	 // 设置要显示的对应图片	
		}	
	}
	
	void standStill() // 游戏角色默认为向左或向右静止站立
	{
		if (playerStatus==runleft || playerStatus == standleft)
		{
			im_show = im_standleft;
		}
		else if (playerStatus==runright || playerStatus == standright)
		{
			im_show = im_standright;
		}
	}

	void beginJump() // 按下w或向上方向键后，游戏角色跳跃的处理
	{
		if (playerStatus!=jumpleft && playerStatus!=jumpright) // 已经在空中的话，不要起跳
		{
			if (playerStatus==runleft || playerStatus == standleft)  // 起跳前是向左跑或向左站立状态
			{
				im_show = im_jumpleft; // 切换到向左起跳图片
				playerStatus = jumpleft; // 切换到向左起跳状态
			}
			else if (playerStatus==runright || playerStatus == standright)// 起跳前是向右跑或向右站立状态
			{
				im_show = im_jumpright;// 切换到向右起跳图片
				playerStatus = jumpright;// 切换到向右起跳状态
			}
			vy = -30; // 给角色一个向上的初速度
		}
	}

	void updateYcoordinate() // x坐标是按键盘控制的，而y坐标是每帧自动更新的
	{
		if (playerStatus == jumpleft || playerStatus==jumpright) // 当前是在空中跳跃状态
		{
			vy += gravity; // y方向速度受重力影响变化
			y_bottom += vy;  // y方向位置受速度影响变化

			if (y_bottom>HEIGHT/2) // 防止落到地面之下
			{
				y_bottom = HEIGHT/2; // 保证正好落在地面上
				if (playerStatus == jumpleft) // 向左跳，落地后切换到向左站立方向
					playerStatus = standleft;
				if (playerStatus == jumpright) // 向右跳，落地后切换到向右站立方向
					playerStatus = standright;
			}
		}
	}
};

// 一些全局变量
IMAGE im_land;  // 地面图像
IMAGE im_bk;  // 背景图像
Player player;  // 定义玩家控制的游戏角色对象
Timer timer;  // 用于精确延时

void startup()  // 初始化
{	
	player.initialize(); // 玩家角色初始化
	loadimage(&im_land, _T("land.png")); // 导入地面图片
	loadimage(&im_bk,  _T("landscape1.png")); // 导入背景图片

	initgraph(WIDTH,HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 显示
{
	putimage(-100, -100, &im_bk);	// 显示背景	
	putimage(WIDTH/2,HEIGHT/2,&im_land);  // 绘制一个地面
	player.draw();  // 显示玩家相关信息
	FlushBatchDraw(); // 批量绘制
	timer.Sleep(50); // 暂停若干毫秒
}

void updateWithoutInput() // 和输入无关的更新
{
	player.updateYcoordinate(); // 游戏角色y坐标是每帧自动更新的
}

void updateWithInput() // 和输入有关的更新
{
	player.standStill(); // 游戏角色默认为向左或向右静止站立

	if (kbhit()) // 当按键时，切换角色显示图片，更改位置
	{
		if (GetAsyncKeyState(VK_RIGHT)  || GetAsyncKeyState('D'))  // 按下D键或右方向键
		{
			player.runRight();
		}
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// 按下A键或左方向键
		{
			player.runLeft();
		}
		if (GetAsyncKeyState(VK_UP)  || GetAsyncKeyState('W'))     // 按下W键或上方向键
		{
			player.beginJump();
		}
	}
}

int main() // 主函数
{
	startup();  	// 初始化
	while (1)       // 一直循环
	{
		show();  // 显示
		updateWithoutInput(); // 与输入无关的更新
		updateWithInput();    // 与输入有关的更新
	}
	return 0;
}