#include <graphics.h>  
#include "conio.h"
#include "EasyXPng.h"  // ������ʾ��͸��ͨ����pngͼƬ
#define  WIDTH 560 // ������
#define  HEIGHT 800 // ����߶�

int main()
{
	IMAGE im_bk,im_rocket;  // ����ͼ�����	
	loadimage(&im_bk, _T("background.png")); // ���뱳��ͼƬ
	loadimage(&im_rocket, _T("rocket.png")); // ������ͼƬ

	initgraph(WIDTH,HEIGHT); // �¿�һ������
	putimage(0, 0, &im_bk);	// ��ʾ����
	putimagePng(WIDTH/2, HEIGHT/2, &im_rocket); // ��ʾ���
	_getch();
	return 0;
}