#include <conio.h>
#include <stdio.h>

int m = 1; // ȫ�ֱ������������򶼿��Է���

void fun()
{
	m = 3;
}

int main()
{
	printf("%d\n",m);
	m = 2;
	printf("%d\n",m);
	fun();
	printf("%d\n",m);
	_getch();
	return 0;
}