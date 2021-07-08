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

char* trans_str(int* mass_number, int size, int flag)
{
	//массивы соотвествий дл€ больших систем счислени€
	char* low = "abcdefghijklmnopqrstuvwxyz";
	char* big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int* number_low[26] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };
	int* number_big[26] = { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61 };

	char* str = (char*)malloc(size * sizeof(char));//строка 

	//сопоставление элементов по внутреннему алфавиту
	for (int i = 0; i < 10; i++)
	{
		if ((mass_number[i] >= 0) && (mass_number[i] <= 9))//если числа из массива можно записать без букв, то используем коды ASCII
			str[i] = mass_number[i] + 48;
		else
		//если числа больше 9, тогда используем внутренний алфавит дл€ записи их в виде букв
		{
			for (int j = 0; j < 26; j++)
			{
				if (mass_number[i] == number_low[j])
					str[i] = low[j];
				if (mass_number[i] == number_big[j])
					str[i] = big[j];
			}
		}
	}

	//если флаг равен -1, тогда в конец строки запишем "-", потому что вывод строки будет с конца
	if (flag = -1)
	{
		str = (char*)realloc(str, (size + 1) * sizeof(char));
		str[size] = '-';
	}

	return(str);
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

	//перевод в указанную систему счислени€
	int* mass_number = NULL;//промежуточный массив
	int size = 0;
	int flag = 0;

	if (number < 0)//если число меньше 0, тогда домножим его на -1 и запишем это в флаг
	{
		number *= -1;
		flag = -1;
	}

	while (number % syst < number)//алгоритм перевода из 10 —— в любую
	{
		mass_number = (int*)realloc(mass_number, (size + 1) * sizeof(int));
		mass_number[size] = number % syst;
		number /= syst;
		size++;
	}
	mass_number[size] = number;//записываем так же последнее значение
	size++;

	//строка результата
	char* str = (char*)malloc(size * sizeof(char));
	str = trans_str(mass_number, size, flag);

	if (flag = -1)//если флаг -1, тогда увеличим размер на 1, потому что в конце строки лежит дополнительный -
		size++;

	//вывод строки
	printf("—трока: ");
	for (int i = size - 1; i >= 0; i--)
		printf("%c", str[i]);
}