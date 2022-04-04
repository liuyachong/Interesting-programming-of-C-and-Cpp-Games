#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int width,height,length,area;
	width = 20;
	height = 10;
	length = 2*(width+height);
	area = width*height;
	printf("%d\n",length);
	printf("%d\n",area);
	_getch();
	return 0;
}
