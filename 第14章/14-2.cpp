#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"
#include "Timer.h"
#define  WIDTH 800  
#define  HEIGHT 600

class Player  // ��ҿ��Ƶ���Ϸ��ɫ��
{
public:
	IMAGE im_show;  // ��ǰʱ��Ҫ��ʾ��ͼ��
	float x_left,y_bottom; // ���������꣬��ΪֻҪ���������͵�����ײ������
	float vx,vy; // �ٶ�
	float width,height; // ͼƬ�Ŀ�ȡ��߶�

	void draw()// ��ʾ�����Ϣ	
	{
		putimagePng(x_left,y_bottom-height,&im_show);  // ��Ϸ����ʾ��ɫ
	}

	void initialize() // ��ʼ��
	{
		loadimage(&im_show, _T("standright.png")); // ��������վ��ͼƬ
		width = im_show.getwidth(); // ���ͼ��Ŀ��ߣ����ж���ͼƬ��Сһ��
		height = im_show.getheight();
		updateXY(WIDTH/2,HEIGHT/2); // ��ʼ����ɫ���ڻ����м�
		vx = 10; // ���ó��ٶ�
		vy = 10;
	}

	void updateXY(float mx,float my) // �������룬�����������
	{
		x_left = mx;
		y_bottom = my;
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
	if (kbhit()) // ������ʱ
	{
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))  // ����A���������
		{
			player.x_left -= player.vx; // �����ƶ�
		}
		if (GetAsyncKeyState(VK_RIGHT)  || GetAsyncKeyState('D')) // ����D�����ҷ����
		{
			player.x_left += player.vx; // �����ƶ�
		}
		if (GetAsyncKeyState(VK_UP)  || GetAsyncKeyState('W'))    // ����W�����Ϸ����
		{
			player.y_bottom -= player.vy; // �����ƶ�
		}
		if (GetAsyncKeyState(VK_DOWN)  || GetAsyncKeyState('S'))  // ����S�����·����
		{
			player.y_bottom += player.vy; // �����ƶ�
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