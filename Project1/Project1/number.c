#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<Windows.h>

#include"number.h"

int* trans_number(char* str, int size, int flag)//перевод строки в массив чисел
{
	//массивы соотвествий для больших систем счисления
	char* low = "abcdefghijklmnopqrstuvwxyz";
	char* big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int* number_low[26] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
	int* number_big[26] = {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61};

	int* mass_number = (int*)malloc(size * sizeof(int));//массив чисел после перевода

	//сопоставление элементов по внутреннему алфавиту
	for (int i = 0; i < size; i++)
	{
		if ((flag == -1) && (i == 0))//если переданный флаг -1 и это первый элемент массива, то в первый элемент массива чисел запишем -1(внутреннее соглашение)
		{
			mass_number[i] = -1;
			continue;
		}

		if ((str[i] >= '0') && (str[i] <= '9'))//если символ это число, то просто запишем число в массив через коды ASCII
			mass_number[i] = str[i] - 48;
		else
		//если символ не число, тогда будем сопоставлять буквы с их числовыми значениями из внутреннего алфавита
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


int Error_input(char* str, int size, int syst, int flag)//функция обработки ошибок ввода строки
{
	//проверка системы счисления
	if ((syst < 2) || (syst > 61))
	{
		printf("Введена неверная система счисления %d", syst);
		exit(syst);
		system("pause");
	}

	//проверка на соотвествие системе счисления
	//находим максимальное число после перевода в массив чисел
	//если максимально число +1 больше чем система счисления, значит в строке содержиться символ, выходящий за пределы введеной СС
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
		printf("Введенные данные не соответствуют системе счисления");
		exit(syst);
		system("pause");
	}

	//проверка на посторонние символы в строке
	for (int i = 0; i < size; i++)
	{
		if ((number[i] >= -1) && (number[i] <= 61))//от -1, потому что если число отрицательное - первый элемент массива чисел будет -1
			max = 1;
		else 
		{
			printf("Введена некорректная строка");
			exit(number[i]);
			system("pause");
		}
	}
}


int notation(char*str, int size, int syst, int flag)//если система счисления введена 0, то она определяется автоматически
{
	//переводим строку в массив чисел
	//находим максимально число и по нему определяем систему счисления
	int* number = (int*)malloc(size * sizeof(int));
	number = trans_number(str, size, flag);
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (number[i] > max)
			max = number[i];
	}
	syst = max + 1;//система счисления - максимальный элемент +1

	return(syst);
}


int str_number()//строка->число
{
	printf("Введите систему счисления: ");
	int syst;
	scanf_s("%d", &syst);

	int flag = 0;

	//ввод строки
	printf("Введите строку: ");
	char* str = NULL, symbol;
	int size = 0;
	symbol = fgetc(stdin);//два раза чтобы случайно не считался enter от предыдущего ввода
	symbol = fgetc(stdin);
	while (symbol != '\n')//ввод пока не будет нажат enter
	{
		str = (char*)realloc(str, (size + 1) * sizeof(char));
		str[size] = symbol;
		size++;
		symbol = fgetc(stdin);
	}
	
	if (str[0] == '-')//введено отрицательное число мы это запомни в флаг
		flag = -1;

	//если система счисления введена 0, то определяем ее автоматически по наибольшему элементу
	if (syst == 0)
		syst = notation(str, size, syst, flag);
	Error_input(str, size, syst, flag);//проверка некорректного ввода

	//получаем преобразованный массив чисел
	int* mass_number = (int*)malloc(size * sizeof(int));
	mass_number = trans_number(str, size, flag);

	//переводим массив чисел в десятичную систему счисления и записываем в результат
	int rez = 0, power = 0;
	for (int i = size-1; i >= 0; i--)
	{
		if (mass_number[i] == -1)//если первый элемент равен -1, то просто добавим "-" в итоговый результат
			continue;
		int interim;//переменная для хранения степени
		if (power > 1)
			interim = POW(syst, power);//если степень больше 1, то возводим в нужную
		else if (power == 0)//если степень 0, то промежуточный результат будет 1
			interim = 1;
		else if (power == 1)//если степень 1, то промежуточный будет равен системе счисления
			interim = syst;

		rez += mass_number[i] * interim;//алгоритм перевода из любой системы счисления в 10

		power++;
	}

	//если флаг -1, тогда результат следует умножить на -1
	if (flag == -1)
		rez *= -1;

	printf("Число: %d", rez);
}