#ifndef PRACTICALWORK3
#define PRACTICALWORK3
#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>

#define N 8 //размер матрицы
void printMatrix(int[N][N]); //метод, для печати матриц
void makeMatrixA(int[N][N], int*[N*N]); //методы для создания матриц
void makeMatrixB(int[N][N], int*[N*N]);
void changeMatrixA(int[N][N]); //методы для перестановки элементов матрицы
void changeMatrixB(int[N][N]);
void changeMatrixC(int[N][N]);
void changeMatrixD(int[N][N]);
void quicksort(int**, int, int); //сортировка матрицы из прошлой работы, работает через порядок создания
void userChangeMatrix(int[N][N]); //уведичение, уменьшение, умножение или деление матрицы на число пользователя

extern int maxValue; //число, для ровного вывода матрицы

int practicalWork3();
#endif