#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	while(1)  // һֱѭ��
	{		
		if (kbhit())// ������ʱ
		{
			char input = _getch(); // ��������ַ�
			if (input==' ') // �����¿ո��
				printf("�����˿ո�\n");			
		}
	}
	return 0;
}