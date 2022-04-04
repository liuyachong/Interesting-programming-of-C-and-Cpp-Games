#include <conio.h>
#include <stdio.h>

int main()
{
	int a[5] = {1,2,3,4,5};
	printf("%d\n",a);
	printf("%d\n",&a[0]);
	printf("%d\n",*a);
	printf("%d\n",a[0]);
	_getch();
	return 0;
}
