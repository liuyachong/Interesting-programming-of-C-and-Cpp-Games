#include <conio.h>
#include <stdio.h>

int main()
{
	int a[5] = {1,2,3,4,5};
	int *p = a;
	int i;
	for (i=0;i<5;i++)
		printf("%d ",a[i]);
	printf("\n");
	for (i=0;i<5;i++)
		printf("%d ",*(a+i));
	printf("\n");
	for (i=0;i<5;i++)
		printf("%d ",*(p+i));
	printf("\n");
	for (i=0;i<5;i++)
		printf("%d ",p[i]);
	printf("\n");
	_getch();
	return 0;
}
