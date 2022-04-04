#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
int main()
{
	const float Pi = 3.1415926; // Pi����
	int width = Pi*200; // ������
	int height = 200; // ����߶�
	initgraph(width,height); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ����Ϊ��ɫ	
	cleardevice(); // �Ա���ɫ��ձ���
	setlinecolor(RGB(0,0,0));

	float x;
	float step = Pi/360; 
	for (x=0;x<=2*Pi;x=x+step) 
	{
		float x0 = x*width/(2*Pi);
		float x1 = (x+step)*width/(2*Pi);
		float y0 = height/2 - sin(x)*height/2;
		float y1 = height/2 - sin(x+step)*height/2;
		line(x0,y0,x1,y1); // ����ǰ������������֮�������
	}

	_getch();
	closegraph(); 
	return 0;
}