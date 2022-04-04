#include <conio.h>
#include <stdio.h>

void fun1( )
{
	printf("a\n");
}

void fun2( )
{
	fun1( );
	printf("b\n");
}

int main()
{
	fun2( );
	printf("c\n");
	_getch();
	return 0;
}