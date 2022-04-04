#include <graphics.h>  
#include <conio.h>
#include <math.h>
#define PI 3.14159 // PI�궨��

struct Round // ����ṹ�壬������ʾ���Ƕ�ָʾ��СԲȦ
{
	float x,y; // СԲ��Բ������
	float r; // СԲ�뾶
	int angleNum;  // ��Ӧ�ĽǶȣ�����ֻ����0,1,2,3����ʾ���� PI/2 ���Ӧ���ĸ��Ƕ�ֵ
};
// ȫ�ֱ�������
Round rounds[5][5]; // �ṹ���ά����

void startup()  // ��ʼ������
{
	initgraph(600,700); // �½�����
	setbkcolor(RGB(50,50,50)); // ���ñ�����ɫ
	setlinestyle(PS_SOLID,3); //  ����������ʽ���߿�
	cleardevice(); // ��ձ���
	BeginBatchDraw(); // ��ʼ��������

	int i,j;
	// ��ʼ�� �趨5*5��25��СԲȦ
	for (i=0;i<5;i++)
	{
		for (j=0;j<5;j++)
		{
			rounds[i][j].x = 100 + j*100; // �趨СԲȦ��Բ������
			rounds[i][j].y = 200 + i*100; // 
			rounds[i][j].r = 30; // �趨СԲȦ�İ뾶
			rounds[i][j].angleNum = 1; // ��ʼ����PI/2�Ƕȣ�Ҳ���Ƕ�������
		}
	}
}

void show() // ���ƺ���
{
	int i,j;
	float angle; // 
	cleardevice();
	// ������СԲȦ����
	for (i=0;i<5;i++)
	{
		for (j=0;j<5;j++)
		{
			setlinecolor(RGB(200,200,200));  // ����ԲȦΪ�׻�ɫ
			circle(rounds[i][j].x,rounds[i][j].y,rounds[i][j].r); // ��СԲȦ
			setlinecolor(RGB(255,0,0)); // ���ýǶ�ָʾ��Ϊ��ɫ
			angle = rounds[i][j].angleNum * PI/2; // ͨ�������¼�ı����趨��Ӧ�ĽǶ�
			// �����Ǻ����������������
			line(rounds[i][j].x, rounds[i][j].y,	
				rounds[i][j].x + rounds[i][j].r * cos(-angle),
				rounds[i][j].y + rounds[i][j].r * sin(-angle));
		}
	}
	FlushBatchDraw(); // ��ʼ��������
}

void update()  // ���º���
{
}

int main() // ������
{
	startup();  // ��ʼ��
	while (1)   // �ظ�ѭ��
	{
		show();  // ����
		update();  // ����
	}
	return 0;
}