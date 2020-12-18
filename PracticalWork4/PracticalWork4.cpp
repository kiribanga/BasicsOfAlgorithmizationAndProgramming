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

int main()
{
	setlocale(LC_ALL, "Russian"); //для корректного вывода руских букв;
	std::cout.setf(std::ios::fixed); //для кореектного вывода дробных чисел
	std::cout.precision(7); //только первые 7 знаков после запятой значащие для вывода временного интервала
	std::srand(time(0)); //для случайности генератора предложений и списка символов для Death Note
	std::string sentence; //рабочее предложение
	char answer, answer1; //для приема ответов пользователя
	bool flag = true, flag1;
	std::cout << "Введите команду для начала работы\n" \
		"f: чтение строки из файла\n" \
		"r: создание случайной строки\n" \
		"c: ввод строки с клавиатуры\n";
	std::ifstream in;
	while (flag) {//цикл для первого создания предложения
		std::cin >> answer;
		std::cin.ignore(INT_MAX, '\n');
		
		switch (answer)
		{
		case 'f':
			in.open("SimpleText.txt");
			if (in.is_open()) {
				std::getline(in, sentence);
				flag = false;
			}
			else
				std::cout << "Файл не доступен\n";
			in.close();
			break;
		case 'r':
			sentence = makeSentence(50);
			flag = false;
			break;
		case 'c':
			std::cout << "Вводите строку\n";
			std::getline(std::cin, sentence);
			flag = false;
			break;
		default:
			std::cout << "Вы выбрали несуществующую команду\n";
			break;
		}
	}
	std::cout << "Ваша строка:\n";
	std::cout << sentence << '\n';
	changeSentence(&sentence);
	std::cout << '\n' << sentence << '\n';
	printNotNumberWord(sentence);
	printDeathNote(sentence);
	userFindWord(sentence);

	flag = true;
	while (flag) {//цикл для приема команд от пользователя
		std::cout << "Введите команду для работы с массивом\n";
		std::cin >> answer;
		std::cin.ignore(INT_MAX, '\n');
		switch (answer)
		{
		case 'h':
			std::cout << "h: список команд\n" \
				"n: заново задать предложение\n" \
				"d: найти индексы среднего элемента\n" \
				"w: поменять местам пару элементов в массиве\n" \
				"e: завершить работу программы\n";
			break;
		case 'n':
			flag1 = true;
			std::cout << "Введите команду для начала работы\n" \
				"f: чтение строки из файла\n" \
				"r: создание случайной строки\n" \
				"c: ввод строки с клавиатуры\n";
			while (flag1) {//цикл для создания нового предложения
				std::cin >> answer1;
				std::cin.ignore(INT_MAX, '\n');

				switch (answer1)
				{
				case 'f':
					in.open("SimpleText.txt");
					if (in.is_open()) {
						std::getline(in, sentence);
						flag1 = false;
					}
					else
						std::cout << "Файл не доступен\n";
					in.close();
					break;
				case 'r':
					sentence = makeSentence(50);
					flag1 = false;
					break;
				case 'c':
					std::cout << "Вводите строку\n";
					std::getline(std::cin, sentence);
					flag1 = false;
					break;
				default:
					std::cout << "Вы выбрали несуществующую команду\n";
					break;
				}
			}
			std::cout << "Ваша строка:\n";
			std::cout << sentence << '\n';
			changeSentence(&sentence);
			std::cout << '\n' << sentence << '\n';
			printNotNumberWord(sentence);
			break;
		case 'd':
			printDeathNote(sentence);;
			break;
		case 'w':
			userFindWord(sentence);
			break;
		case 'e':
			flag=false;
			break;
		default:
			std::cout << "Вы указали несуществующую команду";
			break;
		}
	}
	system("pause");
	return 0;
}

/*
случайным образом выбирается размер предложения, затем создаются слова не более 10 символов
и между ними создается мешанина пробелов и знаков препинания, после последнего слова стоит одна точка
*/
std::string makeSentence(int N) {
	std::string sentence;
	int count = std::rand() % (N) + 1;
	for (int i = 0;i < count - 1;i++) {
		for (int j = std::rand() % 10 + 1;j > 0;j--) {
			int k = std::rand() % 62 + 48;
			if (k > 57)
				k += 7;
			if (k > 90)
				k += 6;
			sentence += (char)k;
		}
		for (int j = std::rand() % 7;j >= 0;j--) {
			int choice = std::rand() % 11;
			switch (choice)
			{
			case 0:
				sentence += ' ';
				break;
			case 1:
				sentence += "  ";
				break;
			case 2:
				sentence += "   ";
				break;
			case 3:
				sentence += '!';
				break;
			case 4:
				sentence += ',';
				break;
			case 5:
				sentence += '.';
				break;
			case 6:
				sentence += ':';
				break;
			case 7:
				sentence += ';';
				break;
			case 8:
				sentence += '?';
				break;
			case 9:
				sentence += '...';
				break;
			case 10:
				sentence += '..';
				break;
			}
		}
		sentence += ' ';
	}
	for (int j = std::rand() % 10 + 1;j > 0;j--) {
		int k = std::rand() % 62 + 48;
		if (k > 57)
			k += 7;
		if (k > 90)
			k += 6;
		sentence += (char)k;
	}
	sentence += '.';
	return sentence;
}

