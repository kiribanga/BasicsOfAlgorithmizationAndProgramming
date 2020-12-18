#include <iostream>
#include "PracticalWork1.h"
#include "PracticalWork2.h"
#include "PracticalWork3.h"
#include "PracticalWork4.h"


int main()
{
	setlocale(LC_ALL, "Russian"); //для корректного вывода руских букв;
	std::cout << "Запущена курсовая работа Кольцова Кирилла\n";
	bool curseWorkWork = true;
	char curseWorkAnswer;
	while (curseWorkWork) {
		std::cout << "Для перехода к нужной работе введите ее номер\n" \
			"Для завершения введите q\n";
		std::cin >> curseWorkAnswer;
		switch (curseWorkAnswer)
		{
		case '1':
			std::cin.ignore(INT_MAX, '\n');
			system("cls");
			practicalWork1();
			system("cls");
			std::cout << "Запущена курсовая работа Кольцова Кирилла\n";
			break;
		case '2':
			std::cin.ignore(INT_MAX, '\n');
			system("cls");
			practicalWork2();
			system("cls");
			std::cout << "Запущена курсовая работа Кольцова Кирилла\n";
			break;
		case '3':
			std::cin.ignore(INT_MAX, '\n');
			system("cls");
			practicalWork3();
			system("cls");
			std::cout << "Запущена курсовая работа Кольцова Кирилла\n";
			break;
		case '4':
			std::cin.ignore(INT_MAX, '\n');
			system("cls");
			practicalWork4();
			system("cls");
			std::cout << "Запущена курсовая работа Кольцова Кирилла\n";
			break;
		case 'q':
			curseWorkWork = false;
			break;
		default:
			std::cout << "Вы указали несуществующую команду\n";
			break;
		}
	}
	system("pause");
	return 0;
}