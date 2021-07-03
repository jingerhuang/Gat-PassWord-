#pragma warning(disable:4996)				 //vs对scanf禁用的禁用、dev可以删除
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char shuziku[] = "0123456789";										 /*字符库*/
char zimuku[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char teshuku[] = "!@#$%^&*_-";

int panduanx0(char* p)								   /*判断首字符是否是数字*/
{
	if (*p >= 0 && *p <= 9)
		return 1;
	else
		return 0;
}

int panduanx1(char* p)								   /*判断是否有英文大小写*/
{
	int i, m = 0, n = 0;
	for (i = 0; i < strlen(p); i++)
	{
		if ((*(p + i) < 'z' && *(p + i) > 'a'))
			m = 1;
		if ((*(p + i) < 'Z' && *(p + i) > 'A'))
			n = 1;
	}
	if (m && n)											   /*同时有英文大小写*/
		return 0;
	else
		return 1;
}

int panduanx2(char* p)									 /*判断是否有特殊字符*/
{
	int i,m=0,n;
	for(n=0;n<10;n++)									   /*特殊字符库有10个*/
		for (i = 0; i < strlen(p); i++)
		{
			if ((*(p + i) == teshuku[n]))
				return 0;
		
		}
		return 1;
}

void fuzamima(int mima_c_d,char *p)					       /*复杂密码生成函数*/
{	
	int i, n, m;
	int x[3];
	printf("是输1，否输0\n");
	printf("开头不可为数字\n");
	scanf("%d", &x[0]);
	printf("必须包含英语大小写\n");
	scanf("%d", &x[1]);
	printf("含有字符\n");
	scanf("%d", &x[2]);
	do {
		for (i = 0; i < mima_c_d; i++)
		{
			if (x[2])								   /*检测是否需要特殊字符*/
				m = rand() % 3;
			else									   /*生成不同情况的随机数*/
				m = rand() % 2;
			if (m == 0)/*根据产生的随机数调用字符库，在各字符库中选取随机字符*/
			{											  /*填入密码的i+1位上*/
				*(p + i) = shuziku[(rand() % strlen(shuziku))];
			}
			else if (m == 1)
			{
				*(p + i) = zimuku[(rand() % strlen(zimuku))];
			}
			else
			{
				*(p + i) = teshuku[(rand() % strlen(teshuku))];
			}
		}
		*(p + i) = '\0';										 /*封闭字符串*/
	} while((panduanx0(p)&&x[0])||(panduanx1(p)&&x[1])||(panduanx2(p)&& x[2]));
}					/*判断是否满足密码条件*//*小括号内的同时为1时需要重新生成*/

void shuzimima(int mima_c_d, char* p)				 /*数字密码生成，节省步骤*/
{
	int i;
	for (i = 0; i < mima_c_d; i++)						   /*调用数字库随机值*/
	{
			*(p + i) = shuziku[(rand() % strlen(shuziku))];
	}
	*(p + i) = '\0';
}

void mimazhuangtaixuanzhe()									   /*密码长度输入*/
{
	int d;
	struct mimazu  /*生成密码组，后期可配合文件调用函数实现批量生成密码并存储*/
	{
		int MAXchangdu;
		int MINchangdu;
		int shijichangdu;
		char mima[100];
	}m1;
	
	printf("最大长度\n");
	scanf("%d",&m1.MAXchangdu);
	printf("最小长度\n");
	scanf("%d", &m1.MINchangdu);
	m1.shijichangdu = rand() % (m1.MAXchangdu-m1.MINchangdu+1)+ m1.MINchangdu;
															   /*生成随机长度*/
	printf("长度=%d\n需要什么样的密码\n",m1.shijichangdu);
	printf("复杂密码\t1\n六位数字密码\t2\n四位数字密码\t3\n");
	scanf("%d", &d);
	if(d==1)
		fuzamima(m1.shijichangdu,&m1.mima);
	else if(d==2)
		shuzimima(6, &m1.mima);
	else
		shuzimima(4, &m1.mima);
	printf("密码=%s\n", m1.mima);
}

int main()															 /*主函数*/
{	
	int n, i;
	printf("您需要几条密码\n");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		mimazhuangtaixuanzhe();
	}
	system("pause");
	return 0;
}
