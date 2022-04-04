#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float width,height,gravity; // ��Ϸ�����С���������ٶ�
	float ball_x,ball_y,ball_vy,radius; // С��Բ�����ꡢy�����ٶȡ��뾶��С
	float rect_left_x,rect_top_y,rect_width,rect_height,rect_vx; // �����ϰ������ز���
	int score = 0; // �÷�

	width = 600;  // ��Ϸ������
	height = 400; // ��Ϸ����߶�
	gravity = 0.6;  // �������ٶ�
	initgraph(width, height); // �½�һ������

	radius = 20; // С��뾶	
	ball_x = width/4; // С��xλ��
	ball_y = height-radius;  // С��yλ��
	ball_vy = 0;  // С���ʼy�ٶ�Ϊ0

	rect_height = 100; // ����߶�
	rect_width = 20; // ������
	rect_left_x = width*3/4; // �������x����
	rect_top_y = height - rect_height; // ���鶥��y����
	rect_vx = -3; // ����x�����ٶ�

	while(1) // һֱѭ��
	{		
		if (kbhit()) // ������ʱ
		{
			char input = _getch(); // ��������ַ�
			if (input==' ') // �����¿ո��ʱ
			{
				ball_vy = -17; // ��С��һ�����ϵ��ٶ�
			}
		}

		ball_vy = ball_vy + gravity;  // �����������ٶȸ���С��y�����ٶ�
		ball_y = ball_y + ball_vy;    // ����С��y�����ٶȸ�����y����
		if (ball_y >= height-radius)  // ���С���䵽������
		{
			ball_vy = 0;  // y�ٶ�Ϊ0
			ball_y = height-radius;  // �淶��y���꣬�����䵽������
		}

		rect_left_x = rect_left_x + rect_vx; // ����������
		if (rect_left_x <= 0) // ��������ܵ������
		{
			rect_left_x = width; // �����ұ����³���
			score = score + 1; // �÷�+1
			rect_height = rand() % int(height/4) + height/4; // ��������߶�
			rect_vx = rand()/float(RAND_MAX) *4 - 7; // ���÷�������ٶ�
		}
		// ���С����������
		if ((rect_left_x <= ball_x + radius) 
			&& (rect_left_x + rect_width >= ball_x - radius) 
			&& (height - rect_height <= ball_y + radius) )
		{
			Sleep(100); // ������Ч��
			score = 0; // �÷�����
		}

		cleardevice();  // ��ջ���
		fillcircle(ball_x, ball_y, radius);  // ����С��
		// ������
		fillrectangle(rect_left_x, height - rect_height, rect_left_x + rect_width,height);
		TCHAR s[20]; // �����ַ�������
		_stprintf(s, _T("%d"),  score); // ��scoreת��Ϊ�ַ���
		settextstyle(40, 0, _T("����")); // �������ִ�С������
		outtextxy(50, 30, s); // ����÷�����
		Sleep(10);  // ��ͣ10����
	}
	closegraph(); 
	return 0;
}