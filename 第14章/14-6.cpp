#include <graphics.h>  
#include <conio.h>
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

	void draw()// ��ʾ�����Ϣ	
	{
		putimage(left_x,top_y,&im_land);  // ����һ������
	}
};

class Scene // ��Ϸ������
{
public:
	IMAGE im_bk;  // ����ͼ��	
	vector<Land> lands; // �������

	void draw()// ��ʾ�����Ϣ	
	{
		putimage(-100, -100, &im_bk);	// ��ʾ����	
		for (int i=0;i<lands.size();i++)
		{
			lands[i].draw();  // �������е���
		}
	}

	void initialize() // ��ʼ��
	{
		loadimage(&im_bk,  _T("landscape1.png")); // ���뱳��ͼƬ
		for (int i=1;i<=6;i++) // ����ͳ�ʼ���������
		{
			Land land;
			land.initialize();
			land.left_x = i*land.land_width;
			land.top_y = (i-1)/6.0 * HEIGHT;
			lands.push_back(land);
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
		putimagePng(x_left,y_bottom-height,&im_show);  // ��Ϸ����ʾ��ɫ
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

	void runRight() // ��Ϸ��ɫ���ұ���
	{
		x_left += vx; // ���������ӣ������ƶ�
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

	void runLeft() // ��Ϸ��ɫ������
	{
		x_left -= vx; // ��������٣������ƶ�
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

	void updateYcoordinate() // x�����ǰ����̿��Ƶģ���y������ÿ֡�Զ����µ�
	{
		if (playerStatus == jumpleft || playerStatus==jumpright) // ��ǰ���ڿ�����Ծ״̬
		{
			vy += gravity; // y�����ٶ�������Ӱ��仯
			y_bottom += vy;  // y����λ�����ٶ�Ӱ��仯

			if (y_bottom>HEIGHT/2) // ��ֹ�䵽����֮��
			{
				y_bottom = HEIGHT/2; // ��֤�������ڵ�����
				if (playerStatus == jumpleft) // ����������غ��л�������վ������
					playerStatus = standleft;
				if (playerStatus == jumpright) // ����������غ��л�������վ������
					playerStatus = standright;
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
	scene.initialize();  // ������ʼ��
	player.initialize(); // ��ҽ�ɫ��ʼ��
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ��ʾ
{
	scene.draw();   // ��ʾ���������Ϣ
	player.draw();  // ��ʾ��������Ϣ
	FlushBatchDraw(); // ��������
	timer.Sleep(50); // ��ͣ���ɺ���
}

void updateWithoutInput() // �������޹صĸ���
{
	player.updateYcoordinate(); // ��Ϸ��ɫy������ÿ֡�Զ����µ�
}

void updateWithInput() // �������йصĸ���
{
	player.standStill(); // ��Ϸ��ɫĬ��Ϊ��������Ҿ�ֹվ��

	if (kbhit()) // ������ʱ���л���ɫ��ʾͼƬ������λ��
	{
		if (GetAsyncKeyState(VK_RIGHT)  || GetAsyncKeyState('D'))  // ����D�����ҷ����
		{
			player.runRight();
		}
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// ����A���������
		{
			player.runLeft();
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