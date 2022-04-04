#include <conio.h>
#include <stdio.h>
int main()
{
	int a[3];
	a[0] = 1;
	printf("%d \n",a[0]);
	a[1] = 3*a[0];
	printf("%d \n",a[1]);
	a[2] = a[0] + a[1];
	printf("%d \n",a[2]);
	_getch();
	return 0;
}