#include <conio.h>
#include <stdio.h>
int main()
{
	int i;
	float a[8] = {21.5,13.7,10.5,-7,19,20.5,-2.3,13.2};
	float min = a[0];
	float max = a[0];
	for (i=1;i<8;i++)
	{
		if (a[i]<min)
			min = a[i];
		if (a[i]>max)
			max = a[i];
	}
	printf("最大值：%f，最小值：%f\n",max,min);
	_getch();
	return 0;
}