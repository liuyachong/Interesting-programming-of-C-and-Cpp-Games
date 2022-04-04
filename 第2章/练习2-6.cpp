#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int x = 12*14*16*18;
	if (x > 50000)
		printf("结果大于50000");
	if (x == 50000)
		printf("结果等于50000");
	if (x < 50000)
		printf("结果小于50000");
	_getch();
	return 0;
}