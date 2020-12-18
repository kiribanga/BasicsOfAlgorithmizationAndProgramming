#ifndef PRACTICALWORK3
#define PRACTICALWORK3
#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>

#define N 8 //������ �������
void printMatrix(int[N][N]); //�����, ��� ������ ������
void makeMatrixA(int[N][N], int*[N*N]); //������ ��� �������� ������
void makeMatrixB(int[N][N], int*[N*N]);
void changeMatrixA(int[N][N]); //������ ��� ������������ ��������� �������
void changeMatrixB(int[N][N]);
void changeMatrixC(int[N][N]);
void changeMatrixD(int[N][N]);
void quicksort(int**, int, int); //���������� ������� �� ������� ������, �������� ����� ������� ��������
void userChangeMatrix(int[N][N]); //����������, ����������, ��������� ��� ������� ������� �� ����� ������������

extern int maxValue; //�����, ��� ������� ������ �������

int practicalWork3();
#endif