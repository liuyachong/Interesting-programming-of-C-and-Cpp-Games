#include <graphics.h>  
#include <conio.h>
#include <time.h>
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

// 定义函数，随机生成两个整数间的任意整数
int randBetweenMinMax(int min,int max)
{
	int r = rand() % (max-min+1) + min;
	return r;
}

class Land  // 地面类
{
public:
	IMAGE im_land;  // 地面图像
	float left_x,right_x,top_y; // 用来刻画一块地面的左、右、上坐标
	float land_width,land_height; // 一块地面图像的宽度、高度

	void initialize() // 初始化
	{
		loadimage(&im_land, _T("land.png")); // 导入地面图片
		land_width = im_land.getwidth(); // 获得地面图像的宽、高
		land_height = im_land.getheight();
		left_x = WIDTH/2;  // land初始化在画面正中间，正好就在玩家角色脚底下
		right_x = left_x+land_width;
		top_y = HEIGHT/2;
	}

	void draw(float px,float py)// 显示相关信息	
	{
		putimage(left_x-px,top_y-py,&im_land);  // 角色不动，绘制地面有一个偏移量
	}
};

class Enemy  // 敌人类
{
public:
	IMAGE im_enemy;  // 敌人图像
	float x,y; // 用来刻画敌人的中心坐标
	float enemy_width,enemy_height; // 敌人图像的宽度、高度
	float x_min,x_max; // 敌人移动的x坐标最大值、最小值
	float vx; // 敌人在x方向的移动速度

	void initialize() // 初始化
	{
		loadimage(&im_enemy, _T("bat.png")); // 导入敌人-蝙蝠-图片
		enemy_width = im_enemy.getwidth(); // 获得图像的宽、高
		enemy_height = im_enemy.getheight();		
	}

	void draw(float px,float py)// 显示相关信息	
	{
		putimagePng(x-enemy_width/2-px,y-enemy_height/2-py,&im_enemy); // 角色不动，绘制敌人有一个相对偏移量
	}

	void update()  // 敌人在一定范围内，左右移动
	{
		x += vx;
		if (x>x_max || x<x_min)
			vx = -vx;
	}
};

class Scene // 游戏场景类
{
public:
	IMAGE im_bk;  // 背景图像	
	vector<Land> lands; // 多个地面
	vector<Enemy> enemies; // 多个敌人
	int level; // 玩家玩到第几关
	int lastlevel; // 上一次玩到第几关

	void draw(float px,float py)// 显示相关信息	
	{
		// 角色不动，绘制背景有一个偏移量
		// 背景偏移量/20，就形成了有深度差的前后景的视觉效果
		putimage(-px/20, -100-py/20, &im_bk);	// 显示背景	

		for (int i=0;i<lands.size();i++)
			lands[i].draw(px,py);  // 绘制所有地面

		for (int i=0;i<enemies.size();i++)
			enemies[i].draw(px,py);   // 绘制所有敌人

		// 显示这是第几关
		TCHAR s[20]; // 字符串
		setbkmode(TRANSPARENT); // 文字透明显示
		_stprintf(s, _T("第 %d 关"), level); // 生成文字字符串
		settextcolor(RGB(0,50,200));  // 设置文字颜色
		settextstyle(30, 0, _T("黑体")); // 设置文字大小、字体
		outtextxy(WIDTH*0.45, 30, s); // 输出文字
	}

	void initialize() // 初始化
	{
		loadimage(&im_bk,  _T("landscape1.png")); // 导入背景图片

		if (lands.size()==0) // 游戏才开始，默认第一关
		{
			level = 1;
			lastlevel = 1;
		}
		// 第一关才开始要初始化。升级后，清空，继续开始。不升级的话，还是用之前地图继续开始。
		if (lands.size()==0 || level > lastlevel)  
		{
			lands.clear();// 先清空掉vector
			// 第一个land要在游戏角色的正下方
			Land land1;
			land1.initialize();
			lands.push_back(land1);

			for (int i=1;i<10+level*2;i++) // level越大，总长度越长
			{
				Land land2;
				land2.initialize();
				int r1 = randBetweenMinMax(1,30);
				if (r1>level) // level越大，x方向越不连续
					land2.left_x = land1.left_x + land2.land_width;   
				else
					land2.left_x = land1.left_x + 2*land2.land_width;

				int r3 = randBetweenMinMax(1,20);
				if (r1>level)  // level越大，y方向越不连续
					land2.top_y = land1.top_y;
				else
				{
					int r3 = randBetweenMinMax(-1,1);
					land2.top_y = WIDTH/2 + HEIGHT/10 * r3;
				}

				land2.right_x = land2.left_x + land2.land_width;

				lands.push_back(land2);
				land1 = land2;
			}

			enemies.clear(); // 敌人也要清空掉
			// 第level关，一共有(level+3)/5 个敌人，也就是第1关没有敌人，后面逐渐增加敌人数目
			int numEnemy = (level+3)/5;
			int idStep = lands.size()/(numEnemy+1);  // 敌人在scene中均匀分布到lands上
			for (int j=1;j<=numEnemy;j++)
			{
				Enemy enemy;
				enemy.initialize();
				int landId = j*idStep; 
				enemy.x = lands[landId].left_x + lands[landId].land_width/2;
				enemy.y = lands[landId].top_y - enemy.enemy_height;

				float movingRange = enemy.enemy_width*(3+level/15.0); // 敌人的移动范围，逐渐变大
				enemy.x_min = enemy.x - movingRange; // 得到敌人移动的x范围
				enemy.x_max = enemy.x + movingRange;
				enemy.vx = 2 + level/10.0; // 敌人x方向上的移动速度，逐渐变快

				enemies.push_back(enemy);
			}
		} // if (lands.size()==0 || level > lastlevel)  
	}
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
		// 游戏中显示角色，角色不动，地面、背景相对运动
		putimagePng(WIDTH/2,HEIGHT/2-height,&im_show); 
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

