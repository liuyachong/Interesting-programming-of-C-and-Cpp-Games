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

	float maxTime = 20; // ��Ϸ�������ʱ��
	float remainTime = maxTime; // ��Ϸʣ��ʱ��

	while (remainTime>=0)// ѭ��
	{
		now = clock(); // ��õ�ǰʱ��
		// �������һ�������˶�����
		double duration =( double(now - start) / CLOCKS_PER_SEC); 
		remainTime = maxTime - duration; // ������Ϸʣ��ʱ��
		_stprintf(str, _T("ʣ��ʱ�䣺%d��"),  int(remainTime)); //ת��Ϊ�ַ���
		cleardevice(); // ����
		outtextxy(100, 150, str); // �������

		setlinecolor(RGB(255,0,0)); // ���ý���������ɫ
		setfillcolor(RGB(255,0,0));
		fillrectangle(0,10,remainTime*600/maxTime,50); // ���ƽ�����

		Sleep(20); // ��ͣ20����
	}	
	return 0;
}
