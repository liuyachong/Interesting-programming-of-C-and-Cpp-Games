#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

# define BlockSize 40 // С����ĳ����С
# define ColorTypeNum 9 // ���˿հ׷����⣬�����������ɫ�ĸ���

struct Block // С����ṹ��
{
	int x,y; // x y����
	int colorId; // ��Ӧ��ɫ���±�
	int i,j;  // С�����ڶ�ά�����е�i j�±�
};

// ȫ�ֱ���
int RowNum; // ��Ϸ����һ��RowNum��С����
int ColNum; // ��Ϸ����һ��ColNum��С����
Block **blocks = NULL; // ��̬��ά����ָ�룬�洢���з�������
COLORREF  colors[ColorTypeNum+1]; // ��ɫ���飬С������ܵļ�����ɫ
int score; // �÷�����Ҳ������ȥ�ķ���ĸ���
float maxTime; // ��һ����Ϸ����ʱ��
float totalTime; // ��ȥ�۷�������Ϸ��ʱ��
float remainTime; // ʣ��ʱ��
clock_t start, finish; // ���ڼ�ʱ�ı���
int level = 1; // ��ǰ�ؿ����
int noZeroBlockNum; // �ǿհ������ש��ĸ���

void drawBlockHint(int i,int j,COLORREF color,int isfill) // ���Ƴ�һ����ʾ�߿����
{
	setlinecolor(color);
	setfillcolor(color);
	if (isfill==1) // ������еķ��飬����䷽����ʾ
		fillrectangle(blocks[i][j].x,blocks[i][j].y,blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
	if (isfill==0) // ���������ĸ������ҵ���4�����飬���߿���ʾ
		rectangle(blocks[i][j].x,blocks[i][j].y,blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
}


void writeRecordFile(int recordScore)  //������߷������ļ�
{ 
	FILE *fp;
	fp = fopen(".\\gameRecord.dat","w");
	fprintf(fp,"%d",recordScore);
	fclose(fp);
}

int readRecordFile()  //��ȡ��߷������ļ�
{ 
	int recordScore;
	FILE *fp;
	fp = fopen(".\\gameRecord.dat","r");

	// ����򲻿��Ļ������½�һ���ļ�����÷ּ�¼Ϊ0��
	if (fp==NULL)
	{
		writeRecordFile(0);
		return 0;
	}
	else // �ܴ�����ļ����Ͷ�ȡ����߷ּ�¼
	{
		fscanf(fp,"%d",&recordScore);
		fclose(fp);
		return recordScore;
	}
}

void startup() // ��ʼ������
{
	int i,j;
	start = clock(); // ��¼��ǰ����ʱ��

	if (level>1) // ������ǵ�1�أ����������ά�����ڴ棬�����¿����ڴ�ռ�
	{
		for (i=0;i<RowNum;i++)
			free(blocks[i]);
		free(blocks);
	}

	// �����ǵڼ��أ�������һ�ض�Ӧ����Ϸ����Ĵ�С
	RowNum = 12 + level/2;  // ������ӵ���һЩ����һ�������ε���״
	ColNum = 20 + level;

	// ���ٶ�̬��ά����
	blocks = (Block **) malloc(RowNum*sizeof(Block *));
	for (i=0;i<RowNum;i++)
		blocks[i] = (Block *) malloc(ColNum*sizeof(Block));

	maxTime = 200 + level*10; // ��һ����Ϸ�趨����ʱ����ÿ��ʱ��+10��
	totalTime = maxTime; // ��Ϸ��ʱ����ÿ�γ������10����

	int width = BlockSize*ColNum;      // �趨��Ϸ����Ĵ�С
	int height = BlockSize*(RowNum+3); // ������������ʾһЩ��ʾ��Ϣ
	initgraph(width,height);
	setbkcolor(RGB(220,220,220));
	setlinestyle(PS_SOLID,2);
	cleardevice();
	srand(time(0));
	BeginBatchDraw(); // ��ʼ��������

	score = 0; // �÷�����Ҳ������ȥ�ķ���ĸ���
	noZeroBlockNum = 0; // �ǿհ������ש��ĸ���

	colors[0] = RGB(220,220,220); // ��ɫ�����һ����ɫΪ�Ұ�ɫ����ʾ�հ�С����
	for (i=1;i<ColorTypeNum+1;i++) // ����������ɫΪ��ɫ
		colors[i] = HSVtoRGB((i-1)*40,0.6,0.8);

	// ��blocks��ά������г�ʼ��
	for (i=0;i<RowNum;i++)
	{
		for (j=0;j<ColNum;j++)
		{
			// ȡ�������1-6��Ϊ��ɫɫ�飬����Ϊ�հ�ɫ�飬����Ϊ�հ�ɫ��ļ��ʸ�һЩ
			// ��ʼ��ʱ���հ�ɫ���һЩ��������Ϸ���趨
			int t = rand()%(int(ColorTypeNum*1.5));  // ȡ�����
			if (t<ColorTypeNum+1) 
				blocks[i][j].colorId = t; // С�������ɫ���
			else // �����������Ϊ�հ���ɫ����
				blocks[i][j].colorId = 0; // С�������ɫ���
			blocks[i][j].x = j*BlockSize; // С�������Ͻ�����
			blocks[i][j].y = i*BlockSize; // 
			blocks[i][j].i = i;   // �洢��ǰС�����ڶ�ά�����е��±�
			blocks[i][j].j = j; 
			if (blocks[i][j].colorId != 0)
				noZeroBlockNum++; // ͳ����������ķ����У����㷽��ĸ���
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
			fillrectangle(blocks[i][j].x,blocks[i][j].y,blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
		}
	}

	// ����ʣ��ʱ�䣬����һ������ʱ�������������������ʱ��maxTime�����
	setlinecolor(RGB(255,0,0));
	setfillcolor(RGB(255,0,0));
	fillrectangle(0,BlockSize*(RowNum+0.2),remainTime*BlockSize*ColNum/maxTime,BlockSize*(RowNum+0.8));

	// ����÷�����
	TCHAR s[80];
	setbkmode(TRANSPARENT);
	_stprintf(s, _T("%d"), score);	
	settextcolor(RGB(0,0,0)); 
	settextstyle(22, 0, _T("����"));
	outtextxy(BlockSize*(ColNum/2-0.1), BlockSize*(RowNum+0.2), s);
	// ���һЩ��Ϸ��ʾ��Ϣ
	_stprintf(s, _T("����հ׷��飬��ʮ��������������������ͬ��ɫ����������������������ʱ��"));	
	outtextxy(BlockSize*(ColNum/15.0), BlockSize*(RowNum+1.2), s);
	_stprintf(s, _T("Ŀǰ�� %d �أ�ʱ�����ǰ�÷ִﵽ %d �ɽ�����һ��"),level,int(noZeroBlockNum*0.9));	
	outtextxy(BlockSize*(ColNum/5.0), BlockSize*(RowNum+2.2), s);

	FlushBatchDraw(); // ��������
}	

void updateWithoutInput() // �������޹صĸ���
{
	// ����ʱ����
	finish = clock(); // ��ǰʱ��
	// ��startup���к���һ����Ϸ�����˶�����
	double duration = (double)(finish - start) / CLOCKS_PER_SEC; 
	remainTime = totalTime-duration; // ��Ϸʣ���ʱ��

	// ���ʱ�䵽��
	if (remainTime<=0) 
	{
		// ��һ���ļ���¼�������ǰ�÷ֳ�����¼
		if (score > readRecordFile())
		{
			// �����µ÷ּ�¼
			writeRecordFile(score);

			// ��ʾ��ϲ������¼
			show();
			settextcolor(RGB(255,0,0)); 
			settextstyle(100, 0, _T("����"));
			outtextxy(BlockSize*(ColNum/30.0), BlockSize*(RowNum/3.0), _T("��ϲ���Ƶ÷ּ�¼"));
			FlushBatchDraw(); // ��������
			Sleep(2000);
		}

		if (score>=int(noZeroBlockNum*0.9))
		{
			level ++; // ����÷ִﵽҪ���������ǿհ׷�����Ŀ��90%���ؿ���1
		}
		startup(); // ���ó�ʼ�����������¿�ʼ��Ϸ
		return;
	}
}

void updateWithInput() // �������йصĸ���
{
	if (remainTime<=0) // ʱ�䵽�ˣ���Ҫ����
		return;

	int i,j;
	MOUSEMSG m;		
	if (MouseHit())  
	{
		m = GetMouseMsg();  	
		if(m.uMsg == WM_LBUTTONDOWN) // ������������ʱ
		{
			// ��õ����С������±�
			int clicked_i = int(m.y)/BlockSize;
			int clicked_j = int(m.x)/BlockSize;
			// �����������ʾ�����ˣ����ô�����������
			if (clicked_i>=RowNum) 
				return; 
			// �����ǰ����Ĳ��ǿհ׷��飬����Ҫ��������
			if (blocks[clicked_i][clicked_j].colorId!=0)
				return;

			show(); // ����ʾ�������飬�ٻ�����ʾ�򣬺���Ƶ�����ǰ��
			// ��������Ŀհ׷��飬����������ɫ������ʾ��
			drawBlockHint(clicked_i,clicked_j,RGB(100,100,100),1);			

			// �������飬�洢�ϡ��¡������ĸ������ҵ���һ�����ǿհ׵ķ���
			Block fourBlocks[4] = {blocks[clicked_i][clicked_j]}; // ��ʼ��Ϊ����հ׵ĵ���ķ���
			int search; // Ѱ���±�

			// ������
			for (search=0;clicked_i-search>=0;search++)
			{
				if (blocks[clicked_i-search][clicked_j].colorId!=0) // �ҵ���һ����ɫ���ǿհ׵ķ���
				{
					fourBlocks[0] = blocks[clicked_i-search][clicked_j]; // ��������洢������
					break;
				}
			}
			// ������
			for (search=0;clicked_i+search<RowNum;search++)
			{
				if (blocks[clicked_i+search][clicked_j].colorId!=0) // �ҵ���һ����ɫ���ǿհ׵ķ���
				{
					fourBlocks[1] = blocks[clicked_i+search][clicked_j]; // ��������洢������
					break;
				}
			}
			// ������
			for (search=0;clicked_j-search>=0;search++)
			{
				if (blocks[clicked_i][clicked_j-search].colorId!=0) // �ҵ���һ����ɫ���ǿհ׵ķ���
				{
					fourBlocks[2] = blocks[clicked_i][clicked_j-search]; // ��������洢������
					break;
				}
			}
			// ������
			for (search=0;clicked_j+search<ColNum;search++)
			{
				if (blocks[clicked_i][clicked_j+search].colorId!=0) // �ҵ���һ����ɫ���ǿհ׵ķ���
				{
					fourBlocks[3] = blocks[clicked_i][clicked_j+search]; // ��������洢������
					break;
				}
			}

			// ͳ��fourBlocks���ĸ�С���飬��û��ͬ����ɫ��Ŀ���ڵ���2��
			int colorStatistics[ColorTypeNum+1] = {0}; // ��ʼ������Ϊ0
			int isBadClick = 1; // �������ķ��鲻���ʣ�ʮ������û����Ч�����ķ���
			for (i=1;i<ColorTypeNum+1;i++) // i=0�ǿհ���ɫ����Ҫͳ��
			{
				for (j=0;j<4;j++) // ����fourBlocks
				{
					if (fourBlocks[j].colorId==i)
						colorStatistics[i]++; // ������ɫΪ�����i�Ļ����Ѷ�Ӧ��ͳ�Ƹ���+1
				}
				if (colorStatistics[i]>=2) // ���������ɫ����������ڵ���2
				{					
					isBadClick = 0; // �������ˣ���ε���ǺõĲ���
					// �Ѷ�Ӧʮ������Ҫ�����ķ�����ɫ�ĳɿհ���ɫ
					for (j=0;j<4;j++) // ����fourBlocks
					{
						if (fourBlocks[j].colorId==i)
						{
							// Ҫ�����ķ������������ʾ��							
							drawBlockHint(fourBlocks[j].i,fourBlocks[j].j,RGB(0,0,0),0);	
							// ��ɫ�����Ϊ0��Ҳ���ǿհ׵ĻҰ�ɫ
							blocks[fourBlocks[j].i][fourBlocks[j].j].colorId = 0; 
						}
					}
					score += colorStatistics[i]; // �÷ּ��������ķ�����
				}				
			}

			// ����ķ��飬ʮ������û���������ķ��飬Ϊ����������ȥ10����ʱ��
			if (isBadClick==1) 
				totalTime -= 10; 

			FlushBatchDraw(); // ��������
			Sleep(300); // ���ƺ���ʾ�����ͣ300����

		} // while ������������ʱ
	}
}

int main() // ����������
{
	startup();  	
	while (1) 
	{
		show(); 
		updateWithoutInput(); 
		updateWithInput();  

	}
	closegraph(); 
	return 0;
}
