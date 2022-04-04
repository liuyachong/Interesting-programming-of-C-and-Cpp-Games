#include <conio.h>
#include <stdio.h>
int main()
{
	char str[80];
	FILE *fp=fopen("µÇðÙÈ¸Â¥.txt","r");
	while (!feof(fp))
	{	
		fgets(str,80,fp);
		printf("%s",str);
	}
	fclose(fp);
	_getch();
	return 0;
}