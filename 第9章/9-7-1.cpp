#include <conio.h>
#include <stdio.h>
int main()
{
	char str[] = "ÎÄ¼ş²âÊÔ";
	FILE *fp=fopen("test.txt","w");
	fputs(str,fp);
	fclose(fp);
	return 0;
}