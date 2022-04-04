#include <conio.h>
#include <stdio.h>
int main()
{
	int i,s;

	s = 0;
	for (i=1;i<=50;i++)
		s = s + i*i;
	printf("%d\n",s);

	i = 1;
	s = 0;
	while (i<=50)
	{
		s = s + i*i;
		i++;
	}
	printf("%d\n",s);

	_getch();
	return 0;
}