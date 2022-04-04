#include <conio.h>
#include <stdio.h>
int main()
{
	char str1[] = "coding ";
	char str2[] = "is fun";
	char str3[20];

	int i = 0;
	while(str1[i]!='\0')
	{
		str3[i] =  str1[i];
		i++;
	}
	int j = 0;
	while(str2[j]!='\0')
	{
		str3[i] =  str2[j];
		i++;
		j++;
	}
	str3[i] = '\0';

	printf("%s\n",str3);
	_getch();
	return 0;
}