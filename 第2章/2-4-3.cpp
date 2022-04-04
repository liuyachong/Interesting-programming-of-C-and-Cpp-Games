#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int x,y,z;
	x = 5;
	printf("%d\n",x);
	y = x;
	printf("%d\n",y);
	x = x - 2;
	printf("%d\n",x);
	z = 2*x - y + 1;
	printf("%d\n",z);
	_getch();
	return 0;
}