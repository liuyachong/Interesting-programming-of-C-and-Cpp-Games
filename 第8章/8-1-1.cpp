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

int main() // ������
{
	initgraph(600,600); // �½�����
	setbkcolor(RGB(50,50,50)); // ���ñ�����ɫ
	setlinestyle(PS_SOLID,3); //  ����������ʽ���߿�
	cleardevice(); // ��ձ���

	Round round; // ����ṹ�����
	round.x = 300; // �趨СԲȦ��Բ������
	round.y = 300; // 
	round.r = 30; // �趨СԲȦ�İ뾶
	round.angleNum = 1; // 1*PI/2�Ƕȣ�Ҳ��������

	setlinecolor(RGB(200,200,200));  // ����ԲȦΪ�׻�ɫ
	circle(round.x,round.y,round.r); // ��СԲȦ
	setlinecolor(RGB(255,0,0)); // ���ýǶ�ָʾ��Ϊ��ɫ
	float angle = round.angleNum * PI/2; // ͨ�������¼�ı����趨��Ӧ�ĽǶ�
	// �����Ǻ������������������
	line(round.x,round.y,round.x + round.r*cos(-angle),round.y + round.r*sin(-angle));

	_getch();
	closegraph();
	return 0;
}