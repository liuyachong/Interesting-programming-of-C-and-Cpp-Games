#include <conio.h>
#include <stdio.h>

void printStars(char ch,int num)
{
	int i;
	for (i=1;i<=num;i++)
	{
		printf("%c",ch);
	}
	printf("\n");
}

int main()
{
	printStars('+',3);
	printStars('@',5);
	printStars('0',8);
	_getch();
	return 0;
}