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

	int i;
	float offset; 
	for (i=0;i<20;i++) // ������תһ�ܣ�������������
	{
		offset = i*Pi/10; // ��������֮��ƫ�ƵĽǶ�
		setfillcolor(RGB(0,240,220));// ���������ɫΪ��ɫ
		solidpie(left,top,right,bottom,offset,2*Pi/60+offset); // ���������
		setfillcolor(RGB(255,255,255));// ���������ɫΪ��ɫ
		solidpie(left,top,right,bottom,2*Pi/60+offset,3*Pi/60+offset); // ���������
		setfillcolor(RGB(200,0,0));// ���������ɫΪ��ɫ
		solidpie(left,top,right,bottom,3*Pi/60+offset,5*Pi/60+offset); // ���������
		setfillcolor(RGB(0,0,0));// ���������ɫΪ��ɫ
		solidpie(left,top,right,bottom,5*Pi/60+offset,6*Pi/60+offset); // ���������
	}
	_getch();  // ��ͣ���ȴ���������
	return 0;
}