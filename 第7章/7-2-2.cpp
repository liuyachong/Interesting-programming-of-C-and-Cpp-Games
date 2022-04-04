#include <graphics.h>  
#include <conio.h>
#include <stdio.h>

#define BLOCK_SIZE 20 // ÿ��С���ӵĳ����С 
#define HEIGHT 30 // �߶���һ��30��С����
#define WIDTH 40 //  �����һ��40��С���� 

int main() // ������
{
	initgraph(WIDTH*BLOCK_SIZE,HEIGHT*BLOCK_SIZE); //  �¿�����
	cleardevice();
	int Blocks[HEIGHT][WIDTH] = {0}; //  ��ά���飬���ڼ�¼���е���Ϸ����
	int i,j;

	for (i=0;i<HEIGHT;i++) //  �Զ�ά��������Ԫ��ֵ��ʼ��
		for (j=0;j<WIDTH;j++)
			Blocks[i][j] = rand()%30; // ��Ϊ�����

	for (i=0;i<HEIGHT;i++) //  �Զ�ά��������Ԫ�ر���
	{ 
		for (j=0;j<WIDTH;j++)
		{
			setlinecolor(RGB(200,200,200));
			setfillcolor(HSVtoRGB(Blocks[i][j]*10,0.9,1)); // ����Ԫ��ֵ�趨�����ɫ	
			// �ڶ�Ӧλ�ô����Զ�Ӧ��ɫ����С����
			fillrectangle(j*BLOCK_SIZE,i*BLOCK_SIZE,(j+1)*BLOCK_SIZE,(i+1)*BLOCK_SIZE); 
		}
	}

	_getch();
	closegraph();
	return 0;
}