#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int height,width,i,j;
	scanf("%d%d",&height,&width); // �û��Զ������볤��

	// ���䶯̬��ά������ڴ�ռ�
	int **blocks=(int**)malloc(height*sizeof(int*)); 
	for(i=0;i<height;i++)
		blocks[i]=(int*)malloc(width*sizeof(int));

	// blocks���Ե���һ���ά������ʹ����
	for (i=0;i<height;i++)
		for (j=0;j<width;j++)
			blocks[i][j] = i*width+j+1;

	for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
			printf("%3d",blocks[i][j]);
		printf("\n");
	}

	// ʹ���������̬������ڴ�ռ�
	for(i=0; i<height; i++)
		free(blocks[i]);
	free(blocks);
	_getch();
	return 0;
}