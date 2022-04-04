#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600, 600);
	fillcircle(300, 1*600/4, 50);
	fillcircle(300, 2*600/4, 50);
	fillcircle(300, 3*600/4, 50);
	_getch();
	closegraph();
	return 0;
}
