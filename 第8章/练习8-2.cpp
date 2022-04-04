#include <conio.h>
#include <stdio.h>
int main()
{
	int a = 1;
	a += 4;
	printf("%d\n",a);
	a -= 2;
	printf("%d\n",a);
	a *= 3;
	printf("%d\n",a);
	a /= 2;
	printf("%d\n",a);
	a %= 3;
	printf("%d\n",a);
	_getch();
	return 0;
}