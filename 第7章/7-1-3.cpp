#include <graphics.h>  
#include <conio.h>
#include <stdio.h>

// ȫ�ֱ�������

void startup()  //  ��ʼ������
{
}

void show()  // ���ƺ���
{
}	

void updateWithoutInput() // �������޹صĸ���
{
}

void updateWithInput()  // �������йصĸ���
{
}

int main() //  ������
{
	startup();  // ��ʼ����������ִ��һ��	
	while (1)   // һֱѭ��
	{
		show();  // ���л���
		updateWithoutInput(); // �������޹صĸ��� 
		updateWithInput();    // �������йصĸ���
	}
	return 0;
}