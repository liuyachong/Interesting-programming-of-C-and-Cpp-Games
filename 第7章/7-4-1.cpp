#include <conio.h>
#include <stdio.h>
int main()
{
	int x = 7;
	if (x%2==0)
		printf("%d是偶数",x);
	else
		printf("%d是奇数",x);
	_getch();
	return 0;
}