#include <conio.h>
#include <stdio.h>
int main()
{
	char str[] = "hello world!";
	int i = 0;
	while(str[i]!='\0')
		i++;
	printf("%d\n",i);
	_getch();
	return 0;
}