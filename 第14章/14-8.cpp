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

class Scene // ��Ϸ������
{
public:
	IMAGE im_bk;  // ����ͼ��	
	vector<Land> lands; // �������

	void draw(float px,float py)// ��ʾ�����Ϣ	
	{
		// ��ɫ���������Ʊ�����һ��ƫ����
		// ����ƫ����/20�����γ�������Ȳ��ǰ�󾰵��Ӿ�Ч��
		putimage(-px/20, -100-py/20, &im_bk);	// ��ʾ����	
		for (int i=0;i<lands.size();i++)
		{
			lands[i].draw(px,py);  // �������е���
		}
	}

	void initialize() // ��ʼ��
	{
		loadimage(&im_bk,  _T("landscape1.png")); // ���뱳��ͼƬ
		lands.clear();// ����յ�vector

		// ��һ��landҪ����Ϸ��ɫ�����·�
		Land land1;
		land1.initialize();
		lands.push_back(land1);
		for (int i=1;i<20;i++) // �ٲ���һЩ�������
		{
			Land land2;
			land2.initialize();
			land2.left_x = land1.right_x + rand()%2 * land1.land_width;
			land2.right_x = land2.left_x + land2.land_width;
			land2.top_y = HEIGHT/2 + rand()%3 * HEIGHT/10;
			lands.push_back(land2);
			land1 = land2;
		}
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

	// �ж���Ϸ��ɫ�Ƿ���վ���������ϣ�����ǵĻ�����1�����򷵻�0
	int isOnLand(Land &land,float ySpeed)  
	{
		float x_right = x_left + width;
		// �ж��Ƿ�վ��ש���ϣ�����Ҫ����player��y�����ٶ�������ٶȹ����п���ֱ�Ӵ�͸����
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