/*
через указатели метод циклом проходит через предложение, в нем логика разделена на участи слова и участки между слов
при смене участка предыдущий обрабатывается: слова меняют регистр, знаки препинания удаляются до приемлемых сочетаний
*/
void changeSentence(std::string* sentence) {
	char *point = &sentence[0][0], *begin = point, *end = point;
	bool word = true, firstWord = true;
	while (*(point)) {
		if (word) {
			if (((*point >= 48) && (*point <= 57)) || ((*point >= 65) && (*point <= 90)) || ((*point >= 97) && (*point <= 122))) {
				end = point;
			}
			else {
				word = false;
				bool caps = true;
				for (char *marker = begin;marker <= end;marker++) {
					if (caps) {
						if (*marker >= 97) {
							caps = false;
							marker = begin - 1;
						}
					}
					else {
						if ((*marker >= 65) && (*marker <= 90))
							*marker += 32;
					}
				}
				if (firstWord) {
					firstWord = false;
					if (*begin >= 97)
						*begin -= 32;
				}
				begin = end = point;
			}
		}
		else {
			if (((*point >= 48) && (*point <= 57)) || ((*point >= 65) && (*point <= 90)) || ((*point >= 97) && (*point <= 122))) {
				word = true;
				for (char *marker = begin;marker <= end;marker++) {
					switch (*marker)
					{
					case ' ':
						if (!(((*(marker + 1) >= 48) && (*(marker + 1) <= 57)) || ((*(marker + 1) >= 65) && (*(marker + 1) <= 90)) || ((*(marker + 1) >= 97) && (*(marker + 1) <= 122)))) {
							sentence[0].erase(marker - &sentence[0][0], 1);
							end--;
							point--;
							marker--;
						}
						break;
					case '?':
						if (marker != begin) {
							sentence[0].erase(marker - &sentence[0][0], 1);
							end--;
							point--;
							marker--;
						}
						else
							firstWord = true;
						break;
					case '!':
						if (!((marker == begin) || ((*begin == '?') && (marker == begin + 1)))) {
							sentence[0].erase(marker - &sentence[0][0], 1);
							end--;
							point--;
							marker--;
						}
						else
							firstWord = true;
						break;
					case ',':
						if (!(marker == begin) || ((marker == begin + 1) && (*begin == '.'))) {
							sentence[0].erase(marker - &sentence[0][0], 1);
							end--;
							point--;
							marker--;
							if (*begin == '.')
								firstWord = false;
						}
						break;
					case '.':
						if (!((*begin == '.') && ((marker == begin) || ((marker == begin + 1) && (*(marker + 1) == '.')) || ((marker == begin + 2) && (*(marker - 1) == '.'))))) {
							sentence[0].erase(marker - &sentence[0][0], 1);
							end--;
							point--;
							marker--;
						}
						else
							firstWord = true;
						break;
					case ';':
					case ':':
						if (marker != begin) {
							sentence[0].erase(marker - &sentence[0][0], 1);
							end--;
							point--;
							marker--;
						}
						break;
					}
				}
				begin = end = point;
			}
			else {
				end = point;
			}
		}
		point++;
	}
	if (word) {
		bool caps = true;
		for (char *marker = begin;marker <= end;marker++) {
			if (caps) {
				if (*marker >= 97) {
					caps = false;
					marker = begin - 1;
				}
			}
			else {
				if ((*marker >= 65) && (*marker <= 90))
					*marker += 32;
			}
		}
		if (firstWord) {
			firstWord = false;
			if (*begin >= 97)
				*begin -= 32;
		}
	}
	else {
		for (char *marker = begin;marker <= end;marker++) {
			switch (*marker)
			{
			case ' ':
				if (!(((*(marker + 1) >= 48) && (*(marker + 1) <= 57)) || ((*(marker + 1) >= 65) && (*(marker + 1) <= 90)) || ((*(marker + 1) >= 97) && (*(marker + 1) <= 122)))) {
					sentence[0].erase(marker - &sentence[0][0], 1);
					end--;
					marker--;
				}
				break;
			case '?':
				if (marker != begin) {
					sentence[0].erase(marker - &sentence[0][0], 1);
					end--;
					marker--;
				}
				else
					firstWord = true;
				break;
			case '!':
				if (!((marker == begin) || ((*begin == '?') && (marker == begin + 1)))) {
					sentence[0].erase(marker - &sentence[0][0], 1);
					end--;
					marker--;
				}
				else
					firstWord = true;
				break;
			case ',':
				if (!(marker == begin) || ((marker == begin + 1) && (*begin == '.'))) {
					sentence[0].erase(marker - &sentence[0][0], 1);
					end--;
					marker--;
					if (*begin == '.')
						firstWord = false;
				}
				break;
			case '.':
				if (!((*begin == '.') && ((marker == begin) || ((marker == begin + 1) && (*(marker + 1) == '.')) || ((marker == begin + 2) && (*(marker - 1) == '.'))))) {
					sentence[0].erase(marker - &sentence[0][0], 1);
					end--;
					marker--;
				}
				else
					firstWord = true;
				break;
			case ';':
			case ':':
				if (marker != begin) {
					sentence[0].erase(marker - &sentence[0][0], 1);
					end--;
					marker--;
				}
				break;
			}
		}
	}
}

