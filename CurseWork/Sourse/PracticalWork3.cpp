#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>

#define N 8 //размер матриц
void printMatrix(int [N][N]); //метод, для печати матриц
void makeMatrixA(int[N][N], int*[N*N]); //методы для создания матриц
void makeMatrixB(int[N][N], int*[N*N]);
void changeMatrixA(int[N][N]); //методы для перестановки элементов матрицы
void changeMatrixB(int[N][N]);
void changeMatrixC(int[N][N]);
void changeMatrixD(int[N][N]);
void quicksort(int**, int, int); //сортировка матрицы из прошлой работы, работает через порядок создания
void userChangeMatrix(int[N][N]); //уведичение, уменьшение, умножение или деление матрицы на число пользователя

int maxValue; //число, для ровного вывода матрицы

int practicalWork3()
{
	std::srand(time(0)); //чтобы матрицы каждый раз были случайными
	setlocale(LC_ALL, "Russian"); //для корректного вывода руских букв
	int *sort[N*N], mat[N][N]; //первый массив для хранения порядка создания, нужна для сортировки, второй - матрица
	char answer;
	bool flag = true;
	while (flag) {//цикл для первого создания матрицы
		std::cout << "Выберете вариант создания матрицы: a или b\n";
		std::cin >> answer;
		switch (answer)
		{
		case 'a':
			makeMatrixA(mat, sort);
			flag = false;
			break;
		case 'b':
			makeMatrixB(mat, sort);
			flag = false;
			break;
		default:
			std::cout << "Вы выбрали несуществующую схему\n";
			break;
		}
	}
	flag = true;
	char answer1; //для вложенных команд
	bool flag1;
	while (flag) {//цикл для приема команд от пользователя
		std::cout << "Введите команду для работы с массивом\n";
		std::cin >> answer;
		switch (answer)
		{
		case 'h':
			std::cout << "h: список команд\n" \
				"m: заново создать матрицу\n" \
				"c: увеличить, уменьшить, умножить или поделить матрицу на число\n" \
				"s: отсортировать матрицу, используя порядок создания\n" \
				"p: перестановка элементов\n" \
				"e: завершить работу программы\n";
			break;
		case 'm':
			flag1 = true;
			while (flag1) {//цикл для приема команд от пользователя
				std::cout << "Выберете вариант создания матрицы: a или b\n";
				std::cin >> answer1;
				switch (answer1)
				{
				case 'a':
					makeMatrixA(mat, sort);
					flag1 = false;
					break;
				case 'b':
					makeMatrixB(mat, sort);
					flag1 = false;
					break;
				default:
					std::cout << "Вы выбрали несуществующую схему\n";
					break;
				}
			}
			break;
		case 'c':
			userChangeMatrix(mat);
			break;
		case 's':
			quicksort(sort, 0, N*N - 1);
			printMatrix(mat);
			break;
		case 'p':
			flag1 = true;
			while (flag1) {//цикл для приема команд от пользователя
				std::cout << "Выберете перестановку из a,b,c или d\n";
				std::cin >> answer1;
				switch (answer1)
				{
				case 'a':
					changeMatrixA(mat);
					flag1 = false;
					break;
				case 'b':
					changeMatrixB(mat);
					flag1 = false;
					break;
				case 'c':
					changeMatrixC(mat);
					flag1 = false;
					break;
				case 'd':
					changeMatrixD(mat);
					flag1 = false;
					break;
				default:
					std::cout << "Вы выбрали несуществующую перестановку\n";
					break;
				}
			}
			break;
		case'e':
			flag = false;
			break;
		default:
			std::cout << "Вы указали несуществующую команду\n";
			break;
		}
	}



	system("pause");
	return 0;
}

//для ровных матриц используется максимальный элемент, так как в процессе программы матрица может меняться
void printMatrix(int mat[N][N]) {
	int p = maxValue, d = 0;
	while (p) {
		d++;
		p /= 10;
	}
	for (int *i = mat[0];i < (mat[0] + N * N);i += N) {
		for (int *j = i;j < (i + N);j++)
			std::cout << std::setw(d) << *j << ' ';
		std::cout << '\n';
	}
	std::cout << '\n';
}

