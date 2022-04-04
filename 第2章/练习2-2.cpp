#include <graphics.h>
#include <conio.h>
#include <stdio.h>

int main()
{
	initgraph(900, 600);

	fillcircle(270, 300, 50);
	fillcircle(270, 150, 90);
	fillcircle(270, 450, 90);
	fillcircle(120, 300, 90);
	fillcircle(420, 300, 90);

	fillcircle(770, 300, 50);
	fillcircle(770, 220, 20);
	fillcircle(770, 380, 20);
	fillcircle(690, 300, 20);
	fillcircle(850, 300, 20);

	_getch();
	closegraph();
	return 0;
}
