#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600, 600);; // ��һ������
	setbkcolor(YELLOW); // ���ñ�����ɫΪ��ɫ
	cleardevice();  // �Ա�����ɫ��ջ���
	setlinecolor(RGB(0,0,0));  // ��������Ϊ��ɫ
	int i;
	int step = 30;
	for(i=1; i<=19; i++)  // �����ߺ�����
	{
		line(i*step, 1*step, i*step,  19*step);
		line(1*step, i*step, 19*step, i*step);
	}
	_getch();  // ��ͣ���ȴ���������
	return 0;
}