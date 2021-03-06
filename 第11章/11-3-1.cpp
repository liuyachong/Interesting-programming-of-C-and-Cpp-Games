#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <math.h>
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
float randBetweenMinMax(float min,float max)
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
	setlinestyle(PS_SOLID,thickness); // 设定当前枝干线宽
	setlinecolor(HSVtoRGB(15,0.75,0.5)); // 设定当前枝干颜色 灰褐色
	line(x_start,y_start,x_end,y_end); // 画出当前枝干（画线）

	// 求出子枝干的代数
	int childGeneration = generation + 1;	
	// 生成子枝干的长度，逐渐变短
	float childLength = shortenRate*length;
	
	// 当子枝干长度大于等于2，并且代数小于等于10，递归调用产生子枝干
	if (childLength>=2 && childGeneration<=9) 
	{		
		// 生成子枝干的粗细，逐渐变细
		float childThickness = thickness*0.8;
		if (childThickness<2) // 枝干绘图最细的线宽为2
			childThickness = 2;

		// 产生左右的子枝干
		brunch(x_end,y_end,childLength,angle+offsetAngle,childThickness,childGeneration);
		brunch(x_end,y_end,childLength,angle-offsetAngle,childThickness,childGeneration);
		// 产生中间的子枝干
		brunch(x_end,y_end,childLength,angle,childThickness,childGeneration);
	}
	else  // 画出最末端的樱花
	{
		setlinestyle(PS_SOLID,1); // 线宽
		setlinecolor(HSVtoRGB(325,0.3,1)); // 设定线条颜色 粉色
		setfillcolor(HSVtoRGB(325,0.3,1)); // 设定填充颜色 粉色
		if (childLength<=4) // 如果子枝干长度小于等于4
			fillcircle(x_end,y_end,2); // 圆的半径为2（再小就看不清了）
		else
			fillcircle(x_end,y_end,childLength/2); // 画一个圆，半径为子枝干长度的一半
	}
}

void startup()  // 初始化
{
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