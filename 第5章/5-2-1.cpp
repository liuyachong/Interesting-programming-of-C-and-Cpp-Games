#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
int main()
{
	float Pi = 3.1415926;
	int width = 800; // ������
	int height = 600; // ����߶�
	initgraph(width,height); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ����Ϊ��ɫ
	cleardevice(); // �Ա���ɫ��ձ���

	float lineLength = 160; // ��ĳ���
	float xEnd,yEnd; // ����յ�λ�����꣨����ʼλ��ΪԲ�ģ�
	float angle = Pi/3; // �����ת�Ƕ�

	setlinestyle(PS_SOLID,3); // �߿�Ϊ3�������뿴����������
	setlinecolor(RGB(0,0,0)); // ��������ɫΪ��ɫ
	xEnd = lineLength*cos(-angle) +width/2; // �������ĩ������
	yEnd = lineLength*sin(-angle) +height/2;
	line(width/2,height/2,xEnd,yEnd); // ����һ����
	
	setlinecolor(HSVtoRGB(0,0.9,0.8)); // ����Բ��������ɫΪ��ɫ
	circle(width/2,height/2,60); // �����м��Բ��

	_getch();	
	closegraph(); 
	return 0;
}