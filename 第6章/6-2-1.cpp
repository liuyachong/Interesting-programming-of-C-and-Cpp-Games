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
	int circleNum = 0; // ���ɵ�Բ�ĸ���
	float x,y,r; // ����Բ��Բ�����ꡢ�뾶

	while (circleNum<100) // ��Բ�ĸ���С��100ʱ��ѭ������
	{
		x = rand() % width; // ��Բ��Բ��x����
		y = rand() % height; // ��Բ��Բ��y����
		r = rand() % (rmax-rmin+1) + rmin; // ��Բ�İ뾶

		xArray[circleNum] = x; // ����Բ��Բ��������ӵ�������
		yArray[circleNum] = y; //
		rArray[circleNum] = r; // ����Բ�İ뾶��ӵ�������
		circleNum++; // Բ�ĸ���+1

		setlinecolor(RGB(0,0,0)); // ����������ɫ
		setfillcolor(RGB(255,255,0)); // ���������ɫ��ɫ
		fillcircle(x,y,r); // /������Բ

		Sleep(100); // ��ͣ100����
	}

	_getch();	// �ȴ���������
	closegraph();  // �رմ���
	return 0;
}