#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	while(1)  // 一直循环
	{		
		if (kbhit())// 当按键时
		{
			char input = _getch(); // 获得输入字符
			if (input==' ') // 当按下空格键
				printf("按下了空格！\n");			
		}
	}
	return 0;
}