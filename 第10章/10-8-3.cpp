#include <conio.h>
#include <stdio.h>
int main()
{
	int a = 1;
	int *p,*q;
	p = &a;
	q = p;
	*q = 2;	
	printf("%d\n",a);
	printf("%d\n",*p);
	printf("%d\n",*q);
	_getch();
	return 0;
}
