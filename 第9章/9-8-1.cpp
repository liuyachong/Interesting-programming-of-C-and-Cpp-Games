#include <conio.h>
#include <stdio.h>

enum Element // ����ö�����ͣ�С�������еĿ��ܵ�����
{
	wall,target,box,empty,achieved,role
};

int main()
{
	Element e;
	e = box;
	// ���ڴ洢��ͼ���ݣ���ö������ʵ��
	Element level[8][8] = 
	{{wall,wall,wall,wall,wall,wall,wall,wall},
	{wall,wall,wall,target,box,empty,empty,wall},
	{wall,empty,empty,empty,empty,empty,empty,wall},
	{wall,empty,empty,empty,empty,empty,empty,wall},
	{wall,empty,empty,empty,empty,empty,empty,wall},
	{wall,role,empty,box,target,wall,wall,wall},
	{wall,empty,empty,empty,empty,wall,wall,wall},
	{wall,wall,wall,wall,wall,wall,wall,wall}};

	_getch();
	return 0;
}
