#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // Բ����Pi
	initgraph(600,600); // ��һ��600*600�Ĵ���
	setbkcolor(RGB(128,128,128)); // ���ñ�����ɫΪ��ɫ
	cleardevice();  // �Ա�����ɫ��ջ���
	
	int centerX = 300; // Բ������
	int centerY = 300;
	int radius = 200; // Բ�뾶
	int left = centerX - radius; // Բ���о������Ͻ�x����
	int top = centerY - radius; // Բ���о������Ͻ�y����
	int right = centerX + radius; // Բ���о������½�x����
	int bottom = centerY + radius; // Բ���о������½�y����	

	setfillcolor(RGB(0,255,0));// ���������ɫΪ��ɫ
	solidpie(left,top,right,bottom,0*Pi/2,1*Pi/2); // ���������
	setfillcolor(RGB(255,255,255));// ���������ɫΪ��ɫ
	solidpie(left,top,right,bottom,1*Pi/2,2*Pi/2); // ���������
	setfillcolor(RGB(255,0,0));// ���������ɫΪ��ɫ
	solidpie(left,top,right,bottom,2*Pi/2,3*Pi/2); // ���������
	setfillcolor(RGB(0,0,0));// ���������ɫΪ��ɫ
	solidpie(left,top,right,bottom,3*Pi/2,4*Pi/2); // ���������

	_getch();  // ��ͣ���ȴ���������
	return 0;
}