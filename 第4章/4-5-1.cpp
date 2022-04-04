#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int i,j;
	for (i=1;i<=9; i=i+1)
	{
		for (j=1;j<=9; j=j+1)
		{
			printf("%3d",i*j); // 输出整数占3个字符，用于对齐
		}
		printf("\n");
	}
	_getch();
	return 0;
}