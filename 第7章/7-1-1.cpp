#include <conio.h>
#include <stdio.h>

void fun()
{
	int a; // 局部变量，仅能在fun函数内部使用
	a = 10;
}

int main()
{
	int x; // 局部变量，仅能在main函数内部使用
	x = 1;
	_getch();
	return 0;
}
