#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // Բ����Pi
	initgraph(600,600); // ��һ��600*600�Ĵ���
	setbkcolor(WHITE);    // ���ñ�����ɫΪ��ɫ
	setlinecolor(RED);    // ����������ɫΪ��ɫ
	setfillcolor(GREEN);  // ���������ɫΪ��ɫ
	cleardevice();  // �Ա�����ɫ��ջ���
	int centerX = 300; // Բ������
	int centerY = 300;
	int radius = 200; // Բ�뾶
	circle(centerX,centerY,radius); // ������Ӧ��Բ�߿�
	int left = centerX - radius; // Բ���о������Ͻ�x����
	int top = centerY - radius; // Բ���о������Ͻ�y����
	int right = centerX + radius; // Բ���о������½�x����
	int bottom = centerY + radius; // Բ���о������½�y����	
	solidpie(left,top,right,bottom,Pi/6,Pi/3); // ��������Σ��Ƕ�ΪPi/6��Pi/3
	_getch();  // ��ͣ���ȴ���������
	return 0;
}