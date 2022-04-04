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

class Player  // ��ҿ��Ƶ���Ϸ��ɫ��
{
public:
	IMAGE im_show;  // ��ǰʱ��Ҫ��ʾ��ͼ��
	IMAGE im_standright; // ����վ��ͼ��
	IMAGE im_standleft; // ����վ��ͼ��
	vector <IMAGE> ims_runright; // ���ұ��ܵ�ͼ������
	int animId;  // ����ѭ���������ŵ�id

	PlayerStatus playerStatus; // ��ǰ��״̬

	float x_left,y_bottom; // ���������꣬��ΪֻҪ���������͵�����ײ������
	float vx,vy; // �ٶ�
	float width,height; // ͼƬ�Ŀ�ȡ��߶�

	void draw()// ��ʾ�����Ϣ	
	{
		putimagePng(x_left,y_bottom-height,&im_show);  // ��Ϸ����ʾ��ɫ
	}

	void initialize() // ��ʼ��
	{
		loadimage(&im_standright, _T("standright.png")); // ��������վ��ͼƬ
		loadimage(&im_standleft, _T("standleft.png")); // ��������վ��ͼƬ

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

		animId = 0; // ����id��ʼ��Ϊ0


		updateXY(WIDTH/2,HEIGHT/2); // ��ʼ����ɫ���ڻ����м�
		vx = 10; // ���ó��ٶ�
		vy = 10;
	}

	void updateXY(float mx,float my) // �������룬�����������
	{
		x_left = mx;
		y_bottom = my;
	}

	void runRight() // ��Ϸ��ɫ���ұ���
	{
		x_left += vx; // ���������ӣ������ƶ�
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
};

// һЩȫ�ֱ���
IMAGE im_land;  // ����ͼ��
IMAGE im_bk;  // ����ͼ��
Player player;  // ������ҿ��Ƶ���Ϸ��ɫ����
Timer timer;  // ���ھ�ȷ��ʱ

void startup()  // ��ʼ��
{	
	player.initialize(); // ��ҽ�ɫ��ʼ��
	loadimage(&im_land, _T("land.png")); // �������ͼƬ
	loadimage(&im_bk,  _T("landscape1.png")); // ���뱳��ͼƬ

	initgraph(WIDTH,HEIGHT); // �¿�һ������
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ��ʾ
{
	putimage(-100, -100, &im_bk);	// ��ʾ����	
	putimage(WIDTH/2,HEIGHT/2,&im_land);  // ����һ������
	player.draw();  // ��ʾ��������Ϣ
	FlushBatchDraw(); // ��������
	timer.Sleep(50); // ��ͣ���ɺ���
}

void updateWithoutInput() // �������޹صĸ���
{
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