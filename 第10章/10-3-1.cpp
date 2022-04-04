#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
# define BlockSize 40 // С����ĳ����С
# define RowNum 13 // ��Ϸ����һ��RowNum��С����
# define ColNum 21 // ��Ϸ����һ��ColNum��С����
# define ColorTypeNum 9 // �����ɫ��ɫ�ĸ���

struct Block // С����ṹ��
{
	int x,y; // С�����ڻ����е�x,y����
	int i,j;  // С�����ڶ�ά�����е�i,j�±�
	int colorId; // ��Ӧ��ɫ���±�
};

// ȫ�ֱ���
Block blocks[RowNum][ColNum]; // ������ά���飬�洢��������
COLORREF  colors[ColorTypeNum+1]; // ��ɫ���飬С������ܵļ�����ɫ

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
	srand(time(0)); // ������ӳ�ʼ��

	colors[0] = RGB(220,220,220); // ��ɫ�����һ����ɫΪ�Ұ�ɫ����ʾ�հ�С����
	for (i=1;i<ColorTypeNum+1;i++) // ����������ɫΪ��ɫ
		colors[i] = HSVtoRGB((i-1)*40,0.6,0.8);
	
	// ��blocks��ά������г�ʼ��
	for (i=0;i<RowNum;i++)
	{
		for (j=0;j<ColNum;j++)
		{	
			// ȡ�������1-ColorTypeNumΪ��ɫ������Ϊ�հ�ɫ
			// ����Ϊ�հ�ɫ�ı������ߣ�������Ϸ���趨
			int t = rand()%(int(ColorTypeNum*1.5));  // ȡ�����
			if (t<ColorTypeNum+1) 
				blocks[i][j].colorId = t; // С�������ɫ���
			else // �����������Ϊ�հ���ɫ����
				blocks[i][j].colorId = 0; // С�������ɫ���

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
			setfillcolor(colors[blocks[i][j].colorId]);
			fillrectangle(blocks[i][j].x,blocks[i][j].y,
						blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
		}
	}
	FlushBatchDraw(); // ��ʼ��������
}	

void updateWithoutInput() // �������޹صĸ���
{
}

void updateWithInput() // �������йصĸ���
{
	MOUSEMSG m;		
	if (MouseHit())   // ���������Ϣʱ
	{
		m = GetMouseMsg();  	
		if(m.uMsg == WM_LBUTTONDOWN) // ������������ʱ
		{
			// ͨ�����λ�ü���������С�����ڶ�ά�����е��±�
			int clicked_i = int(m.y)/BlockSize;
			int clicked_j = int(m.x)/BlockSize;

			// �����������ɫ�����Ϊ0��Ҳ���ǿհ׵ĻҰ�ɫ
			blocks[clicked_i][clicked_j].colorId = 0; 
		} 
	}
}

int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // ѭ��ִ��
	{
		show();  // ����
		updateWithoutInput(); // �������޹صĸ���
		updateWithInput();   // �������йصĸ���
	}
	return 0;
}