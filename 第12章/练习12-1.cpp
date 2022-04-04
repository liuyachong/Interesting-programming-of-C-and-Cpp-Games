#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"  // ������ʾ��͸��ͨ����pngͼƬ
#define  WIDTH 560 // ������
#define  HEIGHT 800 // ����߶�
#define	 MaxBulletNum 200  // �����ӵ�����

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

IMAGE im_bk,im_bullet;  // ����ͼ�����	
Bullet bullet[MaxBulletNum]; // �����ӵ���������

void startup()  //  ��ʼ������
{	
	loadimage(&im_bk, _T("background.png")); // ���뱳��ͼƬ
	loadimage(&im_bullet, _T("bullet.png")); // �����ӵ�ͼƬ
	for (int i=0;i<MaxBulletNum;i++) // �������ӵ���ʼ��
	{
		bullet[i].x = WIDTH/2; // �ӵ���ʼλ��
		bullet[i].y = 10;
		float angle = (rand()/double(RAND_MAX)-0.5)*0.9*PI;
		float scalar = 2*rand()/double(RAND_MAX) + 2;
		bullet[i].vx = scalar*sin(angle); // �ӵ��ٶ�
		bullet[i].vy = scalar*cos(angle);
		bullet[i].im_bullet = im_bullet;  // �����ӵ�ͼ��
		bullet[i].radius = im_bullet.getwidth()/2; // �����ӵ��İ뾶Ϊ��ͼƬ��ȵ�һ��
	}
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	putimage(0, 0, &im_bk);	// ��ʾ����	
	for (int i=0;i<MaxBulletNum;i++)
		bullet[i].draw();  // ��ʾ�ӵ�
	FlushBatchDraw(); // ��������
	Sleep(10); // ��ͣ
}

void updateWithoutInput() // �������޹صĸ���
{
	for (int i=0;i<MaxBulletNum;i++) // �������ӵ�
		bullet[i].update(); // �����ӵ���λ�á��ٶ�
}

int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // �ظ�����
	{
		show();  // ����
		updateWithoutInput();  // �������޹صĸ���
	}
	return 0;
}