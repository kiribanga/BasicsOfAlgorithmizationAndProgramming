#ifndef PRACTICALWORK4
#define PRACTICALWORK4
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <chrono>

std::string makeSentence(int); //��������� ��������� �� ������ � ������ �� �� ��������� ������ �� �������� ������
void changeSentence(std::string*); //������� ������ �������, �������� � ������� ����� ���������� � ��������
void printNotNumberWord(std::string); //�������� ����� �� �����������, �� ���������� �����
void printDeathNote(std::string); //�������� �����������, �������� �� ����� ����� ��������� ��������
void userFindWord(std::string); //����� ��������� ������������
int practicalWork4(); 
#endif