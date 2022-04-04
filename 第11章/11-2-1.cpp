#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
#define  PI 3.1415926
#define  WIDTH 800   // ������
#define  HEIGHT 600  // ����߶ȶ�

// ֦�����ɺͻ��Ƶݹ麯��
// ���������֦����ʼx,y���֦꣬�ɽǶȣ��ڼ���
void brunch(float x_start,float y_start,float angle,int generation)
{
	// �������Ǻ��������ǰ֦�ɵ��յ�x,y����
	float x_end,y_end; 
	x_end = x_start+ 150* cos(angle);
	y_end = y_start+ 150* sin(angle);

	line(x_start,y_start,x_end,y_end); // ������ǰ֦�ɣ����ߣ�		

	// �����֦�ɵĴ���
	int childGeneration = generation + 1;		
	// ����֦�ɲ��Ҵ���С�ڵ���4��������ǰ֦�ɣ����ݹ���ò�����֦��
	if (childGeneration<=4) 
	{						
		// �������ҵ���֦��
		brunch(x_end,y_end,angle+PI/6,childGeneration);
		brunch(x_end,y_end,angle-PI/6,childGeneration);
	}
}

int main() // ������
{
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ��ɫ����
	setlinecolor(RGB(0,0,0)); // �趨������ɫΪ��ɫ
	setlinestyle(PS_SOLID,3); // �趨�߿�
	cleardevice(); // ����
	BeginBatchDraw(); // ��ʼ��������
	brunch(WIDTH/2,HEIGHT,-PI/2,1); // �ݹ麯������
	FlushBatchDraw(); // ��������
	_getch();
	return 0;
}
