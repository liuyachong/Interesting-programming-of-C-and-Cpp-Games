#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(600, 600);
	fillcircle(300, 300, 50);
	_getch();
	closegraph();
	return 0;
}
