#ifndef PRACTICALWORK1
#define PRACTICALWORK1
#include <iostream>
#include <typeinfo> //����� ��� ��������� ����� ���� ������ � ����� ������

/*
������ ������� ����� ��� ������ �� ������� ������ � �������� ���������������� ����,
���������� ������������ ��� ������ �������� �������� � ������� �����
� ����� ��� ������ ���������� ����� � main
*/
template <typename T> void printMemorySize();
void printMemorySize();

//������� ��������� ���������� ������, ������������� ��������� ��� ������� ��������
void printMemoryShowing(double);
void printMemoryShowing(float);
void printMemoryShowing(int);

int practicalWork1();
#endif