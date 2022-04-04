#include <conio.h>
#include <stdio.h>

void swap(int *x,int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int main()
{
	int a = 1;
	int b = 2;
	printf("a=%d b=%d\n",a,b);
	swap(&a,&b);
	printf("a=%d b=%d\n",a,b);
	_getch();
	return 0;
}