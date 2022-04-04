#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"  // ������ʾ��͸��ͨ����pngͼƬ
// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
#define  WIDTH 560 // ������
#define  HEIGHT 800 // ����߶�
#define	 MaxBulletNum 200  // ����ӵ�����

void sleep(DWORD ms)  // ��ȷ��ʱ����
{
	static DWORD oldtime = GetTickCount();
	while(GetTickCount() - oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}

void PlayMusicOnce(TCHAR fileName[80]) // ����һ�����ֺ���
{
	TCHAR cmdString1[50];
	_stprintf(cmdString1, _T("open %s alias tmpmusic"), fileName);	// ���������ַ���
	mciSendString(_T("close tmpmusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
	mciSendString(cmdString1, NULL, 0, NULL); // ������
	mciSendString(_T("play tmpmusic"), NULL, 0, NULL); // ������һ��	
}

class Rocket  // ��������
{
public:
	IMAGE im_rocket; // ���ͼ��
	IMAGE im_blowup; // ��ըͼ��
	float x,y; // �������
	float width,height; // ���ͼƬ�Ŀ�ȡ��߶�
	int liveSecond; // �������˶೤ʱ��
	int life;  // ����м�����

	void draw() // ��ʾ��������Ϣ	
	{
		// �������Ͻ���ʾlife�����ͼƬ����ʾ���������
		for (int i=0;i<life;i++)
			putimagePng(i*width*0.9,0,&im_rocket);

		// �������Ϸ���ʾ����˶�����
		TCHAR s[20];
		setbkmode(TRANSPARENT); // ��������͸��
		_stprintf(s, _T("%d��"), liveSecond);	
		settextcolor(WHITE); // �趨������ɫ
		settextstyle(40, 0, _T("����"));//  �趨���ִ�С����ʽ
		outtextxy(WIDTH*0.85, 20, s); //  �����������

		if (life>0) // ��������û������ʾ��ͬ��ͼƬ
			putimagePng(x - width/2,y-height/2,&im_rocket);  // ��Ϸ����ʾ���ͼƬ
		else
			putimagePng(x - width/2,y-height/2,&im_blowup);  // ��Ϸ����ʾ��ըͼƬ
	}

	void update(float mx,float my) // ���������������»����λ��
	{
		x = mx;
		y = my;
	}

	void updateWhenLifeLost() // ���������ʱִ�еĲ���
	{
		PlayMusicOnce(_T("explode.mp3"));  // ����һ�α�ը��Ч
		life --; // ��������
	}
};

class Bullet  // �����ӵ���
{
public:
	IMAGE im_bullet; // �ӵ�ͼ��
	float x,y; // �ӵ�����
	float vx,vy; // �ӵ��ٶ�
	float radius; // �ӽ�������ӵ��뾶��С

	void draw()// ��ʾ�ӵ�	
	{
		putimagePng(x - radius,y-radius,&im_bullet);  
	}

	void update() // �����ӵ���λ�á��ٶ�
	{
		x += vx;
		y += vy;
		if (x<=0 || x>=WIDTH)
			vx = -vx;
		if (y<=0 || y>=HEIGHT)
			vy = -vy;
	}

	int isCollideRocket(Rocket rocket) // �ж��ӵ��Ƿ�ͻ����ײ
	{
		float distance_x = abs(rocket.x - x);
		float distance_y = abs(rocket.y - y);
		if ( distance_x < rocket.width/2 && distance_y < rocket.height/2 )
			return 1; // ������ײ����1
		else
			return 0; // ����ײ����0	
	}
};

class SmartUFO: public Bullet // ���ܷɵ��࣬��Bullet����������
{
public:
	void updateVelforTarge(Rocket targetRocket) // �÷ɵ����ٶ�����Ŀ����
	{
		float scalar = 1*rand()/double(RAND_MAX) + 1; // �ٶȴ�С��һ���������
		if (targetRocket.x>x) // Ŀ���ڷɵ���ߣ��ɵ�x�����ٶ�����
			vx = scalar;
		else if (targetRocket.x<x) // Ŀ���ڷɵ��ұߣ��ɵ�x�����ٶ�����
			vx = -scalar;
		if (targetRocket.y>y) // Ŀ���ڷɵ��·����ɵ�y�����ٶ�����
			vy = scalar;
		else if (targetRocket.y<y) // Ŀ���ڷɵ��Ϸ����ɵ�y�����ٶ�����
			vy = -scalar;
	}
};

IMAGE im_bk,im_bullet,im_rocket,im_blowup,im_UFO;  // ����ͼ�����	
Bullet bullet[MaxBulletNum]; // �����ӵ���������
Rocket rocket;  // ����������
SmartUFO ufo;  // ����ɵ�����
int bulletNum = 0; // �����ӵ��ĸ���

void startup()  //  ��ʼ������
{	
	mciSendString(_T("open game_music.mp3 alias bkmusic"), NULL, 0, NULL);//�򿪱�������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // ѭ������

	srand(time(0)); // ��ʼ���������
	loadimage(&im_bk, _T("background.png")); // ���뱳��ͼƬ
	loadimage(&im_bullet, _T("bullet.png")); // �����ӵ�ͼƬ
	loadimage(&im_rocket, _T("rocket.png")); // ������ͼƬ
	loadimage(&im_blowup, _T("blowup.png")); // ���뱬ըͼƬ
	loadimage(&im_UFO, _T("ufo.png")); // ����ɵ�ͼƬ

	// �Էɵ���һЩ��Ա������ʼ��
	ufo.x = WIDTH/2;  // ���÷ɵ�λ��
	ufo.y = 10;
	ufo.im_bullet = im_UFO; // ���÷ɵ�ͼƬ
	ufo.radius = im_UFO.getwidth()/2; // ���÷ɵ��뾶��С
	ufo.updateVelforTarge(rocket); // ���·ɵ����ٶ�

	// ��rocketһЩ��Ա������ʼ��
	rocket.im_rocket = im_rocket;  // ���û��ͼƬ
	rocket.im_blowup = im_blowup;  // ���û����ըͼƬ
	rocket.width = im_rocket.getwidth(); // ���û�����
	rocket.height = im_rocket.getheight(); // ���û���߶�
	rocket.life = 5; // �����ʼ5���� 

	initgraph(WIDTH,HEIGHT); // �¿�һ������
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	putimage(0, 0, &im_bk);	// ��ʾ����	
	ufo.draw();  // ��ʾ�ɵ�
	for (int i=0;i<bulletNum;i++)
		bullet[i].draw();  // ��ʾ���е��ӵ�
	rocket.draw();  // ��ʾ����������Ϣ
	FlushBatchDraw(); // ��������
	sleep(10); // ��ͣ
}

void updateWithoutInput() // �������޹صĸ���
{
	if (rocket.life<=0) // ���û�����ˣ�������
		return; // ֱ�ӷ���

	static int lastSecond = 0; // ��¼ǰһ�γ��������˶�����
	static int nowSecond = 0; // ��¼��ǰ���������˶�����
	static clock_t start = clock(); // ��¼��һ������ʱ��
	clock_t now = clock(); // ��õ�ǰʱ��
	// �������Ŀǰһ�������˶�����
	nowSecond =( int(now - start) / CLOCKS_PER_SEC);
	rocket.liveSecond = nowSecond; // ��������˶����븳ֵ

	if (nowSecond==lastSecond+1) // ʱ�����1���ӣ������·ɵ����ٶ�
		ufo.updateVelforTarge(rocket); // ufo�ٶȷ�����׼���

	if (nowSecond==lastSecond+2) // ʱ�����2���ӣ�����һ���ӵ�
	{
		lastSecond = nowSecond; // ������lastSecond����
		// ���û�г�������ӵ���Ŀ�����ƣ�����һ���µ��ӵ�
		if (bulletNum<MaxBulletNum)
		{
			bullet[bulletNum].x = WIDTH/2; // �ӵ���ʼλ��
			bullet[bulletNum].y = 10;
			float angle = (rand()/double(RAND_MAX)-0.5)*0.9*PI;
			float scalar = 2*rand()/double(RAND_MAX) + 2;
			bullet[bulletNum].vx = scalar*sin(angle); // �ӵ�����ٶ�
			bullet[bulletNum].vy = scalar*cos(angle);
			bullet[bulletNum].im_bullet = im_bullet;  // �����ӵ�ͼ��
			bullet[bulletNum].radius = im_bullet.getwidth()/2; // �ӵ��뾶ΪͼƬ���һ��
		}
		bulletNum++; // �ӵ���Ŀ��һ
	}

	for (int i=0;i<bulletNum;i++) // ���������е��ӵ�
	{
		bullet[i].update(); // �����ӵ���λ�á��ٶ�		
		if (bullet[i].isCollideRocket(rocket)) // �ж��ӵ��Ƿ�ͻ����ײ
		{
			rocket.updateWhenLifeLost(); // ���������ز���
			bullet[i].x = 5; // ��ǰ�ӵ��ƿ�����ֹ�ظ���ײ
			bullet[i].y = 5; 
			break; // �����ը�������ٺ������ӵ��Ƚ���
		}
	}

	ufo.update(); // ���·ɵ���λ�á��ٶ�		
	if (ufo.isCollideRocket(rocket)) // �жϷɵ��Ƿ�ͻ����ײ
	{
		rocket.updateWhenLifeLost(); // ���������ʱִ�еĲ���
		ufo.x = 5; // ��ǰ�ɵ��ƿ�����ֹ�ظ���ײ
		ufo.y = 5; 
	}
}

void updateWithInput()  // ��������صĸ���
{
	if (rocket.life<=0) // ���û�����ˣ�������
		return; // ֱ�ӷ���

	MOUSEMSG m;		// ���������Ϣ
	while (MouseHit())  // ��⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if(m.uMsg == WM_MOUSEMOVE)  // ������ƶ�ʱ			
			rocket.update(m.x,m.y); // �����λ�õ���������ڵ�λ��
	}	
}

int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // �ظ�����
	{
		show();  // ����
		updateWithoutInput();  // �������޹صĸ���
		updateWithInput();  // ��������صĸ���
	}
	return 0;
}