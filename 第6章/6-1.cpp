#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
int main()
{
	int width = 600; // ���ڿ��
	int height = 600; // ���ڸ߶�
	initgraph(width,height); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ������ɫΪ��ɫ
	cleardevice(); // �Ա�����ɫ��ձ���
	srand(time(0));  // ������Ӻ���

	int xArray[100]; // ����洢����Բ�ĵ�x����
	int yArray[100]; // ����洢����Բ�ĵ�y���� 
	int rArray[100]; // ����洢����Բ�İ뾶 
	int rmin = 8; // Բ����С�뾶
	int rmax = 50; // Բ�����뾶
	int circleNum = 100; // ���ɵ�Բ�ĸ���

	int i;
	for (i=0;i<circleNum;i++) // ����circleNum��Բ�������ݱ�����������
	{
		xArray[i] = rand() % width; // Բ�ĵ�x����
		yArray[i] = rand() % height;// Բ�ĵ�y����
		rArray[i] = rand() % (rmax-rmin+1) + rmin; // Բ�İ뾶
	}

	for (i=0;i<circleNum;i++) // ���Ƴ����е�Բ
	{
		setlinecolor(RGB(0,0,0)); // ����������ɫ
		setfillcolor(RGB(255,255,0)); // ���������ɫ��ɫ
		fillcircle(xArray[i],yArray[i],rArray[i]); // ������洢�����ݻ���Բ
	}

	_getch();	// �ȴ���������
	closegraph();  // �رմ���
	return 0;
}