#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

struct node // ����ڵ�
{
	int data;
	node *next;
};

int main()
{
	node *head,*p1,*p2,*p; // ����ڵ�ָ��
	int i;
	head = 0; // ָ���һ���ڵ��ָ��

	// ��ʼ������
	for (i=1;i<=5;i++)
	{
		p1=(node *)malloc(sizeof(node)); // �����ڴ�ռ�
		(*p1).data = i; // �趨�ڵ�洢��ֵ
		if(head == 0) // �趨�����һ���ڵ�
		{
			head = p1; 
			p2 = p1;
		}
		else  // �趨�����м�ڵ�
		{
			(*p2).next = p1; 
			p2 = p1;
		}		
	}
	(*p2).next = 0; // ��ĩβ�ڵ�ָ����Ϊ0

	// �����������
	p = head;
	printf("�����ϸ���������Ϊ��\n");
	while(p!=0) // ������û�н���ʱ
	{
		printf("%d ",(*p).data); // �����ǰ�ڵ�����
		p = (*p).next; // ָ����һ���ڵ�
	}
	printf("\n");
	_getch();
	return 0;
}