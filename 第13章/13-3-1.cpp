#include <graphics.h>  
#include <conio.h>
#include <vector>
using namespace std;
#define  WIDTH 1000 // ���ڿ��
#define  HEIGHT 700 // ���ڸ߶�

class Point // ���嶥����
{
public:
	float x,y; // ��¼(x,y)����
	Point() // �޲����Ĺ��캯��
	{
	}
	Point (float ix,float iy) // �в����Ĺ��캯��
	{
		x = ix;
		y = iy;
	}
};

class Path  // ����켣��
{
public:
	vector<Point> keyPoints; //  ��¼�켣�ϵ�һЩ�ؼ��㣬�ؼ���֮����ֱ������

	void draw() // �����켣
	{
		setlinecolor(RGB(0,0,0)); // ����������ɫ
		setfillcolor(RGB(0,0,0)); // ���������ɫ
		// �ؼ��㴦��СԲȦ
		for (int i=0;i<keyPoints.size();i++)
			fillcircle(keyPoints[i].x,keyPoints[i].y,8);
		// �����ؼ������������γɵĶ����߶�
		for (int i=0;i<keyPoints.size()-1;i++)
			line(keyPoints[i].x,keyPoints[i].y,keyPoints[i+1].x,keyPoints[i+1].y); 
	}
};

// ���¶���һЩȫ�ֱ���
Path path; // ����켣����

void startup()  // ��ʼ������
{	
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	setbkcolor(WHITE); // ���ñ�����ɫ
	cleardevice(); // ����

	// Ϊ�켣�����һЩ�ؼ���
	path.keyPoints.push_back(Point(100, 600));
	path.keyPoints.push_back(Point(900, 600));
	path.keyPoints.push_back(Point(900, 100));
	path.keyPoints.push_back(Point(100, 100));

	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	cleardevice(); // ����
	path.draw();  // �����켣
	FlushBatchDraw(); // ��������
	Sleep(1); // ��ʱ
}

int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // ѭ��
	{
		show(); // ��ʾ
	}
	return 0;
}