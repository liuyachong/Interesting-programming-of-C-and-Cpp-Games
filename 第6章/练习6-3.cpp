#include <conio.h>
#include <stdio.h>

void printStars(char ch,int n,int m)
{
	int i,j;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
		{
			printf("%c",ch);
		}
		printf("\n");
	}
	
}

int main()
{
	printStars('+',2,4);
	printStars('@',3,6);
	_getch();
	return 0;
}