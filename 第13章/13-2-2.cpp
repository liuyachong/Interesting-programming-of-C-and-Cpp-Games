#include <stdio.h>
#include <conio.h>
#include <vector> 
#include <algorithm>
using namespace std;

// 输出vector
void printVector(vector<int> vec)
{
	int i;
	for (i=0;i<vec.size();i++)
		printf("%d ",vec[i]);
	printf("\n");
}

int main()
{
	vector<int> v;  // 定义vector
	int i;

	// 数据初始化
	for (i=0;i<5;i++)
		v.push_back(i+1);
	printVector(v);

	// 删除数据
	v.erase(v.begin()+2); 
	printVector(v);

	// 删除数据
	v.erase(v.end()-1); 
	printVector(v);

	// 插入数据
	v.insert(v.begin(),3);
	printVector(v);

	// 升序排序
	sort(v.begin(),v.end());
	printVector(v);

	// 清空vector
	v.clear();
	printf("%d",v.size());
	
	_getch();
	return 0;
}