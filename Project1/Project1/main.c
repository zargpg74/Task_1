#include<stdio.h>
#include<locale.h>
#include<Windows.h>

#include"number.h"

void main()
{
	system("cls");
	setlocale(0, "ru");
	
	printf("Выберите вариант перевода:\n1) Из строки в число\n2) Из числа в строку\nВаш вариант: ");
	int choice;
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
		str_number();
		break;
	default:
		printf("Такого варианта не существует");
		exit(choice);
	}


}