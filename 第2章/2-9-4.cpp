#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float y = 100; // С���y����
	float vy = 0; // С��y�����ٶ�
	float g = 0.5; // С����ٶȣ�y����
	initgraph(600, 600); // ��ʼ��Ϸ���ڻ��棬��600����600
	while(1) // һֱѭ������
	{		
		cleardevice(); // �����֮ǰ���Ƶ�����
		vy = vy+g; // ���ü��ٶ�g����vy�ٶ�
		y = y+vy; // ����y�����ٶ�vy����y����
		if (y>=580) // ����������ʱ
			vy = -0.95*vy; // y�����ٶȸı䷽�򣬲�������Ӱ�����ֵ��С
		if (y>580) // ��ֹС��Խ������
			y = 580;
		fillcircle(300, y, 20); // ������(300,y)����һ���뾶Ϊ20��Բ
		Sleep(10); // ��ͣ10����
	}
	_getch(); // �ȴ�����
	closegraph(); // �رմ���
	return 0;
}
