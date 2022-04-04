#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	printf("%d\n",(2>3));
	printf("%d\n",(5<6));
	printf("%d\n",!(2>3));
	printf("%d\n",(2>3)&&(5<6));
	printf("%d\n",(2>3)||(5<6));
	_getch();
	return 0;
}