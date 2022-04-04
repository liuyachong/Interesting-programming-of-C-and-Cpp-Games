#include <conio.h>
#include <stdio.h>

void fun(int a)
{
	a++;
	printf("%d\n",a);
}

int main()
{
	int x = 1;
	printf("%d\n",x);
	fun(x);
	printf("%d\n",x);
	_getch();
	return 0;
}