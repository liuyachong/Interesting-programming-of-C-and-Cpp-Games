#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
int main()
{
	float Pi = 3.14159;  // Բ����Pi
	initgraph(800,600); // ��һ������
	setbkcolor(RGB(128,128,128)); // ���ñ�����ɫΪ��ɫ
	cleardevice();  // �Ա�����ɫ��ջ���

	int centerX,centerY; // Բ������
	int radius; // Բ�뾶	
	int i;
	float offset;  // ͬһ�뾶��������֮��ĽǶ�ƫ����
	float totalOffset = 0; // ��ͬ�뾶֮��ĽǶ�ƫ����

	for (centerX = 100;centerX<800;centerX=centerX+200) // ��Բ��x����ѭ��
	{
		for (centerY = 100;centerY<600;centerY=centerY+200) // ��Բ��y����ѭ��
		{
			float h = rand()%180; // ���ɫ��
			COLORREF  color1 = HSVtoRGB(h,0.9,0.8); // ɫ��1���ɵ���ɫ1
			COLORREF  color2 = HSVtoRGB(h+180,0.9,0.8); // ɫ��2���ɵ���ɫ2
			for (radius=100;radius>0;radius=radius-20) // �뾶�Ӵ�С����
			{
				int left = centerX - radius; // Բ���о������Ͻ�x����
				int top = centerY - radius; // Բ���о������Ͻ�y����
				int right = centerX + radius; // Բ���о������½�x����
				int bottom = centerY + radius; // Բ���о������½�y����	
				for (i=0;i<20;i++) // ������תһ�ܣ�������������
				{
					offset = i*Pi/10 + totalOffset; // ��������֮��ƫ�ƵĽǶ�
					setfillcolor(color1); // ɫ��1���ɵ���ɫ1
					solidpie(left,top,right,bottom,offset,2*Pi/60+offset); 
					setfillcolor(RGB(255,255,255));// ���������ɫΪ��ɫ
					solidpie(left,top,right,bottom,2*Pi/60+offset,3*Pi/60+offset); 
					setfillcolor(color2); // ɫ��2���ɵ���ɫ2
					solidpie(left,top,right,bottom,3*Pi/60+offset,5*Pi/60+offset); 
					setfillcolor(RGB(0,0,0));// ���������ɫΪ��ɫ
					solidpie(left,top,right,bottom,5*Pi/60+offset,6*Pi/60+offset); 
				}
				totalOffset = totalOffset + Pi/20; // ��ͬ�뾶��Ƕ�ƫ����ΪPi/20
			}
		}
	}

	_getch();  // ��ͣ���ȴ���������
	return 0;
}