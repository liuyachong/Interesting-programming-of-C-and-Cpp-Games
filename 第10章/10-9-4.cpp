#include <conio.h>
#include <stdio.h>
#include<stdlib.h>
int main()
{
	int n,i;
	scanf("%d",&n);
	int *p = (int *) malloc(n * sizeof(int));
	for (i=0;i<n;i++)
		p[i] = i+1;
	for (i=0;i<n;i++)
		printf("%d ",p[i]);
	free(p);
	_getch();
	return 0;
}
