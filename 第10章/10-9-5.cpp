#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int height,width,i,j;
	scanf("%d%d",&height,&width); // 用户自定义输入长宽

	// 分配动态二维数组的内存空间
	int **blocks=(int**)malloc(height*sizeof(int*)); 
	for(i=0;i<height;i++)
		blocks[i]=(int*)malloc(width*sizeof(int));

	// blocks可以当成一般二维数组来使用了
	for (i=0;i<height;i++)
		for (j=0;j<width;j++)
			blocks[i][j] = i*width+j+1;

	for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
			printf("%3d",blocks[i][j]);
		printf("\n");
	}

	// 使用完清除动态数组的内存空间
	for(i=0; i<height; i++)
		free(blocks[i]);
	free(blocks);
	_getch();
	return 0;
}