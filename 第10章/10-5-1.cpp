#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
int main()
{
	initgraph(600,400); // �¿�һ������
	setbkcolor(RGB(255,255,255)); // ������ɫΪ��ɫ
	setbkmode(TRANSPARENT); // ͸����ʾ����
	settextcolor(BLACK);  // ����������ɫ
	settextstyle(60, 0, _T("����")); // �������ִ�С������	
	TCHAR str[20]; // �����ַ�����
	clock_t start, now; // ���ڼ�ʱ�ı���
	start = clock(); // ��¼��ǰ����ʱ��

	while (1)// ѭ��
	{
		now = clock(); // ��õ�ǰʱ��
		// �������һ�������˶�����
		double duration =( double(now - start) / CLOCKS_PER_SEC); 
		_stprintf(str, _T("����������%d��"),  int(duration)); //ת��Ϊ�ַ���
		cleardevice(); // ����
		outtextxy(100, 150, str); // �������
		Sleep(20); // ��ͣ20����
	}	
	return 0;
}