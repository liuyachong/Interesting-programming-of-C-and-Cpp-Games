#include <stdio.h>
#include <conio.h>
#include <vector> 
#include <algorithm>
using namespace std;

// ���vector
void printVector(vector<int> vec)
{
	int i;
	for (i=0;i<vec.size();i++)
		printf("%d ",vec[i]);
	printf("\n");
}

int main()
{
	vector<int> v;  // ����vector
	int i;

	// ���ݳ�ʼ��
	for (i=0;i<5;i++)
		v.push_back(i+1);
	printVector(v);

	// ɾ������
	v.erase(v.begin()+2); 
	printVector(v);

	// ɾ������
	v.erase(v.end()-1); 
	printVector(v);

	// ��������
	v.insert(v.begin(),3);
	printVector(v);

	// ��������
	sort(v.begin(),v.end());
	printVector(v);

	// ���vector
	v.clear();
	printf("%d",v.size());
	
	_getch();
	return 0;
}