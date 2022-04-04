#include <conio.h>
#include <stdio.h>
int main()
{
	int a = 1;
	int *p;
	p = &a;
	printf("%d\n",&a);
	printf("%d\n",p);
	printf("%d\n",a);
	printf("%d\n",*p);
	_getch();
	return 0;
}
