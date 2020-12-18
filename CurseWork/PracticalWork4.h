#ifndef PRACTICALWORK4
#define PRACTICALWORK4
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <chrono>

std::string makeSentence(int); //принимает указатель на строку и меняет ее на случайную строку по условиям работы
void changeSentence(std::string*); //удаляет лишние пробелы, приводит в порядок знаки препинания и регистры
void printNotNumberWord(std::string); //печатает слова из предложения, не содержащие цифры
void printDeathNote(std::string); //печатает предложение, исключая из слова набор случайных символов
void userFindWord(std::string); //поиск подстроки пользователя
int practicalWork4(); 
#endif