#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int x = 12*14*16*18;
	if (x > 50000)
		printf("�������50000");
	if (x == 50000)
		printf("�������50000");
	if (x < 50000)
		printf("���С��50000");
	_getch();
	return 0;
}