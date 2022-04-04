#include <conio.h>
#include <stdio.h>
int main()
{
	int i;
	for (i=1;i<=5;i++)
	{
		if (i==3)
			break;
		printf("%d\n",i);
	}	
	_getch();
	return 0;
}