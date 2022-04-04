#include <conio.h>
#include <stdio.h>
#define B_NUM 8 
int main()
{
	char level[B_NUM][B_NUM+1]; 
	FILE *fp=fopen("level.txt","r");
	char str[80];
	int i,j;
	for (i=0;i<B_NUM;i++)
	{	
		fgets(str,80,fp);
		printf("%s",str);
		for (j=0;j<B_NUM;j++)
			level[i][j] = str[j];
	}
	fclose(fp);
	_getch();
	return 0;
}