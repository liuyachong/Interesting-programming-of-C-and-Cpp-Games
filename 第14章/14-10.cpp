#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
using namespace std;

#define  WIDTH 800  
#define  HEIGHT 600

enum PlayerStatus // ö�����ͣ���Ϸ��ɫ���еĿ���״̬
{
	standleft,standright,runleft,runright,jumpleft,jumpright,die
};

// ���庯������������������������������
int randBetweenMinMax(int min,int max)
{
	int r = rand() % (max-min+1) + min;
	return r;
}

class Land  // ������
{
public:
	IMAGE im_land;  // ����ͼ��
	float left_x,right_x,top_y; // �����̻�һ���������ҡ�������
	float land_width,land_height; // һ�����ͼ��Ŀ�ȡ��߶�

	void initialize() // ��ʼ��
	{
		loadimage(&im_land, _T("land.png")); // �������ͼƬ
		land_width = im_land.getwidth(); // ��õ���ͼ��Ŀ���
		land_height = im_land.getheight();
		left_x = WIDTH/2;  // land��ʼ���ڻ������м䣬���þ�����ҽ�ɫ�ŵ���
		right_x = left_x+land_width;
		top_y = HEIGHT/2;
	}

	void draw(float px,float py)// ��ʾ�����Ϣ	
	{
		putimage(left_x-px,top_y-py,&im_land);  // ��ɫ���������Ƶ�����һ��ƫ����
	}
};

class Enemy  // ������
{
public:
	IMAGE im_enemy;  // ����ͼ��
	float x,y; // �����̻����˵���������
	float enemy_width,enemy_height; // ����ͼ��Ŀ�ȡ��߶�
	float x_min,x_max; // �����ƶ���x�������ֵ����Сֵ
	float vx; // ������x������ƶ��ٶ�

	void initialize() // ��ʼ��
	{
		loadimage(&im_enemy, _T("bat.png")); // �������-����-ͼƬ
		enemy_width = im_enemy.getwidth(); // ���ͼ��Ŀ���
		enemy_height = im_enemy.getheight();		
	}

	void draw(float px,float py)// ��ʾ�����Ϣ	
	{
		putimagePng(x-enemy_width/2-px,y-enemy_height/2-py,&im_enemy); // ��ɫ���������Ƶ�����һ�����ƫ����
	}

	void update()  // ������һ����Χ�ڣ������ƶ�
	{
		x += vx;
		if (x>x_max || x<x_min)
			vx = -vx;
	}
};

class Scene // ��Ϸ������
{
public:
	IMAGE im_bk;  // ����ͼ��	
	vector<Land> lands; // �������
	vector<Enemy> enemies; // �������
	int level; // ����浽�ڼ���
	int lastlevel; // ��һ���浽�ڼ���

	void draw(float px,float py)// ��ʾ�����Ϣ	
	{
		// ��ɫ���������Ʊ�����һ��ƫ����
		// ����ƫ����/20�����γ�������Ȳ��ǰ�󾰵��Ӿ�Ч��
		putimage(-px/20, -100-py/20, &im_bk);	// ��ʾ����	

		for (int i=0;i<lands.size();i++)
			lands[i].draw(px,py);  // �������е���

		for (int i=0;i<enemies.size();i++)
			enemies[i].draw(px,py);   // �������е���

		// ��ʾ���ǵڼ���
		TCHAR s[20]; // �ַ���
		setbkmode(TRANSPARENT); // ����͸����ʾ
		_stprintf(s, _T("�� %d ��"), level); // ���������ַ���
		settextcolor(RGB(0,50,200));  // ����������ɫ
		settextstyle(30, 0, _T("����")); // �������ִ�С������
		outtextxy(WIDTH*0.45, 30, s); // �������
	}

