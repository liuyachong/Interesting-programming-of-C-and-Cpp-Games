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
int step; // ��ʣ�µĲ�������
int score; // �÷֣�Ҳ����һ����ת�˶��ٶ�

void rotateRound(int i,int j) // �Զ�ά������i��j�е�СԲȦ��˳ʱ����ת
{
	rounds[i][j].angleNum -= 1; // ֵ��1
	if (rounds[i][j].angleNum<0) // ���С��0������Ϊ3
		rounds[i][j].angleNum = 3;  
	score += 90; // �÷ּ���90��
}

// ��õ�ǰԲָ�����һ��ԲȦ���
// ��ǰԲ��Ŵ洢������int indexes[2]�У���һ��Բ���Ҳ�洢�����������
// �������һ��ָ���Բ������1�����ָ��߽��ˣ�����0
int GetNextIndexes(int indexes[2]) 
{
	int i = indexes[0]; // ��ǰԲ��i��j���
	int j = indexes[1]; // 

	// ���ݵ�ǰԲ�ĽǶȣ������һ��СԲȦ�����
	if (rounds[i][j].angleNum==0) // ָ���ұߵ�СԲȦ
		j++; // right
	else if (rounds[i][j].angleNum==3) // ָ���±ߵ�СԲȦ 
		i++; // down
	else if (rounds[i][j].angleNum==2) // ָ����ߵ�СԲȦ 
		j--; // left
	else if (rounds[i][j].angleNum==1) // ָ���ϱߵ�СԲȦ 
		i--; // up

	indexes[0] = i; // �������и���ָ�����һ��ԲȦ�����
	indexes[1] = j; // 

	if (i>=0 && i<5 && j>=0  && j<5) // ������û��Խ��
		return 1; // ˵��ָ����һ��ԲȦ������1
	else // 
		return 0; // û��ָ����ЧԲȦ������0
}

void startup()  // ��ʼ������
{
	initgraph(600,700); // �½�����
	setbkcolor(RGB(50,50,50)); // ���ñ�����ɫ
	setlinestyle(PS_SOLID,3); //  ����������ʽ���߿�
	cleardevice(); // ��ձ���
	BeginBatchDraw(); // ��ʼ��������
	step = 10; // һ�����Բ���10��
	score = 0; // ��ʼΪ0��
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
	TCHAR s[20]; // Ҫ������ַ���
	setbkmode(TRANSPARENT); // ͸����ʾ����
	_stprintf(s, _T("%d ��  %d ��"), step, score);	 // ������ת��Ϊ�ַ���
	settextstyle(50, 0, _T("����")); // �����С����ʽ
	outtextxy(150, 30, s); // ��xyλ������ַ�������
	settextstyle(20, 0, _T("����")); // 
	outtextxy(15,100,_T("���һ��ԲȦ ��ָ��˳ʱ����ת90��֮�� ָ���ָ��������ת")); 
	FlushBatchDraw();
	FlushBatchDraw(); // ��ʼ��������
}

void update()  // ���º���
{
	MOUSEMSG m;		 // ���������Ϣ
	if (MouseHit())   // ����������Ϣ
	{
		m = GetMouseMsg();  // ��������Ϣ
		if (m.uMsg == WM_LBUTTONDOWN  && step>0) // ������������������һ��п��Բ����Ĳ���
		{
			step--; // ��������-1
			int clicked_i = int(m.y -150)/100; // ��õ�ǰ���ԲȦ�����
			int clicked_j = int(m.x -50)/100; // 
			rotateRound(clicked_i,clicked_j);	// �ѵ�ǰԲȦ˳ʱ����ת90��
			show(); // ����
			Sleep(500); // ��ͣ���ɺ���

			int indexes[2] = {clicked_i,clicked_j}; // ����洢���СԲȦ���������
			while (GetNextIndexes(indexes)) // ���ָ�����һ��ԲȦ���������1����һֱ�ظ�ִ����ȥ
			{
				rotateRound(indexes[0],indexes[1]);	 // ��ָ�����һ��ԲȦҲ��ת90��
				show(); // ����
				Sleep(500); // ��ͣ���ɺ���
			}
		}
	}
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