#include <conio.h>
#include <stdio.h>

void fun()
{
	int m=0;
	m++;
	printf("%d\n",m);
}

int main()
{
	fun();
	fun();
	fun();
	_getch();
	return 0;
}