#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include <vector>
using namespace std;
#define  WIDTH 1000 // ���ڿ��
#define  HEIGHT 700 // ���ڸ߶�
#define  Radius 25 //  С��뾶
#define  ColorNum 5 //  С����ɫ������Ŀ
COLORREF  colors[ColorNum] = {RED,BLUE,GREEN,YELLOW,MAGENTA}; // �������鱣�����е���ɫ

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

	void draw() // �����켣
	{
		setlinecolor(RGB(0,0,0)); // ����������ɫ
		setfillcolor(RGB(0,0,0)); // ���������ɫ
		// �����ؼ������������γɵĶ����߶�
		for (int i=0;i<keyPoints.size()-1;i++)
			line(keyPoints[i].x,keyPoints[i].y,keyPoints[i+1].x,keyPoints[i+1].y); 
		// ���в����㴦���ֱ�һ��СԲ��
		for (int i=0;i<allPoints.size();i++)
			fillcircle(allPoints[i].x,allPoints[i].y,2); 
	}

	~Path()  // ��������
	{
		keyPoints.clear(); // ���vector���ڴ�ռ�
		allPoints.clear();
	}
};

class Ball // ����С����
{
public:	
	Point center; // Բ������
	float radius; // �뾶
	int colorId;  // С�����ɫ��ţ�������ɫ��colors������ȡ
	int indexInPath; // С��λ����Path��allPoints�еĶ�Ӧ���

	void draw() // ����С��
	{
		setlinecolor(colors[colorId]);
		setfillcolor(colors[colorId]);
		fillcircle(center.x,center.y,radius); 
	}

	void movetoIndexInPath(Path path)
	{
		// ��С���ƶ��� Path��allPoints�е�indexInPath���λ��
		center = path.allPoints[indexInPath];
	}

	void initiate(Path path) // ��ʼ��С��path�ʼ��λ����
	{
		radius = Radius; //  �뾶
		indexInPath = 0; // ��ʼ�����
		movetoIndexInPath(path); // �ƶ���Path����Ķ�Ӧ��Ų�����λ��		
		colorId = rand() % ColorNum; // �����ɫ���
	}
};

// ���¶���һЩȫ�ֱ���
Path path; // ����켣����
vector <Ball> balls; // ��¼���С��

void startup()  // ��ʼ������
{	
	srand(time(0)); // �����ʼ������
	initgraph(WIDTH,HEIGHT); // �¿�һ������
	setbkcolor(WHITE); // ���ñ�����ɫ
	cleardevice(); // ����

	// Ϊ�켣�����һЩ�ؼ���
	path.keyPoints.push_back(Point(100, 600));
	path.keyPoints.push_back(Point(900, 600));
	path.keyPoints.push_back(Point(900, 100));
	path.keyPoints.push_back(Point(100, 100));

	path.sampleInterval = Radius/5; // ���ù켣�ߵĲ���������豻Radius�����Ա㴦��
	path.getAllPoints();    // ��ù켣�ϵ����в�����

	// ���һЩС��
	for (int i=30;i>=0;i--)
	{
		Ball ball;  // ����һ��С�����
		ball.initiate(path); // ��ʼ��С��path�ʼ��λ����	
		// ������ţ����ñ�֤��������С������
		ball.indexInPath = i* (2*ball.radius/path.sampleInterval); 
		ball.movetoIndexInPath(path);
		balls.push_back(ball); // ��С��ball��ӵ�balls��
	}

	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	cleardevice(); // ����
	path.draw();  // �����켣
	for (int i=0;i<balls.size();i++)
		balls[i].draw();  // ��������С��
	FlushBatchDraw(); // ��������
	Sleep(1); // ��ʱ
}

void gameover() // ��Ϸ����ʱ�Ĵ���
{
	balls.clear(); // ���vector���ڴ�ռ�
}

int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // ѭ��
	{
		show(); // ��ʾ
	}
	gameover(); // ��Ϸ����ʱ�Ĵ���
	return 0;
}