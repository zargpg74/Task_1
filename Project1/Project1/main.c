#include<stdio.h>
#include<locale.h>
#include<Windows.h>

#include"number.h"

void main()
{
	system("cls");
	setlocale(0, "ru");
	
	printf("�������� ������� ��������:\n1) �� ������ � �����\n2) �� ����� � ������\n��� �������: ");
	int choice;
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
		str_number();
		break;
	default:
		printf("������ �������� �� ����������");
		exit(choice);
	}


}