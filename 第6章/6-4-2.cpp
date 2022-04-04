#include <conio.h>
#include <stdio.h>

void printStars(int num)
{
	int i;
	for (i=1;i<=num;i++)
	{
		printf("*");
	}
	printf("\n");
}

int main()
{
	int j;
	for (j=1;j<=5;j++)
		printStars(j);
	_getch();
	return 0;
}