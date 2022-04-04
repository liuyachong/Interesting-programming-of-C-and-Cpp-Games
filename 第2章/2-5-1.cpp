#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int y = 100;
	int step = 100;
	initgraph(600, 600);
	fillcircle(300, y, 20);
	Sleep(1000);
	y = y+step;
	fillcircle(300, y, 20);
	Sleep(1000);
	y = y+step;
	fillcircle(300, y, 20);
	Sleep(1000);
	y = y+step;
	fillcircle(300, y, 20);
	Sleep(1000);
	y = y+step;
	fillcircle(300, y, 20);
	Sleep(1000);
	_getch();
	closegraph();
	return 0;
}