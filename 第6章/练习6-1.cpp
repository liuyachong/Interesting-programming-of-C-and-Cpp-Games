#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(460, 460);
	int bx = 100;
	while (bx<460)
	{
		fillrectangle(0,bx,460,bx+20);
		fillrectangle(bx,0,bx+20,460);
		bx = bx+120;
	}
	_getch(); 
	closegraph(); 
	return 0;
}