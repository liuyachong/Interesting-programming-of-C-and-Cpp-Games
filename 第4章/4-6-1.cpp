#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // Բ����Pi
	initgraph(600,600); // ��һ��600*600�Ĵ���
	setbkcolor(RGB(255,255,255)); // ���ñ�����ɫΪ��ɫ
	cleardevice();  // �Ա�����ɫ��ջ���

	int centerX = 300; // Բ������
	int centerY = 300;
	int radius = 200; // Բ�뾶
	int left = centerX - radius; // Բ���о������Ͻ�x����
	int top = centerY - radius; // Բ���о������Ͻ�y����
	int right = centerX + radius; // Բ���о������½�x����
	int bottom = centerY + radius; // Բ���о������½�y����	

	int i;
	int step = 10;
	COLORREF  color; // ������ɫ����
	for (i=0;i<360;i=i+step) // ������תһ�ܣ�������������
	{
		color = HSVtoRGB(i,1,1); // HSV���õ���ɫ
		setfillcolor(color);// ���������ɫΪcolor
		solidpie(left,top,right,bottom,i*Pi/180,(i+step)*Pi/180); // ���������
	}
	_getch();  // ��ͣ���ȴ���������
	return 0;
}