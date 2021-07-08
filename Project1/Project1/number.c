#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<Windows.h>

#include"number.h"

int* trans_number(char* str, int size, int flag)//перевод строки в массив чисел
{
	//массивы соотвествий дл€ больших систем счислени€
	char* low = "abcdefghijklmnopqrstuvwxyz";
	char* big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int* number_low[26] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
	int* number_big[26] = {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61};

	int* mass_number = (int*)malloc(size * sizeof(int));//массив чисел после перевода


	for (int i = 0; i < size; i++)
	{
		if ((flag == -1) && (i == 0))
		{
			mass_number[i] = -1;
			continue;
		}

		if ((str[i] >= '0') && (str[i] <= '9'))
			mass_number[i] = str[i] - 48;
		else
		{
			for (int j = 0; j < 26; j++)
			{
				if (str[i] == low[j])
					mass_number[i] = number_low[j];
				if (str[i] == big[j])
					mass_number[i] = number_big[j];
			}
		}
	}

	return(mass_number);
}


int POW(num, power)//возведение в степень
{
	int rezult = 1;
	for (int i = 0; i < power; i++)
		rezult *= num;

	return(rezult);
}


int Error_input(char* str, int size, int syst, int flag)//функци€ обработки ошибок ввода строки
{
	//проверка системы счислени€
	if ((syst < 2) || (syst > 61))
	{
		printf("¬ведена неверна€ система счислени€ %d", syst);
		exit(syst);
		system("pause");
	}

	//проверка на соотвествие системе счислени€
	int* number = (int*)malloc(size * sizeof(int));
	number = trans_number(str, size, flag);
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (number[i] > max)
			max = number[i];
	}
	if (max + 1 > syst)
	{
		printf("¬веденные данные не соответствуют системе счислени€");
		exit(syst);
		system("pause");
	}

	//проверка на посторонние символы в строке
	for (int i = 0; i < size; i++)
	{
		if ((number[i] >= -1) && (number[i] <= 61))
			max = 1;
		else 
		{
			printf("¬ведена некорректна€ строка");
			exit(number[i]);
			system("pause");
		}
	}
}


int notation(char*str, int size, int syst, int flag)//если система счислени€ введена 0, то она определ€етс€ автоматически
{
	int* number = (int*)malloc(size * sizeof(int));
	number = trans_number(str, size, flag);
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (number[i] > max)
			max = number[i];
	}
	syst = max + 1;

	return(syst);
}


int str_number()//строка->число
{
	printf("¬ведите систему счислени€: ");
	int syst;
	scanf_s("%d", &syst);

	int flag = 0;

	//ввод строки
	printf("¬ведите строку: ");
	char* str = NULL, symbol;
	int size = 0;
	symbol = fgetc(stdin);
	symbol = fgetc(stdin);
	while (symbol != '\n')
	{
		str = (char*)realloc(str, (size + 1) * sizeof(char));
		str[size] = symbol;
		size++;
		symbol = fgetc(stdin);
	}
	
	if (str[0] == '-')
		flag = -1;

	//если система счислени€ введена 0, то определ€ем ее автоматически по наибольшему элементу
	if (syst == 0)
		syst = notation(str, size, syst, flag);
	Error_input(str, size, syst, flag);

	//получаем преобразованный массив чисел
	int* mass_number = (int*)malloc(size * sizeof(int));
	mass_number = trans_number(str, size, flag);

	//переводим массив чисел в дес€тичную систему счислени€ и записываем в результат
	int rez = 0, power = 0;
	for (int i = size-1; i >= 0; i--)
	{
		if (mass_number[i] == -1)
			continue;
		int interim;
		if (power > 1)
			interim = POW(syst, power);
		else if (power == 0)
			interim = 1;
		else if (power == 1)
			interim = syst;

		rez += mass_number[i] * interim;

		power++;
	}

	if (flag == -1)
		rez *= -1;

	printf("„исло: %d", rez);
}