#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(800,600); // ��һ������
	setbkcolor(WHITE); // ���ñ�����ɫΪ��ɫ
	cleardevice();  // �Ա�����ɫ��ջ���
	while (1)
	{
		MOUSEMSG m;		 //���������Ϣ
		if (MouseHit())   // ����������Ϣ
		{
			m = GetMouseMsg();  	 // ��������Ϣ
			if (m.uMsg == WM_MOUSEMOVE) // �������ƶ�ʱ
			{
				// �����λ�ô���һ����ɫԲȦ
				setfillcolor(GREEN);
				setlinecolor(GREEN);
				fillcircle(m.x,m.y,3);
			}
		}
	}
	return 0;
}