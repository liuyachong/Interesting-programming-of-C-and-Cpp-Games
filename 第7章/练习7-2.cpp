#include <conio.h>
#include <stdio.h>
int main()
{
	float height,weight,bmi;
	printf("������ߣ��ף���");
	scanf("%f",&height);
	printf("�������أ������");
	scanf("%f",&weight);
	bmi = weight/(height*height);

	if (bmi < 18.5)
		printf("���ع���");
	else if (bmi < 24)
		printf("��������");
	else if (bmi < 27)
		printf("����");
	else if (bmi < 30)
		printf("��ȷ���");
	else if (bmi < 35)
		printf("�жȷ���");
	else 
		printf("�ضȷ���");

	_getch();
	return 0;
}