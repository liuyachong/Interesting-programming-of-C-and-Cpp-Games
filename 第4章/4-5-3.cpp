#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // Բ����Pi
	initgraph(1200,800); // ��һ��600*600�Ĵ���
	setbkcolor(RGB(128,128,128)); // ���ñ�����ɫΪ��ɫ
	cleardevice();  // �Ա�����ɫ��ջ���

	int centerX,centerY; // Բ������
	int radius; // Բ�뾶	
	int i;
	float offset;  // ͬһ�뾶��������֮��ĽǶ�ƫ����
	float totalOffset = 0; // ��ͬ�뾶֮��ĽǶ�ƫ����

	for (centerX = 200;centerX<1200;centerX=centerX+400) // ��Բ��x����ѭ��
	{
		for (centerY = 200;centerY<800;centerY=centerY+400) // ��Բ��y����ѭ��
		{
			for (radius=200;radius>0;radius=radius-50) // �뾶�Ӵ�С����
			{
				int left = centerX - radius; // Բ���о������Ͻ�x����
				int top = centerY - radius; // Բ���о������Ͻ�y����
				int right = centerX + radius; // Բ���о������½�x����
				int bottom = centerY + radius; // Բ���о������½�y����	
				for (i=0;i<20;i++) // ������תһ�ܣ�������������
				{
					offset = i*Pi/10 + totalOffset; // ��������֮��ƫ�ƵĽǶ�
					setfillcolor(RGB(0,240,220));// ���������ɫΪ��ɫ
					solidpie(left,top,right,bottom,offset,2*Pi/60+offset); //���������
					setfillcolor(RGB(255,255,255));// ���������ɫΪ��ɫ
					solidpie(left,top,right,bottom,2*Pi/60+offset,3*Pi/60+offset);//���������
					setfillcolor(RGB(200,0,0));// ���������ɫΪ��ɫ
					solidpie(left,top,right,bottom,3*Pi/60+offset,5*Pi/60+offset);//���������
					setfillcolor(RGB(0,0,0));// ���������ɫΪ��ɫ
					solidpie(left,top,right,bottom,5*Pi/60+offset,6*Pi/60+offset);//���������
				}
				totalOffset = totalOffset + Pi/20; // ��ͬ�뾶��Ƕ�ƫ����ΪPi/20
			}
		}
	}

	_getch();  // ��ͣ���ȴ���������
	return 0;
}