#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int y = 50;
	initgraph(600, 600);
	while (1)
	{
		y = y + 1;
		if (y>620)
			y = -20;
		cleardevice();
		fillcircle(300, y, 20);
		Sleep(10);
	}
	_getch();
	closegraph();
	return 0;
}