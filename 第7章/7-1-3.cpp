#include <graphics.h>  
#include <conio.h>
#include <stdio.h>

// 全局变量定义

void startup()  //  初始化函数
{
}

void show()  // 绘制函数
{
}	

void updateWithoutInput() // 与输入无关的更新
{
}

void updateWithInput()  // 和输入有关的更新
{
}

int main() //  主函数
{
	startup();  // 初始化函数，仅执行一次	
	while (1)   // 一直循环
	{
		show();  // 进行绘制
		updateWithoutInput(); // 和输入无关的更新 
		updateWithInput();    // 和输入有关的更新
	}
	return 0;
}