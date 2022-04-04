#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
# define BlockSize 40 // С����ĳ����С
# define RowNum 13 // ��Ϸ����һ��RowNum��С����
# define ColNum 21 // ��Ϸ����һ��ColNum��С����

struct Block // С����ṹ��
{
	int x,y; // С�����ڻ����е�x,y����
	int i,j;  // С�����ڶ�ά�����е�i,j�±� 
};

// ȫ�ֱ���
Block blocks[RowNum][ColNum]; // ������ά���飬�洢��������

void startup() // ��ʼ������
{
	int i,j;

	int width = BlockSize*ColNum;   // �趨��Ϸ����Ĵ�С
	int height = BlockSize*RowNum; 
	initgraph(width,height);		// �¿�����
	setbkcolor(RGB(220,220,220));   // ���ñ�����ɫ
	setfillcolor(RGB(255,0,0));    // �������ɫ
	setlinestyle(PS_SOLID,2);      // �������͡��߿�
	cleardevice();    // �Ա�����ɫ����
	BeginBatchDraw(); // ��ʼ��������

	// ��blocks��ά������г�ʼ��
	for (i=0;i<RowNum;i++)
	{
		for (j=0;j<ColNum;j++)
		{			
			blocks[i][j].x = j*BlockSize; // С�������Ͻǵ�����
			blocks[i][j].y = i*BlockSize; 
			blocks[i][j].i = i;   // �洢��ǰС�����ڶ�ά�����е��±�
			blocks[i][j].j = j; 
		}
	}
}

void show() // ���ƺ���
{
	cleardevice(); // ����
	setlinecolor(RGB(255,255,255)); // ��ɫ����
	int i,j;
	for (i=0;i<RowNum;i++)
	{
		for (j=0;j<ColNum;j++)
		{
			// �Զ�Ӧ����ɫ�����껭�����е�С����
			fillrectangle(blocks[i][j].x,blocks[i][j].y,
							blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
		}
	}
	FlushBatchDraw(); // ��ʼ��������
}	

int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // ѭ��ִ��
		show();  // ����
	return 0;
}