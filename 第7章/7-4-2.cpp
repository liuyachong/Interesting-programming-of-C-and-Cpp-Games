#include <conio.h>
#include <stdio.h>
int main()
{
	int x;
	scanf("%d",&x);

	if (x>=90)
		printf("����");
	else if (x>=80)
		printf("����");
	else if (x>=70)
		printf("�е�");
	else if (x>=60)
		printf("����");
	else 
		printf("������");

	_getch();
	return 0;
}