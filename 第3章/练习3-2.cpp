#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	float fmin = 1.5;
	float fmax = 6.8;
	while (1)
	{
		float len = fmax - fmin;
		float r = len * rand()/float(RAND_MAX) + fmin;
		printf("%f\n",r);
		Sleep(100);
	}
	return 0;
}