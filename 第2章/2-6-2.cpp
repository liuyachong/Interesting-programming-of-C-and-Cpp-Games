#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int i = 0;
	while(1)
	{
		i = i+1;
		printf("%d\n",i);
		Sleep(100);
	}
	_getch();
	return 0;
}