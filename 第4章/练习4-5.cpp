#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(750,500); // �¿�����
	setbkcolor(RGB(255,255,255)); // ������ɫ
	cleardevice();
	int x,xStart,xEnd; // x��ʼ����ֹ����
	int c,cStart,cEnd; //  ��ʼ��ɫ����ֹ��ɫ
	xStart = 50; // x��ʼ����Ϊ50

	while (xStart<600) // ��x��ʼ����С��600ʱ
	{
		xEnd = xStart+50; // ��һ�ε�x��ֹ����+50��Ҳ���ǻ�һ��50���صĿ�
		cStart = 255; // ��ʼΪȫ��ɫ
		cEnd = 128; //  ���Ϊ����ɫ
		for (x=xStart;x<xEnd;x++) // ������ɫ��������ô���������������ɫ�������� 
		{
			c = (x-xStart)*(cEnd-cStart)/(xEnd-xStart)+cStart; // 
			setlinecolor(RGB(c,0,c)); // �趨��ɫ 
			line(x, 50, x, 100); // ��һ����
			line(x, 250, x, 300); // ��������
		}

		xStart = xEnd;  
		xEnd = xStart+100; 
		cStart = 0; 
		cEnd = 255;  
		for (x=xStart;x<xEnd;x++) // ���ƶ����������ɫ����ɫ��������
		{
			c = (x-xStart)*(cEnd-cStart)/(xEnd-xStart)+cStart; // 
			setlinecolor(RGB(c,c,0)); // �趨��ɫ
			line(x, 50, x, 100); // ��һ���� 
			line(x, 250, x, 300); //  ��������
		}		
		xStart = xEnd + 20; // ������һ���ɫ����
	} // ѭ����������������һ��

	xStart = 50; // ���淴����ƣ��ڶ����С����Ĵ��е�ͼ��
	while (xStart<600) // 
	{
		xEnd = xStart+100; 
		cStart = 255;  
		cEnd = 0;
		for (x=xStart;x<xEnd;x++)  
		{
			c = (x-xStart)*(cEnd-cStart)/(xEnd-xStart)+cStart;  
			setlinecolor(RGB(c,c,0)); 
			line(x, 150, x, 200);  
			line(x, 350, x, 400); 
		}

		xStart = xEnd; 
		xEnd = xStart+50; 
		cStart = 128; 
		cEnd = 255; 
		for (x=xStart;x<xEnd;x++) 
		{
			c = (x-xStart)*(cEnd-cStart)/(xEnd-xStart)+cStart; 
			setlinecolor(RGB(c,0,c)); 
			line(x, 150, x, 200); 
			line(x, 350, x, 400);  
		}
		xStart = xEnd + 20; 
	}	

	_getch(); 
	closegraph(); 
	return 0;
}