#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#define Width 600
#define Height 600

struct Ball // ����С��ṹ��
{
	float x; // С���x����
	float y; // С���y����
	float vx; // С��x�����ٶ�
	float vy; // С��y�����ٶ�
	float r; // С��뾶
};

int main()
{
	Ball ball;  // ����С��ṹ�����
	ball.x = 100; // С���x����
	ball.y = 200; // С���y����
	ball.vx = 8; // С��x�����ٶ�
	ball.vy = 0; // С��y�����ٶ�
	ball.r = 20; // С��뾶
	float g = 0.5; // �������ٶȣ�y����
	initgraph(Width, Height); // ��ʼ��Ϸ���ڻ���
	while(1) // һֱѭ������
	{		
		cleardevice(); // �����֮ǰ���Ƶ�����
		ball.vy = ball.vy + g; // ���ü��ٶ�g����vy�ٶ�
		ball.x = ball.x + ball.vx; // ����x�����ٶ�vx����x����
		ball.y = ball.y + ball.vy; // ����y�����ٶ�vy����y����
		if (ball.y>=Height-ball.r) // ����������ʱ
		{
			ball.vx = 0.98 * ball.vx; // x�����ٶ�������Ӱ���С
			ball.vy = -0.95 * ball.vy; // y�����ٶȸı䷽�򣬲�������Ӱ���С
		}
		if (ball.y>Height-ball.r) // ��ֹС��Խ������
			ball.y = Height-ball.r;
		if (ball.x>=Width-ball.r) // �����ұ�ǽ��С��x�����ٶȷ���
			ball.vx = -ball.vx;
		if (ball.x<=ball.r) // �������ǽ��С��x�����ٶȷ���
			ball.vx = -ball.vx;
		fillcircle(ball.x, ball.y, ball.r); // ������(x,y)����һ���뾶r��Բ
		Sleep(15); // ��ͣ���ɺ���
	}
	_getch(); // �ȴ�����
	closegraph(); // �رմ���
	return 0;
}