#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int imin = 3;
	int imax = 8;
	while (1)
	{
		int r = rand() % (imax-imin+1) + imin;
		printf("%d\n",r);
		Sleep(100);
	}
	return 0;
}