//Вывод слов предложения без цифр
void printNotNumberWord(std::string sentence) {
	std::cout << "Слова, не содержащие цифр\n";
	char *point = &sentence[0], *begin = point, *end = point;
	bool word = true, wordPrint = true;
	while (*(point)) {
		if (word) {
			if (((*point >= 48) && (*point <= 57)) || ((*point >= 65) && (*point <= 90)) || ((*point >= 97) && (*point <= 122))) {
				end = point;
				if ((*point >= 48) && (*point <= 57))
					wordPrint = false;
			}
			else {
				word = false;
				if (wordPrint) {
					for (char *marker = begin;marker <= end;marker++)
						std::cout << *marker;
					std::cout << ' ';
				}
				wordPrint = false;
			}
		}
		else {
			if (((*point >= 48) && (*point <= 57)) || ((*point >= 65) && (*point <= 90)) || ((*point >= 97) && (*point <= 122))) {
				begin = end = point;
				word = true;
				if (!((*point >= 48) && (*point <= 57)))
					wordPrint = true;
			}
		}
		point++;
	}
	std::cout << '\n';
}

//создается случайный набор символо (буквы всегда идут парой строчная и прописная) и затем выводится предложение без этих символов
void printDeathNote(std::string sentence) {
	std::string deathNote;
	bool unique;
	char *begin = &deathNote[0], *end = &deathNote[0];
	std::cout << "Список рекомендуемых к удалению символов:\n";
	for (int j = 6;j > 0;j--) {
		unique = true;
		int k = std::rand() % 36 + 48;
		if (k > 57)
			k += 7;
		for (char *marker = begin;marker < end;marker++)
			if ((char)k == *marker)
				unique = false;
		if (unique) {
			if (k >= 65) {
				deathNote += (char)(k + 32);
				std::cout << *(end);
				end++;
			}
			deathNote += (char)k;
			std::cout << *(end) << ' ';
			end++;
		}
		else
			j++;
	}
	std::cout << '\n';

	char *point;
	point = &sentence[0];
	while (*point) {
		if (((*point >= 48) && (*point <= 57)) || ((*point >= 65) && (*point <= 90)) || ((*point >= 97) && (*point <= 122))) {
			unique = true;
			for (char *marker = begin;marker < end;marker++)
				if (*point == *marker)
					unique = false;
			if (unique)
				std::cout << *point;
		}
		else
			std::cout << *point;
		point++;
	}
	std::cout << '\n';
}

//метод считывает строку и ищет ее в строке простым прогоном и алгоритмом КМП
void userFindWord(std::string sentence) {
	std::cout << "Введите подстроку для поиска\n";
	std::string userWord;
	std::getline(std::cin, userWord);
	std::chrono::system_clock::time_point start, fin;
	std::chrono::duration<double> findTime;
	bool find = false;
	char *point = &sentence[0], *begin = &userWord[0], *end = &userWord[userWord.length() - 1];
	std::cout << "Поиск простым перебором ";
	start = std::chrono::system_clock::now();
	while (*(point + userWord.length())) {
		while (*begin == *point) {
			if (begin == end) {
				find = true;
				begin = &userWord[0];
				std::cout << "нашел ";
				for (char *marker = begin;marker <= end;marker++) {
					std::cout << *marker;
				}
				point = &sentence[sentence.length() - 1 - userWord.length()];
			}
			begin++;
			point++;
		}
		begin = &userWord[0];
		point++;
	}
	fin = std::chrono::system_clock::now();
	findTime = fin - start;
	if (!find)
		std::cout << "не дал результата";
	std::cout << " за " << findTime.count() << " сек.\n";


	find = false;
	std::vector<int> prefixFunxin(userWord.length());
	prefixFunxin[0] = 0;
	int k = 0;
	std::cout << "Поиск алгоритмом КМП ";
	start = std::chrono::system_clock::now();
	for (int i = 1;i < userWord.length();i++) {
		while ((k > 0) && (userWord[i] != userWord[k]))
			k = prefixFunxin[k - 1];
		if (userWord[i] == userWord[k])
			k++;
		prefixFunxin[i] = k;
	}
	k = 0;
	for (int i = 0;i < sentence.length();i++) {
		while ((k > 0) && (userWord[k] != sentence[i]))
			k = prefixFunxin[k - 1];
		if (userWord[k] == sentence[i])
			k++;
		if (k == userWord.length()) {
			find = true;
			std::cout << "нашел ";
			for (int j = i - k + 1;j <= i;j++)
				std::cout << sentence[j];
			i = sentence.length();
		}
	}
	fin = std::chrono::system_clock::now();
	findTime = fin - start;
	if (!find)
		std::cout << "не дал результата";
	std::cout << " за " << findTime.count() << " сек.\n";
	std::cout << '\n';
}