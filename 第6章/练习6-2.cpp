#include <conio.h>
#include <stdio.h>

void printStars()
{
	int i;
	for (i=1;i<=5;i++)
	{
		printf("*");
	}
	printf("\n");
}

int main()
{
	int j;
	for (j=1;j<=4;j++)
		printStars();
	_getch();
	return 0;
}