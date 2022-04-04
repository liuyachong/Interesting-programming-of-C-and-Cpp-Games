#include <conio.h>
#include <stdio.h>

void fun(int i,int j)
{
	i++;
	j++;
}

int main()
{
	int x[2] = {1,2};
	printf("%d %d\n",x[0],x[1]);
	fun(x[0],x[1]);
	printf("%d %d\n",x[0],x[1]);
	_getch();
	return 0;
}