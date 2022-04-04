#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define  PI 3.1415926
#define  WIDTH 800   // ������
#define  HEIGHT 600  // ����߶ȶ�

float offsetAngle = PI/6; // ����֦�ɺ͸�֦��ƫ��ĽǶ�
float shortenRate = 0.65;  // ��֦�ɱȸ�֦�ɱ�̵ı���

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

// ����[min,max]֮������С��
float randBetween(float min,float max)
{
	float t = rand()/double(RAND_MAX); // ����[0,1]�����С��
	// ����mapValue��������ֵ��Χ��[0,1]ӳ�䵽[min,max]
	float r = mapValue(t,0,1,min,max);
	return r;
}

// ֦�����ɺͻ��Ƶݹ麯��
// ���������֦����ʼx y���֦꣬�ɳ��ȣ�֦�ɽǶȣ�֦�ɻ�ͼ������ȣ��ڼ���
void brunch(float x_start,float y_start,float length,float angle,float thickness,int generation)
{
	// �������Ǻ��������ǰ֦�ɵ��յ�x,y����
	float x_end,y_end; 
	x_end = x_start+ length* cos(angle);
	y_end = y_start+ length* sin(angle);

	// ������֦��
	setlinestyle(PS_SOLID,thickness); // �趨��ǰ֦���߿�
	// ����֦��Ϊ�Һ�ɫ����������ڣ���֦���𽥱���
	COLORREF  color = HSVtoRGB(15,0.75,0.4+generation*0.05);		
	setlinecolor(color); // �趨��ǰ֦����ɫ

	line(x_start,y_start,x_end,y_end); // ������ǰ֦�ɣ����ߣ�

	// �����֦�ɵĴ���
	int childGeneration = generation + 1;	
	// �������ҡ��м�������֦�ɵĳ��ȣ��𽥱�̣�����һ�������
	float childLength = shortenRate*length;
	float leftChildLength = childLength*randBetween(0.9,1.1);
	float rightChildLength = childLength*randBetween(0.9,1.1);
	float centerChildLength = childLength*randBetween(0.8,1.1);

	// ����֦�ɳ��ȴ���2�����Ҵ���С�ڵ���10���ݹ���ò�����֦��
	if (childLength>=2 && childGeneration<=9) 
	{		
		// ������֦�ɵĴ�ϸ���𽥱�ϸ
		float childThickness = thickness*0.8;
		if (childThickness<2) // ֦�ɻ�ͼ��ϸ���߿�Ϊ2
			childThickness = 2;

		// һ�����ʲ������ҡ�����֦��
		if(randBetween(0,1)<0.95)
			brunch(x_end,y_end,leftChildLength,angle+offsetAngle*randBetween(0.5,1),childThickness,childGeneration);
		if(randBetween(0,1)<0.95)
			brunch(x_end,y_end,rightChildLength,angle-offsetAngle*randBetween(0.5,1),childThickness,childGeneration);
		if(randBetween(0,1)<0.85)
			brunch(x_end,y_end,centerChildLength,angle+offsetAngle/5*randBetween(-1,1),childThickness,childGeneration);
	}
	else // ��ĩ�˻���ӣ������һ����ɫ���Բ
	{
		setlinestyle(PS_SOLID,1); // �߿�
		// ӣ����ɫHSVtoRGB(325,0.3,1)����һ�������
		COLORREF  color = HSVtoRGB(randBetween(300,350),randBetween(0.2,0.3),1);
		setlinecolor(color); // �趨������ɫ
		setfillcolor(color); // �趨�����ɫ
		if (childLength<=4) // �����֦�ɳ���С�ڵ���4
			fillcircle(x_end,y_end,2); // Բ�İ뾶Ϊ2����С�Ϳ������ˣ�
		else
			fillcircle(x_end,y_end,childLength/2); // ��һ��Բ���뾶Ϊ��֦�ɳ��ȵ�һ��
	}
}

void startup()  // ��ʼ��
{
	srand(time(0)); // �����ʼ��
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ��ɫ����
	cleardevice(); // ����
	BeginBatchDraw(); // ��ʼ��������
	brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1); // �ݹ麯������
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
			offsetAngle = mapValue(m.x,0,WIDTH,PI/10,PI/4); 
			// �����ϵ��£���֦�ɱȸ�֦�ɵĳ������̵ĸ���
			shortenRate = mapValue(m.y,0,HEIGHT,0.7,0.3); 
		}
		if (m.uMsg == WM_LBUTTONDOWN) // �����������ʱ���Ե�ǰ������ʼ����һ������
		{
			cleardevice(); // ����
			brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1); // �ݹ����
			FlushBatchDraw(); // ��������
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