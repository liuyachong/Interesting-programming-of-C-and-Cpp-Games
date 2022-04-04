#include <conio.h>
#include <stdio.h>

enum Element // 定义枚举类型，小方块所有的可能的种类
{
	wall,target,box,empty,achieved,role
};

int main()
{
	Element e;
	e = box;
	// 用于存储地图数据，用枚举类型实现
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
