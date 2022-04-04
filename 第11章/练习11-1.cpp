#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
#define  PI 3.1415926
#define  WIDTH 800   // ������
#define  HEIGHT 600  // ����߶ȶ�

float offsetAngle = PI/6; // ����֦�ɺ͸�֦��ƫ��ĽǶ�
float shortenRate = 0.65;  // ����֦�ɱȸ�֦�ɱ�̵ı���

// ��[inputMin,inputMax]��Χ��input������ӳ��Ϊ[outputMin,outputMax]��Χ��output����
float mapValue(float input,float inputMin,float inputMax,float outputMin,float outputMax)
{
	float output;
	if (abs(input-inputMin)<0.000001) // ��ֹ�������bug
		output = outputMin;
	else
		output = (input-inputMin)*(outputMax-outputMin)/(inputMax-inputMin) + outputMin;
	return output;
}

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
	line(x_start,y_start,x_end,y_end); // ������ǰ֦�ɣ����ߣ�

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

void startup()  // ��ʼ��
{
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ��ɫ����
	cleardevice(); // ����
	BeginBatchDraw(); // ��ʼ��������
	brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1);//�ݹ����
	FlushBatchDraw(); // ��������
}

void update()  // ÿ֡����
{
	MOUSEMSG m;		
	if (MouseHit())  
	{
		m = GetMouseMsg();  
		if(m.uMsg == WM_MOUSEMOVE) // ������ƶ�ʱ���趨�ݹ麯���Ĳ���
		{
			// �������ң�������֦��ƫ�븸֦�ɵĽǶ��𽥱��
			offsetAngle = mapValue(m.x,0,WIDTH,PI/50,PI/2); 
			// �����ϵ��£���֦�ɱȸ�֦�ɵĳ������̵ĸ���
			shortenRate = mapValue(m.y,0,HEIGHT,0.7,0.3); 
			cleardevice(); // ����
			// �ݹ����
			brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1); 
			FlushBatchDraw(); // ��������
			Sleep(1); // ��ͣ
		}
	}
}

int main() // ������
{
	startup();  // ��ʼ�� 	
	while (1)  // �ظ�ѭ��
		update();  // ÿ֡����
	return 0;
}
