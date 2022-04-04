#include <conio.h>
#include <stdio.h>

void fun(int a[2])
{
	a[0] = 3;
	a[1] = 4;;
}

int main()
{
	int x[2] = {1,2};
	printf("%d %d\n",x[0],x[1]);
	fun(x);
	printf("%d %d\n",x[0],x[1]);
	_getch();
	return 0;
}