	void initialize() // ��ʼ��
	{
		loadimage(&im_bk,  _T("landscape1.png")); // ���뱳��ͼƬ

		if (lands.size()==0) // ��Ϸ�ſ�ʼ��Ĭ�ϵ�һ��
		{
			level = 1;
			lastlevel = 1;
		}
		// ��һ�زſ�ʼҪ��ʼ������������գ�������ʼ���������Ļ���������֮ǰ��ͼ������ʼ��
		if (lands.size()==0 || level > lastlevel)  
		{
			lands.clear();// ����յ�vector
			// ��һ��landҪ����Ϸ��ɫ�����·�
			Land land1;
			land1.initialize();
			lands.push_back(land1);

			for (int i=1;i<10+level*2;i++) // levelԽ���ܳ���Խ��
			{
				Land land2;
				land2.initialize();
				int r1 = randBetweenMinMax(1,30);
				if (r1>level) // levelԽ��x����Խ������
					land2.left_x = land1.left_x + land2.land_width;   
				else
					land2.left_x = land1.left_x + 2*land2.land_width;

				int r3 = randBetweenMinMax(1,20);
				if (r1>level)  // levelԽ��y����Խ������
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

			enemies.clear(); // ����ҲҪ��յ�
			// ��level�أ�һ����(level+3)/5 �����ˣ�Ҳ���ǵ�1��û�е��ˣ����������ӵ�����Ŀ
			int numEnemy = (level+3)/5;
			int idStep = lands.size()/(numEnemy+1);  // ������scene�о��ȷֲ���lands��
			for (int j=1;j<=numEnemy;j++)
			{
				Enemy enemy;
				enemy.initialize();
				int landId = j*idStep; 
				enemy.x = lands[landId].left_x + lands[landId].land_width/2;
				enemy.y = lands[landId].top_y - enemy.enemy_height;

				float movingRange = enemy.enemy_width*(3+level/15.0); // ���˵��ƶ���Χ���𽥱��
				enemy.x_min = enemy.x - movingRange; // �õ������ƶ���x��Χ
				enemy.x_max = enemy.x + movingRange;
				enemy.vx = 2 + level/10.0; // ����x�����ϵ��ƶ��ٶȣ��𽥱��

				enemies.push_back(enemy);
			}
		} // if (lands.size()==0 || level > lastlevel)  
	}
};

class Player  // ��ҿ��Ƶ���Ϸ��ɫ��
{
public:
	IMAGE im_show;  // ��ǰʱ��Ҫ��ʾ��ͼ��
	IMAGE im_standright; // ����վ��ͼ��
	IMAGE im_standleft; // ����վ��ͼ��
	IMAGE im_jumpright; // ���ҷ�����Ծͼ��
	IMAGE im_jumpleft; // ��������Ծͼ��
	vector <IMAGE> ims_runright; // ���ұ��ܵ�ͼ������
	vector <IMAGE> ims_runleft; // �����ܵ�ͼ������
	int animId;  // ����ѭ���������ŵ�id
	PlayerStatus playerStatus; // ��ǰ��״̬
	float x_left,y_bottom; // ���������꣬��ΪֻҪ���������͵�����ײ������
	float vx,vy; // �ٶ�
	float gravity; // �������ٶ�
	float width,height; // ͼƬ�Ŀ�ȡ��߶�

	void draw()// ��ʾ�����Ϣ	
	{
		// ��Ϸ����ʾ��ɫ����ɫ���������桢��������˶�
		putimagePng(WIDTH/2,HEIGHT/2-height,&im_show); 
	}

	void initialize() // ��ʼ��
	{
		ims_runleft.clear(); // ����յ�vector
		ims_runright.clear();
		loadimage(&im_standright, _T("standright.png")); // ��������վ��ͼƬ
		loadimage(&im_standleft, _T("standleft.png")); // ��������վ��ͼƬ
		loadimage(&im_jumpright, _T("jumpright.png")); // �������ҷ�����Ծͼ��
		loadimage(&im_jumpleft, _T("jumpleft.png")); // ������������Ծͼ��

		playerStatus = standright; // ��ʼΪ����վ������Ϸ״̬
		im_show = im_standright;  // ��ʼ��ʾ����վ����ͼƬ
		width = im_standright.getwidth(); // ���ͼ��Ŀ��ߣ����ж���ͼƬ��Сһ��
		height = im_standright.getheight();

		TCHAR filename[80];		
		for (int i=0;i<=7;i++) // �����ұ��ܵİ���ͼƬ������ӵ�ims_runright��
		{
			_stprintf(filename, _T("runright%d.png"),i);	
			IMAGE im;
			loadimage(&im,filename);
			ims_runright.push_back(im);
		}
		for (int i=0;i<=7;i++) // �������ܵİ���ͼƬ������ӵ�ims_runright��
		{
			_stprintf(filename, _T("runleft%d.png"),i);	
			IMAGE im;
			loadimage(&im,filename);
			ims_runleft.push_back(im);
		}

		animId = 0; // ����id��ʼ��Ϊ0

		updateXY(WIDTH/2,HEIGHT/2); // ��ʼ����ɫ���ڻ����м�
		vx = 10; // ˮƽ������ٶ�
		vy = 0;  // ��ֱ�����ٶȳ�ʼΪ0
		gravity = 3;  // �趨�������ٶ�
	}

