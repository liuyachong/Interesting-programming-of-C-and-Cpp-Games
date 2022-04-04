#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float width,height,gravity; // ��Ϸ�����С���������ٶ�
	float ball_x,ball_y,ball_vy,radius; // С��Բ�����ꡢy�����ٶȡ��뾶��С

	width = 600;  // ��Ϸ������
	height = 400; // ��Ϸ����߶�
	gravity = 0.6;  // �������ٶ�
	initgraph(width, height); // �½�һ������

	radius = 20; // С��뾶	
	ball_x = width/4; // С��xλ��
	ball_y = height-radius;  // С��yλ��
	ball_vy = 0;  // С���ʼy�ٶ�Ϊ0
	
	while(1) // һֱѭ��
	{		
		if (kbhit()) // ������ʱ
		{
			char input = _getch(); // ��������ַ�
			if (input==' ') // �����¿ո��ʱ
			{
				ball_vy = -16; // ��С��һ�����ϵ��ٶ�
			}
		}

		ball_vy = ball_vy + gravity;  // �����������ٶȸ���С��y�����ٶ�
		ball_y = ball_y + ball_vy;    // ����С��y�����ٶȸ�����y����
		if (ball_y >= height-radius)  // ���С���䵽������
		{
			ball_vy = 0;  // y�ٶ�Ϊ0
			ball_y = height-radius;  // �淶��y���꣬�����䵽������
		}

		cleardevice();  // ��ջ���
		fillcircle(ball_x, ball_y, radius);  // ����С��
		Sleep(10);  // ��ͣ10����
	}
	closegraph(); 
	return 0;
}