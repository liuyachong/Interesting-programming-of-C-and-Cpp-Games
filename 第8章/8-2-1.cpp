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
			if (m.uMsg == WM_LBUTTONDOWN) // �������������
			{
				// �������λ�û�һ����ɫԲȦ
				setfillcolor(RED);
				fillcircle(m.x,m.y,30);
			}
		}
	}
	return 0;
}