#include<stdio.h>
#include<locale.h>
#include<Windows.h>

#include"number.h"
#include"str.h"


int Choice(int choice)
{
	switch (choice)
	{
	case 1:
		str_number();
		break;
	case 2:
		number_str();
		break;
	case 3:
		exit(0);
	default:
		printf("������ �������� �� ����������, ���������� ��� ���: ");
		scanf_s("%d", &choice);
		Choice(choice);
	}
}


void main()
{
	system("cls");
	setlocale(0, "ru");
	
	while (1)
	{
		printf("�������� ������� ��������:\n1) �� ������ � �����\n2) �� ����� � ������\n3) �����\n��� �������: ");
		int choice;
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			str_number();
			break;
		case 2:
			number_str();
			break;
		case 3:
			exit(0);
		default:
			printf("������ �������� �� ����������, ���������� ��� ���: ");
			scanf_s("%d", &choice);
			Choice(choice);
		}

		printf("\n---------------------------------\n");
	}

	system("pause");
}