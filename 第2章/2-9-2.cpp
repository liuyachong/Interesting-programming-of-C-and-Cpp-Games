#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	float y = 100;
	float vy = 0;
	float g = 0.5;
	initgraph(600, 600);
	while (1)
	{
		vy = vy + g;
		y = y + vy;
		if (y>=580)
			vy = -vy;
		cleardevice();
		fillcircle(300, y, 20);
		Sleep(10);
	}
	_getch();
	closegraph();
	return 0;
}
