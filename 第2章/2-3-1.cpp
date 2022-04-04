#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600, 800);
	fillcircle(300, 100, 50);
	fillcircle(300, 250, 50);
	fillcircle(300, 400, 50);
	_getch();
	closegraph();
	return 0;
}
