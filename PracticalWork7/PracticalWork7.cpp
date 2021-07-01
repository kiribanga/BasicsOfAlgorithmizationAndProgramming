#include <iostream>
#include <string>
double answer = 0;

struct Stack {
	char symbol;
	Stack* tail;
};

struct NumStack {
	double num;
	NumStack* tail;
};

Stack* newStack(char);
void pushStack(Stack**, char);
char popStack(Stack**);

NumStack* newStack(int);
void pushStack(NumStack**, int);
double popStack(NumStack**);

std::string toPostfix(std::string);
std::string truePostfix(std::string);

int main() {
	setlocale(LC_ALL, "Russian"); //для корректного вывода руских букв
	std::string str = "";
	char cha;
	do {
		std::cout << "Введите режим работы\n" \
			"p: проверка и расчет обратной польской нотации\n"\
			"n: проверка и расчет обычной записи\n"\
			"e: выход\n";
		std::cin >> cha;
		switch (cha)
		{
		case 'p':
			std::cin.ignore(INT_MAX, '\n');
			std::getline(std::cin, str);
			if (truePostfix(str) != "Invalid input")
				std::cout << answer << '\n';
			else
				std::cout << "ошибка в польской записи";
			break;
		case 'n':
			std::cin.ignore(INT_MAX, '\n');
			std::getline(std::cin, str);
			str = toPostfix(str);
			std::cout << str << '\n';
			if (truePostfix(str) != "Invalid input")
				std::cout << answer << '\n';
			else
				std::cout << "ошибка в польской записи";
			break;
		case 'e':
			str = "e";
			break;
		default:
			break;
		}
	} while ((cha != 'e') && (str[0] != 'e'));
	system("pause");
}

Stack* newStack(char data) {
	return new Stack{ data, NULL };
}

void pushStack(Stack** sta, char data) {
	if (*sta == NULL)
		*sta = newStack(data);
	else
		*sta = new Stack{ data, *sta };
}

char popStack(Stack** sta) {
	char num = (*sta)->symbol;
	Stack* del = *sta;
	*sta = (*sta)->tail;
	delete del;
	return num;
}

NumStack* newStack(double data) {
	return new NumStack{ data, NULL };
}

void pushStack(NumStack** sta, double data) {
	if (*sta == NULL)
		*sta = newStack(data);
	else
		*sta = new NumStack{ data, *sta };
}

double popStack(NumStack** sta) {
	double num = (*sta)->num;
	NumStack* del = *sta;
	*sta = (*sta)->tail;
	delete del;
	return num;
}

std::string toPostfix(std::string str) {
	std::string postfix = "";
	char* point = &str[0];
	Stack* sta = NULL;
	bool lastNum = false, lastBracket = false, lastSymbol = false;
	while (*point != 0) {
		switch (*point)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (lastNum)
				return "Invalid input";
			if (lastBracket) {
				while ((sta != NULL) && (sta->symbol != '(') && (sta->symbol != '-') && (sta->symbol != '+')) {
					postfix += ' ';
					postfix += popStack(&sta);
				}
				pushStack(&sta, '*');
			}
			if ((postfix != "") && (postfix != "-"))
				postfix += " ";
			postfix += *point;
			while ((*(point + 1) > '0') && (*(point + 1) < '9')) {
				point++;
				postfix += *point;
			}
			lastNum = true;
			lastBracket = false;
			lastSymbol = false;
			break;
		case '+':
			if (postfix == "")
				return "Invalid input";
		case '-':
			if (lastSymbol)
				return "Invalid input";
			if (postfix == "")
				postfix = "-";
			else {
				while ((sta != NULL) && (sta->symbol != '(')) {
					postfix += ' ';
					postfix += popStack(&sta);
				}
				pushStack(&sta, *point);
			}
			lastNum = false;
			lastBracket = false;
			lastSymbol = true;
			break;
		case '*':
		case '/':
			if (lastSymbol)
				return "Invalid input";
			if (postfix == "")
				return "Invalid input";
			else {
				while ((sta != NULL) && (sta->symbol != '(') && (sta->symbol != '-') && (sta->symbol != '+')) {
					postfix += ' ';
					postfix += popStack(&sta);
				}
				pushStack(&sta, *point);
			}
			lastNum = false;
			lastBracket = false;
			lastSymbol = true;
			break;
		case '(':
			if (lastNum || lastBracket) {
				while ((sta != NULL) && (sta->symbol != '(') && (sta->symbol != '-') && (sta->symbol != '+')) {
					postfix += ' ';
					postfix += popStack(&sta);
				}
				pushStack(&sta, '*');
			}
			pushStack(&sta, *point);
			lastNum = false;
			lastBracket = false;
			lastSymbol = false;
			break;
		case ')':
			if (lastSymbol)
				return "Invalid input";
			if (sta->symbol == '(')
				return "Invalid input";
			while (sta->symbol != '(') {
				postfix += ' ';
				postfix += popStack(&sta);
				if (sta == NULL) {
					std::cout << postfix << "\n";
					return "Invalid input";
				}
			}
			popStack(&sta);
			lastNum = false;
			lastBracket = true;
			lastSymbol = false;
			break;
		case ' ':
			break;
		default:
			return "Invalid input";
		}
		point++;
	}
	while (sta != NULL) {
		postfix += ' ';
		postfix += popStack(&sta);
	}
	return postfix;
}

std::string truePostfix(std::string postfix) {
	NumStack* numbers = NULL;
	char* point = &postfix[0];
	double num, a, b;
	bool minus;
	while (*point != 0) {
		switch (*point)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			num = *point - '0';
			minus = false;
			if ((point - &postfix[0] == 1) && (postfix[0] == '-'))
				minus = true;
			while ((*(point + 1) > '0') && (*(point + 1) < '9')) {
				point++;
				num = 10 * num + *point - '0';
			}
			if (minus)
				num = -num;
			pushStack(&numbers, num);
			break;
		case '+':
			if ((numbers != NULL) && (numbers->tail != NULL)) {
				b = popStack(&numbers);
				a = popStack(&numbers);
				pushStack(&numbers, a + b);
			}
			else
				return "Invalid input";
			break;
		case '-':
			if ((numbers != NULL) && (numbers->tail != NULL)) {
				b = popStack(&numbers);
				a = popStack(&numbers);
				pushStack(&numbers, a - b);
			}
			else
				return "Invalid input";
			break;
		case '*':
			if ((numbers != NULL) && (numbers->tail != NULL)) {
				b = popStack(&numbers);
				a = popStack(&numbers);
				pushStack(&numbers, a * b);
			}
			else
				return "Invalid input";
			break;
		case '/':
			if ((numbers != NULL) && (numbers->tail != NULL)) {
				b = popStack(&numbers);
				a = popStack(&numbers);
				if (b == 0)
					return "Invalid input";
				pushStack(&numbers, a / b);
			}
			else
				return "Invalid input";
			break;
		case ' ':
			break;
		default:
			return "Invalid input";
		}
		point++;
	}
	if (numbers == NULL)
		return "Invalid input";
	else {
		if (numbers->tail != NULL)
			return "Invalid input";
		answer = popStack(&numbers);
		return "";
	}
}