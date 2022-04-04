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
	setlinestyle(PS_SOLID,3); // �߿�Ϊ3�������뿴����������

	float lineLength = 160; // ��ĳ���
	float xEnd,yEnd; // ����յ�λ�����꣨����ʼλ��ΪԲ�ģ�
	float rotateSpeed = Pi/360; // �����ת�ٶ�
	int lineNum = 20;  // ��ĸ���
	float Angles[20]; // ���������飬�洢���������ת�Ƕ�
	int i;
	for (i=0;i<lineNum;i++) // ��ʼ����������ĽǶȾ��ȷֲ�
		Angles[i] = i*2*Pi/lineNum;

	BeginBatchDraw(); // ��ʼ��������
	while (1) // �ظ�ѭ��
	{
		cleardevice(); // �Ա���ɫ��ձ���
		setlinecolor(RGB(0,0,0)); // ��������ɫΪ��ɫ
		for (i=0;i<lineNum;i++) // ��������ת����б���
		{
			Angles[i] = Angles[i] + rotateSpeed; // �Ƕ�����
			if (Angles[i]>2*Pi) // �������2*Pi���ͼ�ȥ2*Pi����ֹ�Ƕ�������������
				Angles[i] = Angles[i] - 2*Pi; //
			xEnd = lineLength*cos(-Angles[i]) +width/2; // �������ĩ������
			yEnd = lineLength*sin(-Angles[i]) +height/2;
			line(width/2,height/2,xEnd,yEnd); // ����һ����
		}
		setlinecolor(HSVtoRGB(0,0.9,0.8)); // ����Բ��������ɫΪ��ɫ
		circle(width/2,height/2,60); // �����м��Բ��
		FlushBatchDraw(); // ��������
		Sleep(10); // ��ͣ10����
	}
	closegraph();  // �رջ���
	return 0;
}