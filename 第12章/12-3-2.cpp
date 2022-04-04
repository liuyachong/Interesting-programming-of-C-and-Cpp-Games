#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"  // ������ʾ��͸��ͨ����pngͼƬ
#define  WIDTH 560 // ������
#define  HEIGHT 800 // ����߶�

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
Bullet bullet; // �����ӵ�����

void startup()  //  ��ʼ������
{	
	loadimage(&im_bk, _T("background.png")); // ���뱳��ͼƬ
	loadimage(&im_bullet, _T("bullet.png")); // �����ӵ�ͼƬ
	bullet.x = WIDTH/2; // �ӵ���ʼλ��
	bullet.y = HEIGHT/2;
	bullet.vx = 2;  // �ӵ��ٶ�
	bullet.vy = 2;
	bullet.im_bullet = im_bullet;  // �����ӵ�ͼ��
	bullet.radius = im_bullet.getwidth()/2; // �����ӵ��İ뾶Ϊ��ͼƬ��ȵ�һ��

	initgraph(WIDTH,HEIGHT); // �¿�һ������
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	putimage(0, 0, &im_bk);	// ��ʾ����	
	bullet.draw();  // ��ʾ�ӵ�
	FlushBatchDraw(); // ��������
	Sleep(10); // ��ͣ
}

void updateWithoutInput() // �������޹صĸ���
{
	bullet.update(); // �����ӵ���λ�á��ٶ�
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