#include <conio.h>
#include <stdio.h>
int main()
{
	int i;
	float a[7] = {1.2,2.3,3.0,4.8,5.6,6.9,7.8};
	float sum = 0;
	for (i=0;i<7;i++)
		sum = sum + a[i]*a[i];
	printf("%f\n",sum);
	_getch();
	return 0;
}