#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define  PI 3.1415926
#define  WIDTH 800   // 画面宽度
#define  HEIGHT 600  // 画面高度度

float offsetAngle = PI/6; // 左右枝干和父枝干偏离的角度
float shortenRate = 0.65;  // 子枝干比父枝干变短的倍数

// 把[inputMin,inputMax]范围的input变量，映射为[outputMin,outputMax]范围的output变量
float mapValue(float input,float inputMin,float inputMax,float outputMin,float outputMax)
{
	float output;
	if (abs(input-inputMin)<0.000001) // 防止除以零的bug
		output = outputMin;
	else
		output = (input-inputMin)*(outputMax-outputMin)/(inputMax-inputMin) + outputMin;
	return output;
}

// 生成[min,max]之间的随机小数
float randBetween(float min,float max)
{
	float t = rand()/double(RAND_MAX); // 生成[0,1]的随机小数
	// 调用mapValue函数，把值范围从[0,1]映射到[min,max]
	float r = mapValue(t,0,1,min,max);
	return r;
}

// 枝干生成和绘制递归函数
// 输入参数：枝干起始x y坐标，枝干长度，枝干角度，枝干绘图线条宽度，第几代
void brunch(float x_start,float y_start,float length,float angle,float thickness,int generation)
{
	// 利用三角函数求出当前枝干的终点x,y坐标
	float x_end,y_end; 
	x_end = x_start+ length* cos(angle);
	y_end = y_start+ length* sin(angle);

	// 画线条枝干
	setlinestyle(PS_SOLID,thickness); // 设定当前枝干线宽
	// 设置枝干为灰褐色，主树干最黑，子枝干逐渐变亮
	COLORREF  color = HSVtoRGB(15,0.75,0.4+generation*0.05);		
	setlinecolor(color); // 设定当前枝干颜色

	line(x_start,y_start,x_end,y_end); // 画出当前枝干（画线）

	// 求出子枝干的代数
	int childGeneration = generation + 1;	
	// 生成左、右、中间三个子枝干的长度，逐渐变短，并有一定随机性
	float childLength = shortenRate*length;
	float leftChildLength = childLength*randBetween(0.9,1.1);
	float rightChildLength = childLength*randBetween(0.9,1.1);
	float centerChildLength = childLength*randBetween(0.8,1.1);

	// 当子枝干长度大于2，并且代数小于等于10，递归调用产生子枝干
	if (childLength>=2 && childGeneration<=9) 
	{		
		// 生成子枝干的粗细，逐渐变细
		float childThickness = thickness*0.8;
		if (childThickness<2) // 枝干绘图最细的线宽为2
			childThickness = 2;

		// 一定概率产生左、右、中子枝干
		if(randBetween(0,1)<0.95)
			brunch(x_end,y_end,leftChildLength,angle+offsetAngle*randBetween(0.5,1),childThickness,childGeneration);
		if(randBetween(0,1)<0.95)
			brunch(x_end,y_end,rightChildLength,angle-offsetAngle*randBetween(0.5,1),childThickness,childGeneration);
		if(randBetween(0,1)<0.85)
			brunch(x_end,y_end,centerChildLength,angle+offsetAngle/5*randBetween(-1,1),childThickness,childGeneration);
	}
	else // 最末端绘制樱花，画一个粉色填充圆
	{
		setlinestyle(PS_SOLID,1); // 线宽
		// 樱花粉色HSVtoRGB(325,0.3,1)，有一定随机性
		COLORREF  color = HSVtoRGB(randBetween(300,350),randBetween(0.2,0.3),1);
		setlinecolor(color); // 设定线条颜色
		setfillcolor(color); // 设定填充颜色
		if (childLength<=4) // 如果子枝干长度小于等于4
			fillcircle(x_end,y_end,2); // 圆的半径为2（再小就看不清了）
		else
			fillcircle(x_end,y_end,childLength/2); // 画一个圆，半径为子枝干长度的一半
	}
}

void startup()  // 初始化
{
	srand(time(0)); // 随机初始化
	initgraph(WIDTH,HEIGHT); // 新开一个画面
	setbkcolor(RGB(255,255,255)); // 白色背景
	cleardevice(); // 清屏
	BeginBatchDraw(); // 开始批量绘制
	brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1); // 递归函数调用
	FlushBatchDraw(); // 批量绘制
}

void update()  // 每帧更新
{
	MOUSEMSG m;		
	if (MouseHit())  
	{
		m = GetMouseMsg();  
		if(m.uMsg == WM_MOUSEMOVE) // 当鼠标移动时，设定递归函数的参数
		{
			// 鼠标从左到右，左右子枝干偏离父枝干的角度逐渐变大
			offsetAngle = mapValue(m.x,0,WIDTH,PI/10,PI/4); 
			// 鼠标从上到下，子枝干比父枝干的长度缩短的更快
			shortenRate = mapValue(m.y,0,HEIGHT,0.7,0.3); 
		}
		if (m.uMsg == WM_LBUTTONDOWN) // 当鼠标左键点击时，以当前参数开始绘制一棵新数
		{
			cleardevice(); // 清屏
			brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1); // 递归调用
			FlushBatchDraw(); // 批量绘制
		}
	}
}

int main() // 主函数
{
	startup();  // 初始化 	
	while (1)  // 重复循环
		update();  // 每帧更新
	return 0;
}