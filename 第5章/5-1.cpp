#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	int width = 800; // ������
	int height = 600; // ����߶�
	initgraph(width,height); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ����Ϊ��ɫ
	cleardevice(); // �Ա���ɫ��ձ���

	setlinestyle(PS_SOLID,3); // �߿�Ϊ3�������뿴����������
	setlinecolor(RGB(0,0,0)); // ��������ɫΪ��ɫ
	line(width/2,height/2,width/2+160,height/2); // ����һ����
	
	setlinecolor(HSVtoRGB(0,0.9,0.8)); // ����Բ��������ɫΪ��ɫ
	circle(width/2,height/2,60); // �����м��Բ��

	_getch();	
	closegraph(); 
	return 0;
}