#include <conio.h>
#include <stdio.h>
int main()
{
	int i;
	int a[5] = {1,3,5,7,9};
	for (i=0;i<5;i++)
		printf("%d ",a[i]);
	printf("\n");
	int b[5] = {2,4,6};
	for (i=0;i<5;i++)
		printf("%d ",b[i]);
	printf("\n");
	_getch();
	return 0;
}