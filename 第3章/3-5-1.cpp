#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int i;
	while (1)
	{
		i = rand();
		printf("%d\n",i);
		Sleep(100);
	}
	return 0;
}