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

	int xArray[1000]; // ����洢����Բ�ĵ�x����
	int yArray[1000]; // ����洢����Բ�ĵ�y���� 
	int rArray[1000]; // ����洢����Բ�İ뾶 
	int rmin = 8; // Բ����С�뾶
	int rmax = 50; // Բ�����뾶
	int circleNum = 0; // ���ɵ�Բ�ĸ���
	float x,y,r; // ����Բ��Բ�����ꡢ�뾶
	int isNewCircleOK; // �����ж������ɵ�Բ�Ƿ������
	int i;

	while (circleNum<1000) // ��Բ�ĸ���С��100ʱ��ѭ������
	{
		isNewCircleOK = 0; // ���迪ʼ��OK

		while (isNewCircleOK==0) // �������ɵ�Բ��Okʱ���ظ�������Բ���бȽ�
		{
			x = rand() % width; // ��Բ��Բ��x����
			y = rand() % height; // ��Բ��Բ��y����
			r = rand() % (rmax-rmin+1) + rmin; // ��Բ�İ뾶

			for (i=0;i<circleNum;i++)   // ������Բ����
			{
				float dist2 = (xArray[i] - x)*(xArray[i] - x) + (yArray[i] - y)*(yArray[i] - y);
				float r2 = (rArray[i]+r) * (rArray[i]+r);
				if (dist2<r2) // �������Բ����Բ�ཻ
				{
					break;  // ����ѭ������ʱi<circleNum
				}
			}
			if (i==circleNum) // �������for��䶼��������˵��i����circleNum
			{
				isNewCircleOK = 1; //  ��������ɵ�Բ������Բ�����뽻
			}
		}
		xArray[circleNum] = x; // ����Բ��Բ��������ӵ�������
		yArray[circleNum] = y; //
		rArray[circleNum] = r; // ����Բ�İ뾶��ӵ�������
		circleNum++; // Բ�ĸ���+1

		setlinecolor(RGB(0,0,0)); // ����������ɫ
		setfillcolor(RGB(255,255,0)); // ���������ɫ��ɫ
		fillcircle(x,y,r); // /������Բ

		Sleep(10); // ��ͣ���ɺ���
	}

	_getch();	// �ȴ���������
	closegraph();  // �رմ���
	return 0;
}