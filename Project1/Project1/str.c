#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<Windows.h>

#include"str.h"


int Error_input_str(int syst)//проверка на корректность введенных данных
{
	if ((syst < 2) || (syst > 61))
	{
		printf("¬ведена неверна€ система счислени€ %d", syst);
		exit(syst);
	}
}


int number_str()
{
	printf("¬ведите систему счислени€: ");
	int syst;
	scanf_s("%d", &syst);

	printf("¬ведите число: ");
	int number;
	scanf_s("%d", &number);

	Error_input_str(syst);


}