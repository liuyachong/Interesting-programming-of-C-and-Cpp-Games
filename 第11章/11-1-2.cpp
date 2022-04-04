#include <conio.h>
#include <stdio.h>

int fac(int n)
{  
	int f;
	if(n==1) 
		f=1;
	else 
		f=n*fac(n-1);
	return (f);
}

int main()
{
	int num = fac(5);
	printf("5!= %d \n",num);  
	_getch();
	return 0;
}