#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int r = 10;
	initgraph(600, 600);
	while(1)
	{		
		fillcircle(300, 300, r);
		r = r+1;
		Sleep(20);
		cleardevice();
	}
	_getch();
	closegraph();
	return 0;
}
