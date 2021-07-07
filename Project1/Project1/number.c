#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<Windows.h>

#include"number.h"

int* trans_number(char* str, int size)//перевод строки в массив чисел
{
	//массивы соотвествий для больших систем счисления
	char* low = "abcdefghijklmnopqrstuvwxyz";
	char* big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int* number_low[26] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
	int* number_big[26] = {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61};

	int* mass_number = (int*)malloc(size * sizeof(int));//массив чисел после перевода

	for (int i = 0; i < size; i++)
	{
		printf("%c", str[i]);
	}

	for (int i = 0; i < size; i++)
	{
		if ((str[i] >= '0') && (str[i] <= '9'))
		{
			mass_number = str[i] - 48;
		}
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

	for (int i = 0; i < size; i++)
	{
		printf("%d", mass_number[i]);
	}
}

int str_number()//строка->число
{
	system("cls");
	
	printf("Введите систему счисления: ");
	int syst;
	scanf_s("%d", &syst);

	//ввод строки
	printf("Введите строку: ");
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

	trans_number(str, size);
}