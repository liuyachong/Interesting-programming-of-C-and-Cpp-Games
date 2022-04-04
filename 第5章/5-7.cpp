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
	int lineNum = 0;  // ����ת����ĸ���
	float Angles[1000]; // ���������飬�洢���������ת�Ƕȣ����1000����
	int score = 0; // �÷�
	int i;

	BeginBatchDraw(); // ��ʼ��������
	while (1) // �ظ�ѭ��
	{
		cleardevice(); // �Ա���ɫ��ձ���
		setlinecolor(RGB(0,0,0)); // ��������ɫΪ��ɫ
		line(0,height/2,lineLength,height/2); // ��߷��������һ����

		for (i=0;i<lineNum;i++) // ��������ת����б���
		{
			Angles[i] = Angles[i] + rotateSpeed; // �Ƕ�����
			if (Angles[i]>2*Pi) // �������2*Pi���ͼ�ȥ2*Pi����ֹ�Ƕ�������������
				Angles[i] = Angles[i] - 2*Pi; //
			xEnd = lineLength*cos(-Angles[i]) +width/2; // �������ĩ������
			yEnd = lineLength*sin(-Angles[i]) +height/2;
			setlinecolor(RGB(0,0,255)); // �趨��ת�����ɫΪ��ɫ
			if (i==lineNum-1) // ���·����һ���룬�趨��ɫΪ��ɫ
				setlinecolor(RGB(255,0,0)); 
			line(width/2,height/2,xEnd,yEnd); // ����һ����
		}

		if (kbhit() && rotateSpeed!=0) // ���������������ת�ٶȲ�����0
		{
			char input = _getch(); // ����û���������
			if (input==' ') // ���Ϊ�ո��
			{
				lineNum++; // ��ĸ�����1
				Angles[lineNum-1] = Pi; // �����������ĳ�ʼ�Ƕ�
				xEnd = lineLength*cos(-Angles[lineNum-1]) +width/2; //�������ĩ������
				yEnd = lineLength*sin(-Angles[lineNum-1]) +height/2;	 		
				line(width/2,height/2,xEnd,yEnd); // ���Ƴ���������ӵ���
				for (i=0;i<lineNum-1;i++) // �������ӵ����֮ǰ������Ƚ�
				{
					// ���������֮��ǶȽӽ�����Ϊ��ײ����Ϸʧ��
					if (abs(Angles[lineNum-1]-Angles[i]) < Pi/60) 
					{
						rotateSpeed = 0; // ��ת�ٶ���Ϊ0
						break; // �����ٱȽ��ˣ�ѭ������
					}
				}
				score = score + 1; // �÷�+1
			}
		}
		setfillcolor(HSVtoRGB(0,lineNum/60.0,0.8)); // �����м��Բ�̣���Խ�࣬����ɫԽ����
		setlinecolor(HSVtoRGB(0,0.9,0.8)); // ����Բ��������ɫΪ��ɫ
		fillcircle(width/2,height/2,60); // �����м��Բ��
		TCHAR s[20]; // �����ַ�������
		_stprintf(s, _T("%d"),  score); // ��scoreת��Ϊ�ַ���
		settextstyle(50, 0, _T("Times")); // �������ִ�С������
		settextcolor(RGB(50,50,50));  // ����������ɫ
		outtextxy(65, 200, s); // ����÷�����

		FlushBatchDraw(); // ��������
		Sleep(10); // ��ͣ10����
	}
	closegraph();  // �رջ���
	return 0;
}