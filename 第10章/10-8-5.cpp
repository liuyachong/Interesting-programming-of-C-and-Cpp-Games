#include <conio.h>
#include <stdio.h>

void fun(int &a)
{
	a = a + 1;
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