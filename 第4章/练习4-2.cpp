#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int i,j;

	// 首先打印第一行表头
	printf("   ");
	for (i=1;i<=9; i=i+1)
		printf("%3d",i);
	printf("\n");

	for (i=1;i<=9; i=i+1) // 对行遍历
	{
		printf("%3d",i);  // 打印第一列表头
		for (j=1;j<=i; j=j+1) // 对列遍历，只打印下三角部分
		{
			printf("%3d",i*j); // 最内层，打印乘积
		}
		printf("\n");
	}
	_getch();
	return 0;
}