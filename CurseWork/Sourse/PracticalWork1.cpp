﻿#include <iostream>
#include <typeinfo> //нужен для получения имени типа данных в форме строки

/*
Первая функция нужна для вывода на консоль строки с размером соответствующего типа,
перегрузка используется для вывода размеров заданных в задании типов
и нужна для малого количества строк в main
*/
template <typename T> void printMemorySize();
void printMemorySize();

//Функция принимает переменную целого, вещественного одинарной или двойной точности
void printMemoryShowing(double);
void printMemoryShowing(float);
void printMemoryShowing(int);

int practicalWork1()
{
	int userNumberI;
	float userNumberF;
	double userNumberD;
	setlocale(LC_ALL, "Russian"); //Коректный вывод кириллицы

	printMemorySize(); //пункт 1 задания

	//пункт 2 задания, для быстрой сборки числа считываются клавиатуры
	std::cout << "\nВведите целое число\n";
	while (true) {
		std::cin >> userNumberI;
		if (std::cin)
			break;
		std::cout << "Вы неправильно ввели число. Повторите ввод\n";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	
	printMemoryShowing(userNumberI);

	//пункт 3 задания, для быстрой сборки числа считываются клавиатуры
	std::cout << "\nВведите вещественное число типа float\n";
	while (true) {
		std::cin >> userNumberF;
		if (std::cin)
			break;
		std::cout << "Вы неправильно ввели число. Повторите ввод\n";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	printMemoryShowing(userNumberF);

	//пункт 4 задания, для быстрой сборки числа считываются клавиатуры
	std::cout << "\nВведите вещественное число типа double\n";
	while (true) {
		std::cin >> userNumberD;
		if (std::cin)
			break;
		std::cout << "Вы неправильно ввели число. Повторите ввод\n";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	printMemoryShowing(userNumberD);

	system("pause");
	return 0;
}

void printMemorySize()
{
	//Вывод размера заданных типов
	printMemorySize<int>();
	printMemorySize<short int>();
	printMemorySize<long int>();
	printMemorySize<float>();
	printMemorySize<double>();
	printMemorySize<long double>();
	printMemorySize<char>();
	printMemorySize<bool>();
}

template<typename T>
void printMemorySize()
{
	/*
	У базовых типов есть имена, что позволяет вместо большого числа перегрузок/новых функций использовать шаблон,
	ведь имея тип данных можно получить его имя в виде строки
	*/
	T t;
	switch (sizeof(T) % 10)
	{
	case 2:
	case 3:
	case 4:
		std::cout << "Размер " << typeid(t).name() << " = " << sizeof(T) << " байта\n";
		break;
	default:
		std::cout << "Размер " << typeid(t).name() << " = " << sizeof(T) << " байт\n";
	}
}

void printMemoryShowing(int value)
{
	/*
	Самый простой тип для представления памяти, ведь побитовое И принимает только целые типы данных
	Для вывода представления в памяти будет использована маска в виде числа с только одной единицей в двоичном представлении (числа типа 2^N)
	Читаем мы начиная со старшего разряда, а точнее со знакового, для сравнения с ним можно использовать максимальное положительное 2^31
	Дальше в цикле это число побитого умножается на маску (проверяем есть ли единица в соответствующем разряде),
	выводим 1 или 0 соответствено, и сдвигаем маску вправо (делим на два)
	Отдельно нужно выставить пробели после знакового бита, для этого в цикле есть if
	*/
	unsigned int mask = 2147483648;
	for (int i = 0;i < 32;i++)
	{
		std::cout << (value & mask ? '1' : '0');
		mask >>= 1;
		if (i == 0)
			std::cout << ' ';
	}
	std::cout << '\n';
}

void printMemoryShowing(float value)
{
	/*
	Вывести представление float в памяти просто не получится, для него через конструкцию union получим целое представление нужного участка памяти
	Для вывода представления в памяти будет использована маска в виде числа с только одной единицей в двоичном представлении (числа типа 2^N)
	Читаем мы начиная со старшего разряда, а точнее со знакового, для сравнения с ним можно использовать максимальное положительное 2^31
	Дальше в цикле это число побитого умножается на маску (проверяем есть ли единица в соответствующем разряде),
	выводим 1 или 0 соответствено, и сдвигаем маску вправо (делим на два)
	Отдельно нужно выставить пробели после знакового бита и разделить между собой порядок и мантиссу, для этого в цикле есть if
	*/
	union {
		float valueF;
		int valueI;
	};
	valueF = value;
	unsigned int mask = 2147483648;
	for (int i = 0;i < 32;i++)
	{
		std::cout << (valueI & mask ? '1' : '0');
		mask >>= 1;
		if ((i == 0) || (i == 8))
			std::cout << ' ';
	}
	std::cout << '\n';
}

void printMemoryShowing(double value)
{
	/*
	Вывести представление double можно также как и float, только следует использовать число такого же размера (в памяти) - long long (8 байт)
	Для вывода представления в памяти будет использована маска в виде числа с только одной единицей в двоичном представлении (числа типа 2^N)
	Читаем мы начиная со старшего разряда, а точнее со знакового, для сравнения с ним можно использовать максимальное положительное 2^63
	Дальше в цикле это число побитого умножается на маску (проверяем есть ли единица в соответствующем разряде),
	выводим 1 или 0 соответствено, и сдвигаем маску вправо (делим на два)
	Отдельно нужно выставить пробели после знакового бита и разделить между собой порядок и мантиссу, для этого в цикле есть if
	*/
	union {
		double valueD;
		long long valueLL;
	};
	valueD = value;
	unsigned long long mask = 9223372036854775808;
	for (int i = 0;i < 64;i++)
	{
		std::cout << (valueLL & mask ? '1' : '0');
		mask >>= 1;
		if ((i == 0) || (i == 11))
			std::cout << ' ';
	}
	std::cout << '\n';
}