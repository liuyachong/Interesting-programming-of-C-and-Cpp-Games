#include <stdio.h>
#include <conio.h>

void move(char x, char  y)
{        
	printf("Move  %c to %c \n", x,y);
}

void hanoi(int n,char A,char B,char C)
{   
	if(n==1)  
		move(A,C);
	else
	{
		hanoi(n-1,A,C,B);
		move(A,C);
		hanoi(n-1,B,A,C);
	}
}

int main()
{ 
	int n;  
	printf("Input number of plates: ");
	scanf("%d",&n);
	hanoi(n,'A','B','C');
	_getch();
	return 0;
}