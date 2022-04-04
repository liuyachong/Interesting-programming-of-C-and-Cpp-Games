#include <conio.h>
#include <stdio.h>
int main()
{
	int x;
	scanf("%d",&x);

	if (x>=90)
		printf("优秀");
	else if (x>=80)
		printf("良好");
	else if (x>=70)
		printf("中等");
	else if (x>=60)
		printf("及格");
	else 
		printf("不及格");

	_getch();
	return 0;
}