/*
При создании матриц используются указатели, в случае A расстоновки нам нужны четыре индекса, указываюзие на углы заполняемой области
каждый шаг цикла эта область уменьшается с каждой стороны, в самом цикле идет 4 последловательных цикла по краям области
параллельно создается массив указателей на элементы массива, чтобы был порядок для сортировки
*/
void makeMatrixA(int mat[N][N], int *sort[N*N]) {
	maxValue = 0;
	for (int *i = mat[0];i < (mat[0] + N * N);i += N) {
		for (int *j = i;j < (i + N);j++)
			*j = 0;
	}
	printMatrix(mat);
	Sleep(250);
	int count = 0;
	for (int *i[4] = { mat[0], (mat[0] + N - 1), (mat[0] + N * N - 1), (mat[0] + N * (N - 1)) };i[0] < i[1];i[0] += N + 1, i[1] += N - 1, i[2] -= N + 1, i[3] -= N - 1) {
		for (int *j = i[0];j < i[1];j++) {
			*j = (std::rand() % (N*N)) + 1;
			if (*j > maxValue)
				maxValue = *j;
			sort[count++] = j;
			system("cls");
			printMatrix(mat);
			Sleep(250);
		}
		for (int *j = i[1];j < i[2];j += N) {
			*j = (std::rand() % (N*N)) + 1;
			if (*j > maxValue)
				maxValue = *j;
			sort[count++] = j;
			system("cls");
			printMatrix(mat);
			Sleep(250);
		}
		for (int *j = i[2];j > i[3];j--) {
			*j = (std::rand() % (N*N)) + 1;
			if (*j > maxValue)
				maxValue = *j;
			sort[count++] = j;
			system("cls");
			printMatrix(mat);
			Sleep(250);
		}
		for (int *j = i[3];j > i[0];j -= N) {
			*j = (std::rand() % (N*N)) + 1;
			if (*j > maxValue)
				maxValue = *j;
			sort[count++] = j;
			system("cls");
			printMatrix(mat);
			Sleep(250);
		}
	}
}

/*
При создании матриц используются указатели, в случае B расстоновки нам нужны два индекса, с первого мы идем вниз, со второго вверх
каждый шаг цикла мы сдвигаем область вправо, в самом цикле идет 2 последловательных цикла вниз, затем вверх
параллельно создается массив указателей на элементы массива, чтобы был порядок для сортировки
*/
void makeMatrixB(int mat[N][N], int *sort[N*N]) {
	maxValue = 0;
	for (int *i = mat[0];i < (mat[0] + N * N);i += N) {
		for (int *j = i;j < (i + N);j++)
			*j = 0;
	}
	printMatrix(mat);
	Sleep(250);
	int count = 0;
	for (int *i[2] = { mat[0],(mat[0] + N * (N - 1) + 1) };i[0] < mat[0] + N - 1;i[0] += 2, i[1] += 2) {
		for (int *j = i[0];j <= i[0] + N * (N - 1);j += N) {
			*j = (std::rand() % (N*N)) + 1;
			if (*j > maxValue)
				maxValue = *j;
			sort[count++] = j;
			system("cls");
			printMatrix(mat);
			Sleep(250);
		}
		for (int *j = i[1];j >= i[0] + 1;j -= N) {
			*j = (std::rand() % (N*N)) + 1;
			if (*j > maxValue)
				maxValue = *j;
			sort[count++] = j;
			system("cls");
			printMatrix(mat);
			Sleep(250);
		}
	}
}

//метод позволяет менять матрицу по квадратам 2 на 2 по часовой стрелке
void changeMatrixA(int mat[N][N]) {
	for (int *i = mat[0];i < mat[0] + N * N;i += 2 * N)
		for (int *j = i;j < i + N;j += 2) {
			std::swap(*j, *(j + 1));
			std::swap(*(j + N), *(j + N + 1));
			std::swap(*j, *(j + N + 1));
		}
	printMatrix(mat);
}

