#include <conio.h>
#include <stdio.h>
int main()
{
	char str[3][10]={"Wuhan", "Beijing", "Shanghai"};
	int i,j;
	// 通过二维数组元素输出
	for (i=0;i<3;i++)
	{
		for (j=0;j<10;j++)
			printf("%c",str[i][j]);
		printf("\n");
	}
	// 通过字符串形式输出
	for (i=0;i<3;i++)
		printf("%s\n",str[i]);
	_getch();
	return 0;
}