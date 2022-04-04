#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	initgraph(800,600); 
	int x,y;
	for (y=0;y<=600;y=y+200)
		for (x=0;x<=800;x=x+200)
			fillcircle(x, y, 100);
	_getch();  
	return 0;
}