	void updateXY(float mx,float my) // �������룬�����������
	{
		x_left = mx;
		y_bottom = my;
	}

	void runRight(Scene &scene) // ��Ϸ��ɫ���ұ���
	{
		x_left += vx; // ���������ӣ������ƶ�
		if (isNotOnAllLands(scene.lands,vy))  // �ƶ������κ�һ���������
		{
			im_show = im_jumpright;// �л�����������ͼƬ
			playerStatus = jumpright;// �л�����������״̬
			return;
		}

		if (playerStatus == jumpleft || playerStatus==jumpright) // ���������״̬
		{
			im_show = im_jumpright; // �ı�����Ϊ������������
		}
		else 
		{
			if (playerStatus != runright) // ���֮ǰ��ɫ״̬�������ұ���
			{
				playerStatus = runright; // �л�Ϊ���ұ���״̬
				animId = 0; // ��������id��ʼ��Ϊ0
			}
			else // ��ʾ֮ǰ�������ұ���״̬��
			{
				animId++; // ����ͼƬ��ʼ�л�
				if (animId>=ims_runright.size()) // ѭ���л�
					animId = 0;
			}
			im_show = ims_runright[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	 
		}
	}

	void runLeft(Scene &scene) // ��Ϸ��ɫ������
	{
		x_left -= vx; // ��������٣������ƶ�		
		if (isNotOnAllLands(scene.lands,vy))  // �ƶ������κ�һ���������
		{
			im_show = im_jumpleft; // �л�����������ͼƬ
			playerStatus = jumpleft; // �л�����������״̬
			return;
		}

		if (playerStatus == jumpleft || playerStatus==jumpright) // ���������״̬
		{
			im_show = im_jumpleft; // �ı�����Ϊ������������
		}
		else 
		{
			if (playerStatus != runleft) // ���֮ǰ��ɫ״̬����������
			{
				playerStatus = runleft; // �л�Ϊ������״̬
				animId = 0; // ��������id��ʼ��Ϊ0
			}
			else // ֮ǰ����������״̬��
			{
				animId++; // ����ͼƬ��ʼ�л�
				if (animId>=ims_runleft.size()) // ѭ���л�
					animId = 0;
			}
			im_show = ims_runleft[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	
		}	
	}

	void standStill() // ��Ϸ��ɫĬ��Ϊ��������Ҿ�ֹվ��
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

	void beginJump() // ����w�����Ϸ��������Ϸ��ɫ��Ծ�Ĵ���
	{
		if (playerStatus!=jumpleft && playerStatus!=jumpright) // �Ѿ��ڿ��еĻ�����Ҫ����
		{
			if (playerStatus==runleft || playerStatus == standleft)  // ����ǰ�������ܻ�����վ��״̬
			{
				im_show = im_jumpleft; // �л�����������ͼƬ
				playerStatus = jumpleft; // �л�����������״̬
			}
			else if (playerStatus==runright || playerStatus == standright)// ����ǰ�������ܻ�����վ��״̬
			{
				im_show = im_jumpright;// �л�����������ͼƬ
				playerStatus = jumpright;// �л�����������״̬
			}
			vy = -30; // ����ɫһ�����ϵĳ��ٶ�
		}
	}

	int isCollideEnemy(Enemy &enemy) // �жϽ�ɫ�Ƿ�͵�����ײ������Ƿ���1�����򷵻�0
	{
		float x_center = x_left + width/2;
		float y_center = y_bottom - height/2;
		if ( abs(enemy.x - x_center) <= enemy.enemy_width*0.5 
			&& abs(enemy.y  - y_center) <= enemy.enemy_height*0.5)
			return 1;
		else
			return 0;
	}

	// �ж���Ϸ��ɫ�Ƿ���վ���������ϣ�����ǵĻ�����1�����򷵻�0
	int isOnLand(Land &land,float ySpeed)  
	{
		float x_right = x_left + width;
		// �ж��Ƿ�վ�ڵ����ϣ�����Ҫ����player��y�����ٶ�������ٶȹ����п���ֱ�Ӵ�͸����
		if (ySpeed<=0) // y�᷽���ٶ�С��0����ʾ���������˶�������Ҫ�����ٶȵ�Ӱ��
			ySpeed = 0;
		if (land.left_x - x_left <= width*0.6 && x_right - land.right_x <= width*0.6 && abs(y_bottom-land.top_y)<=5+ySpeed)
			return 1;
		else
			return 0;
	}

	int isNotOnAllLands(vector<Land> &lands,float speed) // �ж�����Ƿ������еĵ�����
	{
		for (int i=0;i<lands.size();i++)
		{
			if (isOnLand(lands[i],speed))
				return 0; // ���κ�һ������ϣ�����0
		}
		return 1; // �������е����ϣ�����1
	}

	void updateYcoordinate(Scene &scene) // x�����ǰ����̿��Ƶģ���y������ÿ֡�Զ����µ�
	{
		if (playerStatus == jumpleft || playerStatus==jumpright) // ��ǰ���ڿ�����Ծ״̬
		{
			vy += gravity; // y�����ٶ�������Ӱ��仯
			y_bottom += vy;  // y����λ�����ٶ�Ӱ��仯
			for (int i=0;i<scene.lands.size();i++)   // �����е������
			{
				if (isOnLand(scene.lands[i],vy)) // �����������վ��һ��������ʱ
				{
					y_bottom = scene.lands[i].top_y; // ��֤�������ڵ�����
					if (playerStatus == jumpleft) // ����������غ��л�������վ������
						playerStatus = standleft;
					if (playerStatus == jumpright) // ����������غ��л�������վ������
						playerStatus = standright;
					break; // ����ѭ��������Ҫ�ٶ����������ж���
				}
			}
		}
	}
};

// һЩȫ�ֱ���
Player player;  // ������ҿ��Ƶ���Ϸ��ɫ����
Scene scene;  // ���峡��ȫ�ֶ���
Timer timer;  // ���ھ�ȷ��ʱ

void startup()  // ��ʼ��
{	
	srand(time(0)); // ��ʼ�����������
	scene.initialize();  // ������ʼ��
	player.initialize(); // ��ҽ�ɫ��ʼ��
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ��ʾ
{
	scene.draw(player.x_left-WIDTH/2,player.y_bottom-HEIGHT/2);   // ��ʾ���������Ϣ
	player.draw();  // ��ʾ��������Ϣ
	FlushBatchDraw(); // ��������
	timer.Sleep(50); // ��ͣ���ɺ���
}

void updateWithoutInput() // �������޹صĸ���
{
	player.updateYcoordinate(scene); // ��Ϸ��ɫy������ÿ֡�Զ����µ�

	int landSize = scene.lands.size(); // �����е���ĸ���
	// ��ɫ�ܵ����һ���������ˣ���Ϸʤ��
	if (player.x_left>scene.lands[landSize-1].left_x  
		&& abs(player.y_bottom-scene.lands[landSize-1].top_y)<=2) 
	{
		scene.lastlevel = scene.level; // ��¼lastlevel
		scene.level ++; // ������һ��
		scene.initialize();  // ������ʼ��
		player.initialize(); // ��ҽ�ɫ��ʼ��
	}
	else if (player.y_bottom>1.5*HEIGHT)  // ��ɫ�䵽���棬��Ϸʧ�ܣ����¿�ʼ
	{
		scene.lastlevel = scene.level; // ������û�������һ��
		scene.initialize();  // ������ʼ��
		player.initialize(); // ��ҽ�ɫ��ʼ��
	}

	for (int i=0;i<scene.enemies.size();i++)
	{
		scene.enemies[i].update(); // ���е����Զ�����λ��
		// �����һ���˺������ײ����Ϸʧ��
		if (player.isCollideEnemy(scene.enemies[i]))
		{
			scene.lastlevel = scene.level;
			scene.initialize();  // ������ʼ��
			player.initialize(); // ��ҽ�ɫ��ʼ��
		}
	}
}

void updateWithInput() // �������йصĸ���
{
	player.standStill(); // ��Ϸ��ɫĬ��Ϊ��������Ҿ�ֹվ��

	if (kbhit()) // ������ʱ���л���ɫ��ʾͼƬ������λ��
	{
		if (GetAsyncKeyState(VK_RIGHT)  || GetAsyncKeyState('D'))  // ����D�����ҷ����
		{
			player.runRight(scene);
		}
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// ����A���������
		{
			player.runLeft(scene);
		}
		if (GetAsyncKeyState(VK_UP)  || GetAsyncKeyState('W'))     // ����W�����Ϸ����
		{
			player.beginJump();
		}
	}
}

int main() // ������
{
	startup();  	// ��ʼ��
	while (1)       // һֱѭ��
	{
		show();  // ��ʾ
		updateWithoutInput(); // �������޹صĸ���
		updateWithInput();    // �������йصĸ���
	}
	return 0;
}