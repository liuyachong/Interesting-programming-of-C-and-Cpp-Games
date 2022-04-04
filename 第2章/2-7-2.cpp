#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int x = 3;
	int y = 5;
	if (x>y)
		printf("x大");
	if (x<y)
		printf("y大");
	if (x==y)
		printf("x与y一样大");
	_getch();
	return 0;
}