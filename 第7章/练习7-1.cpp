#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int a[4][4];
	int i,j;

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			a[i][j] = rand()%5 + 1;	
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
			printf("%2d",a[i][j]);
		printf("\n");
	}
	printf("\n");
	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			if (a[i][j]==5)
				a[i][j]=0;
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
			printf("%2d",a[i][j]);
		printf("\n");
	}

	_getch();
	return 0;
}