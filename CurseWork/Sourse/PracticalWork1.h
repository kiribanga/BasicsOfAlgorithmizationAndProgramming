#ifndef PRACTICALWORK1
#define PRACTICALWORK1
#include <iostream>
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

int practicalWork1();
#endif