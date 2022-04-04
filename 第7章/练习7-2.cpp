#include <conio.h>
#include <stdio.h>
int main()
{
	float height,weight,bmi;
	printf("输入身高（米）：");
	scanf("%f",&height);
	printf("输入体重（公斤）：");
	scanf("%f",&weight);
	bmi = weight/(height*height);

	if (bmi < 18.5)
		printf("体重过轻");
	else if (bmi < 24)
		printf("体重正常");
	else if (bmi < 27)
		printf("过重");
	else if (bmi < 30)
		printf("轻度肥胖");
	else if (bmi < 35)
		printf("中度肥胖");
	else 
		printf("重度肥胖");

	_getch();
	return 0;
}