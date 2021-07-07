#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<Windows.h>

#include"number.h"

int* trans_number(char* str, int size)//������� ������ � ������ �����
{
	//������� ����������� ��� ������� ������ ���������
	char* low = "abcdefghijklmnopqrstuvwxyz";
	char* big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int* number_low[26] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
	int* number_big[26] = {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61};

	int* mass_number = (int*)malloc(size * sizeof(int));//������ ����� ����� ��������


	for (int i = 0; i < size; i++)
	{
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


int POW(num, power)//���������� � �������
{
	int rezult = 1;
	for (int i = 0; i < power; i++)
		rezult *= num;

	return(rezult);
}


int Error_input(char* str, int size, int syst)//������� ��������� ������ ����� ������
{
	//�������� ������� ���������
	if ((syst < 2) || (syst > 61))
	{
		system("cls");
		printf("������� �������� ������� ��������� %d", syst);
		exit(syst);
	}

	//�������� �� ����������� ������� ���������
	int* number = (int*)malloc(size * sizeof(int));
	number = trans_number(str, size);
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (number[i] > max)
			max = number[i];
	}
	if (max + 1 > syst)
	{
		system("cls");
		printf("��������� ������ �� ������������� ������� ���������");
		exit(syst);
	}

	//�������� �� ����������� ������� � ������
	for (int i = 0; i < size; i++)
	{
		if ((number[i] >= 0) && (number[i] <= 61))
			max = 1;
		else
		{
			system("cls");
			printf("������� ������������ ������");
			exit(number[i]);
		}
	}
}


int notation(char*str, int size, int syst)
{
	int* number = (int*)malloc(size * sizeof(int));
	number = trans_number(str, size);
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (number[i] > max)
			max = number[i];
	}
	syst = max + 1;

	return(syst);
}


int str_number()//������->�����
{
	system("cls");
	
	printf("������� ������� ���������: ");
	int syst;
	scanf_s("%d", &syst);

	//���� ������
	printf("������� ������: ");
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

	if (syst == 0)
		syst = notation(str, size, syst);
	Error_input(str, size, syst);

	//�������� ��������������� ������ �����
	int* mass_number = (int*)malloc(size * sizeof(int));
	mass_number = trans_number(str, size);

	//��������� ������ ����� � ���������� ������� ��������� � ���������� � ���������
	int rez = 0, power = 0;
	for (int i = size - 1; i >= 0; i--)
	{
		int interim;
		if (power > 1)
			interim = POW(syst, power);
		else if (power == 0)
			interim = 1;
		else if (power == 1)
			interim = syst;

		rez += mass_number[i] * interim;

		power += 1;
	}

	printf("�����: %d", rez);
}