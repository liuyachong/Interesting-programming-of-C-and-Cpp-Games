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
float maxTime; // ��Ϸ�������ʱ��
float remainTime; // ��Ϸʣ��ʱ��
int score; // �÷�����Ҳ������ȥ�ķ���ĸ���
int noZeroBlockNum; // �ǿհ������ש��ĸ���

// ����blocks[i][j]������һ����ɫΪcolor��isfill������ʾ����
void drawBlockHint(int i,int j,COLORREF color,int isfill) 
{
	setlinecolor(color); // ����������ɫ
	setfillcolor(color); // ���������ɫ
	if (isfill==1) // ����䷽��
		fillrectangle(blocks[i][j].x,blocks[i][j].y,
		blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
	if (isfill==0) // �������ķ����߿�
		rectangle(blocks[i][j].x,blocks[i][j].y,
		blocks[i][j].x+BlockSize,blocks[i][j].y+BlockSize);
}

void startup() // ��ʼ������
{
	int i,j;

	int width = BlockSize*ColNum;   // �趨��Ϸ����Ĵ�С
	int height = BlockSize*(RowNum+2); // ������������ʾһЩ��ʾ��Ϣ
	initgraph(width,height);		// �¿�����
	setbkcolor(RGB(220,220,220));   // ���ñ�����ɫ
	setfillcolor(RGB(255,0,0));    // �������ɫ
	setlinestyle(PS_SOLID,2);      // �������͡��߿�
	cleardevice();    // �Ա�����ɫ����
	BeginBatchDraw(); // ��ʼ��������
	srand(time(0)); // ������ӳ�ʼ��

	maxTime = 200; // ��Ϸ�������ʱ��
	remainTime = maxTime; // ��Ϸʣ��ʱ��

	colors[0] = RGB(220,220,220); // ��ɫ�����һ����ɫΪ�Ұ�ɫ����ʾ�հ�С����
	for (i=1;i<ColorTypeNum+1;i++) // ����������ɫΪ��ɫ
		colors[i] = HSVtoRGB((i-1)*40,0.6,0.8);

	noZeroBlockNum = 0;
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
			if (blocks[i][j].colorId != 0)
				noZeroBlockNum++; // ͳ����������ķ����У����㷽��ĸ���
		}
	}
	score = 0; // �÷�����Ҳ������ȥ�ķ���ĸ���
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
	setlinecolor(RGB(255,0,0)); // ���ý���������ɫ
	setfillcolor(RGB(255,0,0));
	// ����ʣ��ʱ�䣬����һ������ʱ�������������������ʱ��maxTime�����
	fillrectangle(0,BlockSize*(RowNum+0.2),
		remainTime*BlockSize*ColNum/maxTime,BlockSize*(RowNum+0.8));

	// �����ʾ������Ϣ
	TCHAR s[80]; // �����ַ�����
	setbkmode(TRANSPARENT); // ͸����ʾ����
	settextcolor(RGB(0,0,0));  // ����������ɫ
	settextstyle(22, 0, _T("����")); // �������ִ�С������	
	_stprintf(s, _T("��ǰ%d�֣��ﵽ%d����Ϸʤ��"), score,int(0.9*noZeroBlockNum));	
	outtextxy(BlockSize*(ColNum/3-0.1), BlockSize*(RowNum+1.2), s); // �������
	if (score>=0.9*noZeroBlockNum) // ��ȥ�㹻�ķ��飬��Ϸʤ��
	{
		settextstyle(130, 0, _T("����")); // �������ִ�С������
		outtextxy(BlockSize*(ColNum/6.0), BlockSize*(RowNum/3.0), _T("��Ϸʤ��!"));
	}

	FlushBatchDraw(); // ��ʼ��������
}	

void updateWithoutInput() // �������޹صĸ���
{
	if (remainTime<=0) // ʱ�䵽�ˣ���Ҫ����
		return;
	static clock_t start = clock(); // ��¼��һ������ʱ��
	clock_t now = clock(); // ��õ�ǰʱ��
	// �������һ�������˶�����
	double duration = double(now - start) / CLOCKS_PER_SEC; 
	remainTime = maxTime - duration; // ������Ϸʣ��ʱ��
}

void updateWithInput() // �������йصĸ���
{
	if (remainTime<=0) // ʱ�䵽�ˣ���Ҫ����
		return;
	int i,j;
	MOUSEMSG m;		
	if (MouseHit())   // ���������Ϣʱ
	{
		m = GetMouseMsg();  	
		if(m.uMsg == WM_LBUTTONDOWN) // ������������ʱ
		{
			// ͨ�����λ�ü���������С�����ڶ�ά�����е��±�
			int clicked_i = int(m.y)/BlockSize;
			int clicked_j = int(m.x)/BlockSize;

			// �����ǰ����Ĳ��ǿհ׷��飬����Ҫ��������
			if (blocks[clicked_i][clicked_j].colorId!=0)
				return;

			show(); // ����ʾ�������飬�ٻ�����ʾ�򣬺���Ƶ�����ǰ��
			// ��������Ŀհ׷��飬����������ɫ������ʾ��
			drawBlockHint(clicked_i,clicked_j,RGB(100,100,100),1);	

			// ��������洢�ϡ��¡������ĸ������ҵ���һ�����ǿհ׵ķ���
			Block fourBlocks[4] = {blocks[clicked_i][clicked_j]}; //��ʼ��Ϊ����ķ���
			int search; // Ѱ���±�

			// �����ҵ���һ����ɫ���ǿհ׵ķ���
			for (search=0;clicked_i-search>=0;search++)
			{
				if (blocks[clicked_i-search][clicked_j].colorId!=0) 
				{
					fourBlocks[0] = blocks[clicked_i-search][clicked_j];//��������Ԫ��
					break;
				}
			}
			// �����ҵ���һ����ɫ���ǿհ׵ķ���
			for (search=0;clicked_i+search<RowNum;search++)
			{
				if (blocks[clicked_i+search][clicked_j].colorId!=0)  
				{
					fourBlocks[1] = blocks[clicked_i+search][clicked_j];//��������Ԫ��
					break;
				}
			}
			// �����ҵ���һ����ɫ���ǿհ׵ķ���
			for (search=0;clicked_j-search>=0;search++)
			{
				if (blocks[clicked_i][clicked_j-search].colorId!=0)
				{
					fourBlocks[2] = blocks[clicked_i][clicked_j-search];//��������Ԫ��
					break;
				}
			}
			// �����ҵ���һ����ɫ���ǿհ׵ķ���
			for (search=0;clicked_j+search<ColNum;search++)
			{
				if (blocks[clicked_i][clicked_j+search].colorId!=0) 
				{
					fourBlocks[3] = blocks[clicked_i][clicked_j+search];//��������Ԫ��
					break;
				}
			}

			// ͳ��fourBlocks���ĸ�С���飬��û��ͬ����ɫ��Ŀ���ڵ���2��
			int colorStatistics[ColorTypeNum+1] = {0}; // ��ʼ������Ϊ0
			for (i=1;i<=ColorTypeNum;i++) // i=0�ǿհ���ɫ����Ҫͳ��
			{
				for (j=0;j<4;j++) // ����fourBlocks
				{
					if (fourBlocks[j].colorId==i)
						colorStatistics[i]++; //������ɫ���i����Ӧͳ�Ƹ���+1
				}
				if (colorStatistics[i]>=2) // ���������ɫ����������ڵ���2
				{					
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

			FlushBatchDraw(); // ��������
			Sleep(300); // ���ƺ���ʾ�����ͣ300����

		} // if ������������ʱ
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