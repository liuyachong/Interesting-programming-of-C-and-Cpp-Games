#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#define BLOCK_SIZE 20 // ÿ��С���ӵĳ����С 
#define HEIGHT 30 // �߶���һ��30��С����
#define WIDTH 40 //  �����һ��40��С���� 
int main() // ������
{
	initgraph(WIDTH*BLOCK_SIZE,HEIGHT*BLOCK_SIZE); //  �¿�����
	setlinecolor(RGB(200,200,200));
	cleardevice();
	int Blocks[HEIGHT][WIDTH] = {0}; //  ��ά���飬���ڼ�¼���е���Ϸ����
	int i,j;
	Blocks[HEIGHT/2][WIDTH/2] = 1; // �����м仭��ͷ������Ϊ1
	for (i=1;i<=4;i++) //  ��������4��������ֵ����Ϊ2,3,4,5
		Blocks[HEIGHT/2][WIDTH/2-i] = i+1;
	for (i=0;i<HEIGHT;i++) //  �Զ�ά��������Ԫ�ر���
	{ 
		for (j=0;j<WIDTH;j++)
		{
			if (Blocks[i][j]>0) // Ԫ�ش���0��ʾ���ߣ��������ߵ�������ɫɫ������
				setfillcolor(HSVtoRGB(Blocks[i][j]*10,0.9,1));
			else 
				setfillcolor(RGB(150,150,150)); // Ԫ��Ϊ0��ʾΪ�գ���ɫΪ��ɫ
			// �ڶ�Ӧλ�ô����Զ�Ӧ��ɫ����С����
			fillrectangle(j*BLOCK_SIZE,i*BLOCK_SIZE,
						 (j+1)*BLOCK_SIZE,(i+1)*BLOCK_SIZE); 
		}
	}
	_getch();
	closegraph();
	return 0;
}