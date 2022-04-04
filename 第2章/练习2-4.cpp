#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int i = -1;
	while(1)
	{
		i = i+2;
		printf("%d\n",i);
		Sleep(100);
	}
	_getch();
	return 0;
}