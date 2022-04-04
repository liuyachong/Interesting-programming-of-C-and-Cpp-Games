#include <stdio.h>
#include <conio.h>
#include <vector> 
using namespace std;

int main()
{
	vector<int> v;  // 定义vector
	int i;

	// 数据初始化
	for (i=0;i<5;i++)
		v.push_back(i+1);
	
	// 输出vector
	for (i=0;i<v.size();i++)
		printf("%d ",v[i]);
	printf("\n");
	
	_getch();
	return 0;
}