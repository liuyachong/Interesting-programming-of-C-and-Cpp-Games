#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600, 800);
	fillcircle(300, 1*800/4, 50);
	fillcircle(300, 2*800/4, 50);
	fillcircle(300, 3*800/4, 50);
	_getch();
	closegraph();
	return 0;
}
