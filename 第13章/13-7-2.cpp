#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;
#define  WIDTH 1000 // ���ڿ��
#define  HEIGHT 700 // ���ڸ߶�
#define  Radius 25 //  С��뾶
#define  ColorNum 5 //  С����ɫ������Ŀ
COLORREF  colors[ColorNum] = {RED,BLUE,GREEN,YELLOW,MAGENTA}; // �������鱣�����е���ɫ

// ������֮��ľ��뺯��
float Distance(float x1,float y1,float x2,float y2)
{
	float xd = x1 - x2;
	float yd = y1 - y2;
	float length = sqrt(xd*xd+yd*yd); 
	return length;
}

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
	int direction; // С���ƶ�����1���յ㣬-1����㣬0��ͣ

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
		direction = 0; // ��ʼ��ֹ
		movetoIndexInPath(path); // �ƶ���Path����Ķ�Ӧ��Ų�����λ��		
		colorId = rand() % ColorNum; // �����ɫ���
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
};

// ��Balls�����iλ����Ѱ����ǰ����û�к�����ɫһ�����Ҷ����������������
// ����еĻ�����ɾ����,���صĽ����ɾ������С��ĸ���
// ���һ��û��ɾ�����ͷ���0
int eraseSameColorBalls(int i,Ball fireball,Path &path,vector <Ball> &balls)
{
	// ��¼��ǰ��Ͳ����С����ɫһ������ţ�����ȥ�ظ����õ���Ӧ��Ҫɾ�������
	vector<int> sameColorIndexes;  
	int forward = i; 
	int backward = i; 
	sameColorIndexes.push_back(i); // ���Ȱ�i��ӵ�vector��

	// ��Path�յ㷽��Ѱ�ң�Ҳ�������ʼ���������Ѱ��
	while(forward>0 &&  balls[forward].colorId==fireball.colorId)
	{
		sameColorIndexes.push_back(forward);
		if (balls[forward-1].indexInPath - balls[forward].indexInPath>2*Radius/path.sampleInterval)
			break; // ǰ��һ�������������������ѭ��
		forward--;
	}
	if (forward==0 && balls[0].colorId==fireball.colorId) // ���������������ӽ��յ���Ǹ���
		sameColorIndexes.push_back(forward);

	// ��Path��㷽��Ѱ�ң�Ҳ�������������ķ���Ѱ��
	while (backward<balls.size()-1 && balls[backward].colorId==fireball.colorId) // ��û���ҵ����һ���������
	{
		sameColorIndexes.push_back(backward);
		if (balls[backward].indexInPath - balls[backward+1].indexInPath>2*Radius/path.sampleInterval)
			break; // ǰ��һ�������������������ѭ��
		backward++;
	}
	if (backward==balls.size()-1 && balls[balls.size()-1].colorId==fireball.colorId) // ���������������ӽ������Ǹ���
		sameColorIndexes.push_back(backward);

	// ȥ��ͬ����ɫС�����ظ������
	sort(sameColorIndexes.begin(), sameColorIndexes.end());
	vector<int>::iterator ite = unique(sameColorIndexes.begin(), sameColorIndexes.end());
	sameColorIndexes.erase(ite, sameColorIndexes.end());

	int NumSameColors = sameColorIndexes.size();
	if (NumSameColors>=3) // ��ͬ��ɫ����ﵽ3��������
	{
		int minIndex = sameColorIndexes[0];
		int maxIndex = sameColorIndexes[NumSameColors-1];
		// ����Щ���ɾ��						
		balls.erase(balls.begin()+minIndex,balls.begin()+maxIndex+1);
		return NumSameColors; // �����ˣ���������С����Ŀ
	}
	return 0; // û������������0
}

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

	// �����һЩС��
	for (int i=0;i<15;i++)
	{
		Ball ball;  // ����һ��С�����
		ball.initiate(path); // ��ʼ��С��path�ʼ��λ����	
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

void updateWithoutInput() // �������޹صĸ���
{	
	if (balls.size()==0) // С���������
		return; 
	// ��һ�����ܵ��յ��ˣ���Ϸʧ��
	if (balls[0].indexInPath >= path.allPoints.size()-1)
		return;

	int i;	
	for (i=0;i<balls.size();i++)
		balls[i].direction = 0; // ��������С����ٶ���Ϊ0

	//balls��ǰ�ƶ���Դ�������������һ��С�����һ��С��direction=1
	//����յ㷽��ǰ��һ��С������С���������У�����directionҲΪ1������directionΪ0
	i = balls.size() - 1; // ���һ��С��
	balls[i].direction = 1; // ���һ��С����ǰ�˶�

	while (i>0)  // һֱ��ǰ�жϣ���û�б�������ǰ��һ��С��
	{
		// ���ǰ������С����������
		if (balls[i-1].indexInPath-balls[i].indexInPath <= 2*Radius/path.sampleInterval)
		{
			balls[i-1].direction = 1; // ǰһ��С��ķ���Ҳ����ǰ
			// ��ǰһ��С���indexInPath���й��򻯣�ȷ����������
			balls[i-1].indexInPath = balls[i].indexInPath+2*Radius/path.sampleInterval; 
			i--;
		}
		else // ��һ��С��ֱ�ӽӴ�����ֹͣ��ǰ�ٶȵĴ���
			break; // ����ѭ��
	}

	for (int i=0;i<balls.size();i++)  // ÿһ��С�������direction��������λ��
	{
		balls[i].movetoIndexInPath(path);
		balls[i].changeIndexbyDirection(path);
	}

	Sleep(50); // ��ͣ���ɺ���
}

void updateWithInput()  // ��������صĸ���
{
	if (balls.size()==0) // С���������
		return; 

	int i,j;
	MOUSEMSG m;		// ���������Ϣ
	while (MouseHit())  // ��⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if(m.uMsg == WM_LBUTTONDOWN)  // ���������ʱ			
		{				
			// balls������С�������������жϣ������Ƿ������һ��С��
			for (i=0;i<balls.size();i++)
			{
				float distance = Distance(balls[i].center.x, 
					balls[i].center.y,m.x,m.y); 
				if (distance<Radius) // ���������һ��С��
				{			
					// ���渴��һ��С�򣬲��뵽����ط�
					Ball fireball = balls[i];
					balls.insert(balls.begin()+i,fireball);//����һ��С�����vector

					// ��Balls�����iλ����Ѱ����ǰ����û�к�����ɫһ�����Ҷ���3��������������
					// ����ǵĻ�����ɾ����,���صĽ����ɾ������С��ĸ���
					// ���һ��û��ɾ�����ͷ���0
					int count = eraseSameColorBalls(i,fireball,path,balls);
					if (count==0)// ���û�������Ļ�
					{
						for (j=i;j>=0;j--) // �ƶ�ǰ���С�������ռ�����²����С��
						{
							if (balls[j].indexInPath - balls[j+1].indexInPath <=0)
								balls[j].indexInPath = balls[j+1].indexInPath + 
								2*Radius/path.sampleInterval;
							else
								break;// ǰ��С����п�϶�������ٴ�����
						}
					}
					return; // �ҵ�һ���������ײ��С���ˣ�����Ĳ���������
				}
			}  // for (i=0;i<balls.size();i++)
		} // ���������ʱ	
	} 
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
		updateWithoutInput();  // �������޹صĸ���
		updateWithInput();  // ��������صĸ���
	}
	gameover(); // ��Ϸ����ʱ�Ĵ���
	return 0;
}