#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int i,j;

	// ���ȴ�ӡ��һ�б�ͷ
	printf("   ");
	for (i=1;i<=9; i=i+1)
		printf("%3d",i);
	printf("\n");

	for (i=1;i<=9; i=i+1) // ���б���
	{
		printf("%3d",i);  // ��ӡ��һ�б�ͷ
		for (j=1;j<=i; j=j+1) // ���б�����ֻ��ӡ�����ǲ���
		{
			printf("%3d",i*j); // ���ڲ㣬��ӡ�˻�
		}
		printf("\n");
	}
	_getch();
	return 0;
}