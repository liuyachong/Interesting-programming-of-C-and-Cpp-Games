#include <conio.h>
#include <stdio.h>

int maxfun(int x,int y)
{
	int max = x;
	if (x<y)
		max = y;
	return max;	
}

int main()
{
	int result = maxfun(3,5);
	printf("%d\n",result);
	_getch();
	return 0;
}