	void runRight(Scene &scene) // 游戏角色向右奔跑
	{
		x_left += vx; // 横坐标增加，向右移动
		if (isNotOnAllLands(scene.lands,vy))  // 移动后不在任何一块地面上了
		{
			im_show = im_jumpright;// 切换到向右起跳图片
			playerStatus = jumpright;// 切换到向右起跳状态
			return;
		}

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

	void runLeft(Scene &scene) // 游戏角色向左奔跑
	{
		x_left -= vx; // 横坐标减少，向左移动		
		if (isNotOnAllLands(scene.lands,vy))  // 移动后不在任何一块地面上了
		{
			im_show = im_jumpleft; // 切换到向左起跳图片
			playerStatus = jumpleft; // 切换到向左起跳状态
			return;
		}

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

	int isCollideEnemy(Enemy &enemy) // 判断角色是否和敌人碰撞，如果是返回1，否则返回0
	{
		float x_center = x_left + width/2;
		float y_center = y_bottom - height/2;
		if ( abs(enemy.x - x_center) <= enemy.enemy_width*0.5 
			&& abs(enemy.y  - y_center) <= enemy.enemy_height*0.5)
			return 1;
		else
			return 0;
	}

	// 判断游戏角色是否正站在这块地面上，如果是的话返回1，否则返回0
	int isOnLand(Land &land,float ySpeed)  
	{
		float x_right = x_left + width;
		// 判断是否站在地面上，还需要考虑player的y方向速度情况，速度过快有可能直接穿透地面
		if (ySpeed<=0) // y轴方向速度小于0，表示正在向上运动，不需要考虑速度的影响
			ySpeed = 0;
		if (land.left_x - x_left <= width*0.6 && x_right - land.right_x <= width*0.6 && abs(y_bottom-land.top_y)<=5+ySpeed)
			return 1;
		else
			return 0;
	}

	int isNotOnAllLands(vector<Land> &lands,float speed) // 判断玩家是否不在所有的地面上
	{
		for (int i=0;i<lands.size();i++)
		{
			if (isOnLand(lands[i],speed))
				return 0; // 在任何一块地面上，返回0
		}
		return 1; // 不在所有地面上，返回1
	}

	void updateYcoordinate(Scene &scene) // x坐标是按键盘控制的，而y坐标是每帧自动更新的
	{
		if (playerStatus == jumpleft || playerStatus==jumpright) // 当前是在空中跳跃状态
		{
			vy += gravity; // y方向速度受重力影响变化
			y_bottom += vy;  // y方向位置受速度影响变化
			for (int i=0;i<scene.lands.size();i++)   // 对所有地面遍历
			{
				if (isOnLand(scene.lands[i],vy)) // 当火柴人正好站在一个地面上时
				{
					y_bottom = scene.lands[i].top_y; // 保证正好落在地面上
					if (playerStatus == jumpleft) // 向左跳，落地后切换到向左站立方向
						playerStatus = standleft;
					if (playerStatus == jumpright) // 向右跳，落地后切换到向右站立方向
						playerStatus = standright;
					break; // 跳出循环，不需要再对其他地面判断了
				}
			}
		}
	}
};

// 一些全局变量
Player player;  // 定义玩家控制的游戏角色对象
Scene scene;  // 定义场景全局对象
Timer timer;  // 用于精确延时

void startup()  // 初始化
{	
	srand(time(0)); // 初始化随机数种子
	scene.initialize();  // 场景初始化
	player.initialize(); // 玩家角色初始化
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 显示
{
	scene.draw(player.x_left-WIDTH/2,player.y_bottom-HEIGHT/2);   // 显示场景相关信息
	player.draw();  // 显示玩家相关信息
	FlushBatchDraw(); // 批量绘制
	timer.Sleep(50); // 暂停若干毫秒
}

void updateWithoutInput() // 和输入无关的更新
{
	player.updateYcoordinate(scene); // 游戏角色y坐标是每帧自动更新的

	int landSize = scene.lands.size(); // 场景中地面的个数
	// 角色跑到最后一个地面上了，游戏胜利
	if (player.x_left>scene.lands[landSize-1].left_x  
		&& abs(player.y_bottom-scene.lands[landSize-1].top_y)<=2) 
	{
		scene.lastlevel = scene.level; // 记录lastlevel
		scene.level ++; // 进入下一关
		scene.initialize();  // 场景初始化
		player.initialize(); // 玩家角色初始化
	}
	else if (player.y_bottom>1.5*HEIGHT)  // 角色落到底面，游戏失败，重新开始
	{
		scene.lastlevel = scene.level; // 重新玩没有玩过的一关
		scene.initialize();  // 场景初始化
		player.initialize(); // 玩家角色初始化
	}

	for (int i=0;i<scene.enemies.size();i++)
	{
		scene.enemies[i].update(); // 所有敌人自动更新位置
		// 如果任一敌人和玩家碰撞，游戏失败
		if (player.isCollideEnemy(scene.enemies[i]))
		{
			scene.lastlevel = scene.level;
			scene.initialize();  // 场景初始化
			player.initialize(); // 玩家角色初始化
		}
	}
}

void updateWithInput() // 和输入有关的更新
{
	player.standStill(); // 游戏角色默认为向左或向右静止站立

	if (kbhit()) // 当按键时，切换角色显示图片，更改位置
	{
		if (GetAsyncKeyState(VK_RIGHT)  || GetAsyncKeyState('D'))  // 按下D键或右方向键
		{
			player.runRight(scene);
		}
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// 按下A键或左方向键
		{
			player.runLeft(scene);
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