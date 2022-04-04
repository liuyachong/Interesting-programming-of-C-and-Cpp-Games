#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
#define  PI 3.1415926
#define  WIDTH 800   // ������
#define  HEIGHT 600  // ����߶ȶ�

float offsetAngle = PI/6; // ����֦�ɺ͸�֦��ƫ��ĽǶ�
float shortenRate = 0.65;  // ����֦�ɱȸ�֦�ɱ�̵ı���

// ֦�����ɺͻ��Ƶݹ麯��
// ���������֦����ʼx y���֦꣬�ɳ��ȣ�֦�ɽǶȣ�֦�ɻ�ͼ������ȣ��ڼ���
void brunch(float x_start,float y_start,float length,float angle,float thickness,int generation)
{
	// �������Ǻ��������ǰ֦�ɵ��յ�x,y����
	float x_end,y_end; 
	x_end = x_start+ length* cos(angle);
	y_end = y_start+ length* sin(angle);

	setlinestyle(PS_SOLID,thickness); // �趨��ǰ֦���߿�
	setlinecolor(RGB(0,0,0)); // �趨��ǰ֦����ɫ ��ɫ
	line(x_start,y_start,x_end,y_end); //������ǰ֦�ɣ����ߣ�

	// �����֦�ɵĴ���
	int childGeneration = generation + 1;	
	// ������֦�ɵĳ��ȣ��𽥱��
	float childLength = shortenRate*length;
	
	// ����֦�ɳ��ȴ���2�����Ҵ���С�ڵ���10���ݹ���ò�����֦��
	if (childLength>=2 && childGeneration<=9) 
	{		
		// ������֦�ɵĴ�ϸ���𽥱�ϸ
		float childThickness = thickness*0.8;
		if (childThickness<2) // ֦�ɻ�ͼ��ϸ���߿�Ϊ2
			childThickness = 2;
		
		// �������ҵ���֦��
		brunch(x_end,y_end,childLength,angle+offsetAngle,childThickness,childGeneration);
		brunch(x_end,y_end,childLength,angle-offsetAngle,childThickness,childGeneration);
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
	brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1); //�ݹ����
	FlushBatchDraw(); // ��������
	_getch();
	return 0;
}
