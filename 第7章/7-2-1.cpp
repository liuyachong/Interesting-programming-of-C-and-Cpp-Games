#include <conio.h>
#include <stdio.h>

int main()
{
	int a[3][5];
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<5;j++)
			a[i][j] = i*10 + j;

	for (i=0;i<3;i++)
	{
		for (j=0;j<5;j++)
			printf("%3d",a[i][j]);
		printf("\n");
	}
	_getch();
	return 0;
}
