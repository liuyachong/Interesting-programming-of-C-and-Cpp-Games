#include <graphics.h>  
#include <conio.h>
#include <vector>
using namespace std;
#define  WIDTH 1000 // ���ڿ��
#define  HEIGHT 700 // ���ڸ߶�
#define  Radius 25//  С��뾶

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
	float sampleInterval; // �����������ɵĹ켣�ߣ����о��Ȳ����ļ��
	vector<Point> allPoints; //  �����Բ�������õ��Ĳ�����

	void getAllPoints() // �Բ���������в������õ����еĲ�����
	{
		int i;
		// �Թؼ������������γɵĶ����߶ν��б���
		for (i=0;i<keyPoints.size()-1;i++)
		{
			float xd = keyPoints[i+1].x - keyPoints[i].x;
			float yd = keyPoints[i+1].y - keyPoints[i].y;
			float length = sqrt(xd*xd+yd*yd); // ��һ��ֱ�߶εĳ���

			int num = length/sampleInterval; // ��һ��ֱ�߶�Ҫ�������ĸ���
			for (int j=0;j<num;j++)
			{
				float x_sample = keyPoints[i].x + j*xd/num;
				float y_sample = keyPoints[i].y + j*yd/num;
				allPoints.push_back(Point(x_sample,y_sample)); // ��ӽ�ȥ���еĲ�����
			}
		}
		// �������һ���ؼ���
		allPoints.push_back(Point(keyPoints[i].x,keyPoints[i].y));
	}
};

class Ball // ����С����
{
public:	
	Point center; // Բ������
	float radius; // �뾶
	int indexInPath; // С��λ����Path��allPoints�еĶ�Ӧ���
	int direction; // С���ƶ�����1��ǰ��-1���0��ͣ
	COLORREF color; // С����ɫ
	void draw() // ����С��
	{	
		setlinecolor(color);
		setfillcolor(color);
		fillcircle(center.x,center.y,radius); 
	}

	void movetoIndexInPath(Path path)
	{
		// ��С���ƶ��� Path��allPoints�е�indexInPath���λ��
		center = path.allPoints[indexInPath];
	}

	// ��С�����Ź켣Path�ƶ�,ע�ⲻҪԽ��
	// directionΪ0��ʱ����,directionΪ1�����յ��ƶ���directionΪ-1��������ƶ�
	void changeIndexbyDirection(Path path) 
	{
		if (direction==1 && indexInPath+1<path.allPoints.size())
			indexInPath++;
		else if (direction==-1 && indexInPath-1>=0)
			indexInPath--;
	}

	void initiate(Path path) // ��ʼ��С��path�ʼ��λ����
	{
		radius = Radius; //  �뾶
		indexInPath = 0; // ��ʼ�����
		direction = 0;
		movetoIndexInPath(path); // �ƶ���Path����Ķ�Ӧ��Ų�����λ��		
	}
};

// ���¶���һЩȫ�ֱ���
Path path; // ����켣����
Ball ball1,ball2;  // ��������С�����

void startup()  // ��ʼ������
{	
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	setbkcolor(RGB(160,211,255)); // ���ñ�����ɫ
	cleardevice(); // ����

	// Ϊ�켣�����һЩ�ؼ���
	path.keyPoints.push_back(Point(50, 300));
	path.keyPoints.push_back(Point(50, 600));
	path.keyPoints.push_back(Point(100, 650));
	path.keyPoints.push_back(Point(700, 650));
	path.keyPoints.push_back(Point(700, 550));
	path.keyPoints.push_back(Point(250, 550));
	path.keyPoints.push_back(Point(200, 500));
	path.keyPoints.push_back(Point(200, 200));
	path.keyPoints.push_back(Point(250, 150));
	path.keyPoints.push_back(Point(800, 150));
	path.keyPoints.push_back(Point(850, 200));
	path.keyPoints.push_back(Point(850, 650));
	path.keyPoints.push_back(Point(950, 650));
	path.keyPoints.push_back(Point(950, 100));
	path.keyPoints.push_back(Point(900, 50));
	path.keyPoints.push_back(Point(150, 50));

	path.sampleInterval = Radius/5; // ���ù켣�ߵĲ����������Ҫ��Radius���������ں��洦��
	path.getAllPoints();    // ��ù켣�ϵ����в�����

	ball1.initiate(path); // ��ʼ������path�ʼ��λ����
	ball1.direction = 1; // ������ǰ�ƶ�
	ball1.color = RGB(200,30,190); // ���ô���1��ɫ
	ball1.radius = Radius+3; // ���ô���1�뾶

	ball2.initiate(path); // ��ʼ��С��path�ʼ��λ����
	ball2.direction = 1; // С����ǰ�ƶ�
	ball2.color = RGB(250,170,200); // ����С��2��ɫ
	ball2.radius = Radius; // ����С��2�뾶

	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	// �Ȼ���һ�����򣬵�һ�����򵽴��յ��ʼ���ڶ���С��
	if (ball1.indexInPath < path.allPoints.size()-1)
		ball1.draw();  // ����С��1
	else
		ball2.draw();  // ����С��2		
	FlushBatchDraw(); // ��������
}

void update() // ����
{	
	// ���ƶ���һ�����򣬵�һ�����򵽴��յ��ʼ�ƶ��ڶ���С��
	if (ball1.indexInPath < path.allPoints.size()-1)
	{
		ball1.movetoIndexInPath(path);
		ball1.changeIndexbyDirection(path);
	}
	else if (ball2.indexInPath < path.allPoints.size()-2)
	{
		ball2.movetoIndexInPath(path);
		ball2.changeIndexbyDirection(path);
	}	
	if (kbhit()) // ������ʱ
	{
		char input = _getch(); // ��������ַ�
		if (input==' ') // �����¿ո��ʱ
			saveimage(_T("bk.jpg")); // ������Ƶ�ͼ��
	}
}

int main() // ������
{
	startup();  
	while (1) 
	{
		show(); 
		update(); 
	}
	return 0;
}