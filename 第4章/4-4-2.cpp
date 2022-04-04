#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int i,sum;
	sum = 0;
	for (i=1;i<=100;i=i+1)
		sum = sum + i;
	printf("%d\n",sum);
	_getch();
	return 0;
}