//метод позволяет менять матрицу по квадратам 2 на 2 крест на крест
void changeMatrixB(int mat[N][N]) {
	for (int *i = mat[0];i < mat[0] + N * N;i += 2 * N)
		for (int *j = i;j < i + N;j += 2) {
			std::swap(*(j + N + 1), *j);
			std::swap(*(j + N), *(j + 1));
		}
	printMatrix(mat);
}

//метод позволяет менять матрицу по квадратам 2 на 2 верхние с нижними
void changeMatrixC(int mat[N][N]) {
	for (int *i = mat[0];i < mat[0] + N * N;i += 2 * N)
		for (int *j = i;j < i + N;j += 2) {
			std::swap(*(j + N), *j);
			std::swap(*(j + 1), *(j + N + 1));
		}
	printMatrix(mat);
}

//метод позволяет менять матрицу по квадратам 2 на 2 правые с левыми
void changeMatrixD(int mat[N][N]) {
	for (int *i = mat[0];i < mat[0] + N * N;i += 2 * N)
		for (int *j = i;j < i + N;j += 2) {
			std::swap(*(j + 1), *j);
			std::swap(*(j + N), *(j + N + 1));
		}
	printMatrix(mat);
}

//быстрая сортировка, принимающая вместо обычного массива, массив указателей
void quicksort(int** arr, int  begin, int end)
{
	int f = begin, l = end, mid = *arr[(f + l) / 2];
	while (f <= l)
	{
		while (*arr[f] < mid) f++;
		while (*arr[l] > mid) l--;
		if (f <= l)
		{
			std::swap(*arr[f], *arr[l]);
			f++;
			l--;
		}
	}
	if (begin < l) quicksort(arr, begin, l);
	if (f < end) quicksort(arr, f, end);
}


//метод для изменения матрицы на число пользователя, также меняет максимальное число для корректного вывода матрицы
void userChangeMatrix(int mat[N][N]) {
	char answer;
	bool flag = true;
	int ab;
	while (flag) {//цикл для приема команд от пользователя
		std::cout << "Введите символ операции +,-,* или : для изменения матрицы\n";
		std::cin >> answer;
		switch (answer)
		{
		case '+':
			std::cout << "Введите число, на которое увеличить матрицу\n";
			while (true) {
				std::cin >> ab;
				if (std::cin)
					break;
				std::cout << "Вы неправильно ввели число. Повторите ввод\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			for (int* i = mat[0];i < mat[0] + N * N;i++)
				*i += ab;
			maxValue += ab;
			flag = false;
			break;
		case '-':
			std::cout << "Введите число, на которое уменьшить матрицу\n";
			while (true) {
				std::cin >> ab;
				if (std::cin)
					break;
				std::cout << "Вы неправильно ввели число. Повторите ввод\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			for (int* i = mat[0];i < mat[0] + N * N;i++)
				*i -= ab;
			maxValue -= ab;
			flag = false;
			break;
		case '*':
			std::cout << "Введите число, на которое умножить матрицу\n";
			while (true) {
				std::cin >> ab;
				if (std::cin)
					break;
				std::cout << "Вы неправильно ввели число. Повторите ввод\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			for (int* i = mat[0];i < mat[0] + N * N;i++)
				*i *= ab;
			maxValue *= ab;
			flag = false;
			break;
		case ':':
			std::cout << "Введите число, на которое поделить матрицу\n";
			while (true) {
				std::cin >> ab;
				if (std::cin)
					break;
				std::cout << "Вы неправильно ввели число. Повторите ввод\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			for (int* i = mat[0];i < mat[0] + N * N;i++)
				*i /= ab;
			maxValue /= ab;
			flag = false;
			break;
		default:
			std::cout << "Вы указали несуществующую команду";
			break;
		}
	}
	printMatrix(mat);
}
