#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600,350); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ������ɫΪ��ɫ
	cleardevice(); // �Ա�����ɫ��ձ���	
	setbkmode(TRANSPARENT); // ͸����ʾ����

	settextcolor(RED);  // ����������ɫ
	settextstyle(50, 0, _T("����")); // �������ִ�С������	
	outtextxy(50, 30, _T("���")); // �������

	TCHAR str1[20] = _T("����������ֲ���"); // �����ַ�����
	settextcolor(GREEN);  // ����������ɫ
	settextstyle(40, 0, _T("����")); // �������ִ�С������	
	outtextxy(50, 130, str1); // �������

	TCHAR str2[20];  // �����ַ�����
	int score = 10;  // �÷����ͱ���	
	_stprintf(str2, _T("�÷֣�%d"),  score); // ��scoreת��Ϊ�ַ���
	settextcolor(BLUE);  // ����������ɫ
	settextstyle(60, 0, _T("����")); // �������ִ�С������	
	outtextxy(50, 230, str2); // �������

	_getch();
	return 0;
}