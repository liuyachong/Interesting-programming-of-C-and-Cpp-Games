#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int y = 50;
	int vy = 3;
	initgraph(600, 600);
	while (1)
	{
		y = y + vy;
		if (y>=580)
			vy = -vy;
		if (y<=20)
			vy = -vy;
		cleardevice();
		fillcircle(300, y, 20);
		Sleep(10);
	}
	_getch();
	closegraph();
	return 0;
}