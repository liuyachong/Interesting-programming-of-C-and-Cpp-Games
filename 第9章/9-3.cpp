#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#define B_SIZE 60 // �����С
#define B_NUM 8 // ���������һ��8*8������

struct Player // �ṹ�壬���ڼ�¼���λ��
{
	int i;
	int j;
};
Player player; // ���ȫ�ֱ���

// ���ַ��Ͷ�ά����洢��ͼ����
// e: empty    w: wall    t: target    b: box    a: achieved    p:player
char level[B_NUM][B_NUM+1]= {"wwwwwwww","wwwtbeew","weeeeeew","weeeeeew",
							 "weeeeeew","weepaeew","weeewwww","wwwwwwww"};


void startup()  // ��ʼ������
{
	initgraph(B_NUM*B_SIZE,B_NUM*B_SIZE); // �¿�һ������
	setbkcolor(RGB(150,150,150)); // ��ɫ����
	BeginBatchDraw(); // ��ʼ������ͼ
	int i,j;
	// �Զ�ά�������
	for (i=0;i<B_NUM;i++)
		for (j=0;j<B_NUM;j++)
			if (level[i][j]=='p') // �ҵ���ͼ��playerλ��
			{
				player.i = i; // �趨playerλ��
				player.j = j; // 
				level[i][j]='e'; // �ѵ�ͼԪ�ر�ɿհ�empty
			}
}

void show() // ���ƺ���
{
	int i,j;
	cleardevice(); // �Ա�����ɫ�����Ļ
	// �����ؿ���ά��������
	for (i=0;i<B_NUM;i++)
	{
		for (j=0;j<B_NUM;j++)
		{
			if (level[i][j]=='e') // empty Ԫ���ǿհ�����
			{
				setfillcolor(RGB(150,150,150)); // ���ƻ�ɫ����
				setlinecolor(RGB(150,150,150));
				fillrectangle(j*B_SIZE,i*B_SIZE,(j+1)*B_SIZE,(i+1)*B_SIZE);
			}
			else if (level[i][j]=='w')  // wall Ԫ����ǽ
			{
				setfillcolor(RGB(155,0,0));
				setlinecolor(RGB(150,150,150)); // ���Ƶ���ɫ����ɫ�ߵķ���
				fillrectangle(j*B_SIZE,i*B_SIZE,(j+1)*B_SIZE,(i+1)*B_SIZE);
			}
			else if (level[i][j]=='b') // box Ԫ���ǿ��ƶ�������
			{
				setfillcolor(RGB(255,255,0)); // ����һ����ɫ�ķ���
				setlinecolor(RGB(150,150,150));
				fillrectangle(j*B_SIZE,i*B_SIZE,(j+1)*B_SIZE,(i+1)*B_SIZE);
			}
			else if (level[i][j]=='t') // target Ԫ����Ŀ��
			{
				setfillcolor(RGB(250,250,250)); // ����һ����ɫ��С����
				fillrectangle((j+0.3)*B_SIZE,(i+0.3)*B_SIZE,
					(j+0.7)*B_SIZE,(i+0.7)*B_SIZE);
			}
			else if (level[i][j]=='a') // achieved Ԫ���������Ŀ��
			{
				setlinecolor(RGB(150,150,150));
				setfillcolor(RGB(255,255,0)); // ����һ����ɫ�ķ���
				fillrectangle(j*B_SIZE,i*B_SIZE,(j+1)*B_SIZE,(i+1)*B_SIZE);
				setfillcolor(RGB(250,250,250)); // ����һ����ɫ��С����
				fillrectangle((j+0.3)*B_SIZE,(i+0.3)*B_SIZE,
					(j+0.7)*B_SIZE,(i+0.7)*B_SIZE);
			}		
		}
	}
	// ���»�����ң�����һ������ͼ��
	i = player.i; 
	j = player.j;
	setfillcolor(RGB(255,0,0));
	fillcircle((j+0.5)*B_SIZE,(i+0.5)*B_SIZE,0.4*B_SIZE);//һ����ɫԲ��
	setfillcolor(RGB(80,80,80));
	setlinecolor(RGB(80,80,80));
	fillcircle((j+0.3)*B_SIZE,(i+0.45)*B_SIZE,0.08*B_SIZE);//������ɫ�۾�
	fillcircle((j+0.7)*B_SIZE,(i+0.45)*B_SIZE,0.08*B_SIZE); 
	setlinestyle(PS_SOLID,3);
	line((j+0.35)*B_SIZE,(i+0.7)*B_SIZE,(j+0.65)*B_SIZE,(i+0.7)*B_SIZE);//���ɫ���
	setlinestyle(PS_SOLID,1);

	FlushBatchDraw(); // ��ʼ��������
}

void update()  // ÿ֡��������
{
	if(kbhit() )  // �������
	{
		char input = getch(); // ��ȡ����
		if (input=='a' || input=='s' || input=='d' || input=='w') // �������Ч����
		{
			if (input=='a') // ����
				player.j = player.j -1;
			else if (input=='d') // ����
				player.j = player.j +1 ;  
			else if (input=='s') // ����
				player.i = player.i+1;  
			else if (input=='w') // ����
				player.i = player.i-1; 
		}
	}
}

int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // ��Ϸ��ѭ��
	{
		show();		// ����
		update();   // ����
	}
	return 0;
}