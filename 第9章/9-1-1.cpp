#include <conio.h>
#include <stdio.h>
int main()
{
	char str1[6] = "hello";
	printf("%s\n",str1);
	char str2[6] = {'h','e','l','l','o','\0'};
	printf("%s\n",str2);
	char str3[10] = "hello";
	printf("%s\n",str3);
	char str4[] = "hello";
	printf("%s\n",str4);
	_getch();
	return 0;
}