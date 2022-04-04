#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

struct node // 定义节点
{
	int data;
	node *next;
};

int main()
{
	node *head,*p1,*p2,*p; // 定义节点指针
	int i;
	head = 0; // 指向第一个节点的指针

	// 初始化链表
	for (i=1;i<=5;i++)
	{
		p1=(node *)malloc(sizeof(node)); // 分配内存空间
		(*p1).data = i; // 设定节点存储的值
		if(head == 0) // 设定链表第一个节点
		{
			head = p1; 
			p2 = p1;
		}
		else  // 设定链表中间节点
		{
			(*p2).next = p1; 
			p2 = p1;
		}		
	}
	(*p2).next = 0; // 最末尾节点指针设为0

	// 输出链表数据
	p = head;
	printf("链表上各结点的数据为：\n");
	while(p!=0) // 当链表没有结束时
	{
		printf("%d ",(*p).data); // 输出当前节点数据
		p = (*p).next; // 指向下一个节点
	}
	printf("\n");
	_getch();
	return 0;
}