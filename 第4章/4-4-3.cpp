#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600,600); // ��һ��600*600�Ĵ���
	setbkcolor(RGB(255,255,255)); // ���ñ�����ɫΪ��ɫ
	cleardevice();  // �Ա�����ɫ��ջ���
	int radius; // Բ�뾶
	for (radius=255;radius>0;radius=radius-10) // ����һЩͬ��Բ
	{
		setlinecolor(RGB(radius,0,0));// ����������ɫ
		circle(300,300,radius); // ��radiusΪ�뾶��Բ
	}
	_getch();  // ��ͣ���ȴ���������
	return 0;
}