#include <graphics.h>  
#include <conio.h>
#define  WIDTH 560 // ������
#define  HEIGHT 800 // ����߶�

int main()
{
	IMAGE im_bk;  // ����ͼ�����	
	loadimage(&im_bk, _T("background.png")); // ���뱳��ͼƬ
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	putimage(0, 0, &im_bk);	// ��ʾ����	
	_getch();
	return 0;
}