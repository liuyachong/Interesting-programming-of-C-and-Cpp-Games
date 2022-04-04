#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"  // ������ʾ��͸��ͨ����pngͼƬ
#define  WIDTH 560 // ������
#define  HEIGHT 800 // ����߶�
#define	 MaxBulletNum 200  // ����ӵ�����

class Rocket  // ��������
{
public:
	IMAGE im_rocket; // ���ͼ��
	float x,y; // �������
	float width,height; // ���ͼƬ�Ŀ�ȡ��߶�

	void draw()// ��ʾ��������Ϣ	
	{
		putimagePng(x - width/2,y-height/2,&im_rocket);  // ��Ϸ����ʾ���
	}

	void update(float mx,float my) // ���������������»����λ��
	{
		x = mx;
		y = my;
	}
};

class Bullet  // �����ӵ���
{
public:
	IMAGE im_bullet; // �ӵ�ͼ��
	float x,y; // �ӵ�����
	float vx,vy; // �ӵ��ٶ�
	float radius; // �ӽ�������ӵ��뾶��С

	void draw()// ��ʾ�ӵ�	
	{
		putimagePng(x - radius,y-radius,&im_bullet);  
	}

	void update() // �����ӵ���λ�á��ٶ�
	{
		x += vx;
		y += vy;
		if (x<=0 || x>=WIDTH)
			vx = -vx;
		if (y<=0 || y>=HEIGHT)
			vy = -vy;
	}
};

IMAGE im_bk,im_bullet,im_rocket;  // ����ͼ�����	
Bullet bullet[MaxBulletNum]; // �����ӵ���������
Rocket rocket;  // ����������
int bulletNum = 0; // �����ӵ��ĸ���

void startup()  //  ��ʼ������
{	
	srand(time(0)); // ��ʼ���������
	loadimage(&im_bk, _T("background.png")); // ���뱳��ͼƬ
	loadimage(&im_bullet, _T("bullet.png")); // �����ӵ�ͼƬ
	loadimage(&im_rocket, _T("rocket.png")); // ������ͼƬ

	// ��rocketһЩ��Ա������ʼ��
	rocket.im_rocket = im_rocket;  // ���û��ͼƬ
	rocket.width = im_rocket.getwidth(); // ���û�����
	rocket.height = im_rocket.getheight(); // ���û���߶�

	initgraph(WIDTH,HEIGHT); // �¿�һ������
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	putimage(0, 0, &im_bk);	// ��ʾ����	
	for (int i=0;i<bulletNum;i++)
		bullet[i].draw();  // ��ʾ���е��ӵ�
	rocket.draw();  // ��ʾ����������Ϣ
	FlushBatchDraw(); // ��������
	Sleep(10); // ��ͣ
}

void updateWithoutInput() // �������޹صĸ���
{
	static int lastSecond = 0; // ��¼ǰһ�γ��������˶�����
	static int nowSecond = 0; // ��¼��ǰ���������˶�����
	static clock_t start = clock(); // ��¼��һ������ʱ��
	clock_t now = clock(); // ��õ�ǰʱ��
	// �������Ŀǰһ�������˶�����
	nowSecond =( int(now - start) / CLOCKS_PER_SEC);
	if (nowSecond==lastSecond+2) // ʱ�����2���ӣ�����һ���ӵ�
	{
		lastSecond = nowSecond; // ������lastSecond����
		// ���û�г�������ӵ���Ŀ�����ƣ�����һ���µ��ӵ�
		if (bulletNum<MaxBulletNum)
		{
			bullet[bulletNum].x = WIDTH/2; // �ӵ���ʼλ��
			bullet[bulletNum].y = 10;
			float angle = (rand()/double(RAND_MAX)-0.5)*0.9*PI;
			float scalar = 2*rand()/double(RAND_MAX) + 2;
			bullet[bulletNum].vx = scalar*sin(angle); // �ӵ�����ٶ�
			bullet[bulletNum].vy = scalar*cos(angle);
			bullet[bulletNum].im_bullet = im_bullet;  // �����ӵ�ͼ��
			bullet[bulletNum].radius = im_bullet.getwidth()/2; // �ӵ��뾶ΪͼƬ���һ��
		}
		bulletNum++; // �ӵ���Ŀ��һ
	}

	for (int i=0;i<bulletNum;i++) // ���������е��ӵ�
		bullet[i].update(); // �����ӵ���λ�á��ٶ�
}

void updateWithInput()  // ��������صĸ���
{
	MOUSEMSG m;		// ���������Ϣ
	while (MouseHit())  // ��⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if(m.uMsg == WM_MOUSEMOVE)  // ������ƶ�ʱ			
			rocket.update(m.x,m.y); // �����λ�õ���������ڵ�λ��
	}	
}

int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // �ظ�����
	{
		show();  // ����
		updateWithoutInput();  // �������޹صĸ���
		updateWithInput();  // ��������صĸ���
	}
	return 0;
}