#include <graphics.h>  
#include <conio.h>
#include "EasyXPng.h"  // ������ʾ��͸��ͨ����pngͼƬ
#define  WIDTH 560 // ������
#define  HEIGHT 800 // ����߶�

struct Bullet  // �ӵ��ṹ��
{
	IMAGE im_bullet; // �ӵ�ͼ��
	float x,y; // �ӵ�����
	float vx,vy; // �ӵ��ٶ�
	float radius; // �ӽ�������ӵ��뾶��С
};

IMAGE im_bk,im_bullet;  // ����ͼ�����	
Bullet bullet; // �����ӵ��ṹ�����

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
	putimagePng(bullet.x - bullet.radius,bullet.y-bullet.radius,&bullet.im_bullet); // ��ʾ�ӵ�
	FlushBatchDraw(); // ��������
	Sleep(10); // ��ͣ
}

void updateWithoutInput() // �������޹صĸ���
{
	// �����ӵ���λ�á��ٶ�
	bullet.x += bullet.vx;
	bullet.y += bullet.vy;
	if (bullet.x<=0 || bullet.x>=WIDTH)
		bullet.vx = -bullet.vx;
	if (bullet.y<=0 || bullet.y>=HEIGHT)
		bullet.vy = -bullet.vy;
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