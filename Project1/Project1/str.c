#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<Windows.h>

#include"str.h"


int Error_input_str(int syst)//�������� �� ������������ ��������� ������
{
	if ((syst < 2) || (syst > 61))
	{
		printf("������� �������� ������� ��������� %d", syst);
		exit(syst);
	}
}


int number_str()
{
	printf("������� ������� ���������: ");
	int syst;
	scanf_s("%d", &syst);

	printf("������� �����: ");
	int number;
	scanf_s("%d", &number);

	Error_input_str(syst);


}