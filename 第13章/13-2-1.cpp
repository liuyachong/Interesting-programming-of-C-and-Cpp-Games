#include <stdio.h>
#include <conio.h>
#include <vector> 
using namespace std;

int main()
{
	vector<int> v;  // ����vector
	int i;

	// ���ݳ�ʼ��
	for (i=0;i<5;i++)
		v.push_back(i+1);
	
	// ���vector
	for (i=0;i<v.size();i++)
		printf("%d ",v[i]);
	printf("\n");
	
	_getch();
	return 0;
}