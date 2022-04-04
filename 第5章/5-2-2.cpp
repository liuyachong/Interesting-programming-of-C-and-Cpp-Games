#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
int main()
{
	const float Pi = 3.1415926; // Pi����
	int width = 800; // ������
	int height = 600; // ����߶�
	initgraph(width,height); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ����Ϊ��ɫ	

	float lineLength = 160; // ��ĳ���
	float xEnd,yEnd; // ����յ�λ�����꣨����ʼλ��ΪԲ�ģ�
	float angle = 0; // �����ת�Ƕ�
	float rotateSpeed = Pi/360; // �����ת�ٶ�
	setlinestyle(PS_SOLID,3); // �߿�Ϊ3�������뿴����������
	while (1)
	{
		cleardevice(); // �Ա���ɫ��ձ���
		angle = angle + rotateSpeed; // �Ƕ�����
		if (angle>2*Pi) // �������2*Pi���ͼ�ȥ2*Pi����ֹ�Ƕ�������������
			angle = angle - 2*Pi;
		xEnd = lineLength*cos(-angle) +width/2; // �������ĩ������
		yEnd = lineLength*sin(-angle) +height/2;
		setlinecolor(RGB(0,0,0)); // ��������ɫΪ��ɫ
		line(width/2,height/2,xEnd,yEnd); // ����һ����
	
		setlinecolor(HSVtoRGB(0,0.9,0.8)); // ����Բ��������ɫΪ��ɫ
		circle(width/2,height/2,60); // �����м��Բ��
		Sleep(10); // ��ͣ10����
	}
	closegraph(); 
	return 0;
}