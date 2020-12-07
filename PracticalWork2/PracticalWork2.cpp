#include <iostream>
#include <ctime>
#include <chrono>

#define N 100 //по сути переменная, позволяющая одной строкой управлять размером массива
bool wasArrSort; /*нужна, чтобы знать, отсортирован ли массив arrSort, если пользователь перестановкой изменил его,
				 то перед большинством функций ему предложат пересортировать массив, иначе функция не выплнится*/

void newArr(int*, int*); //создание массивов, повторный вызов пересоздаст массивы
void quicksort(int*, int, int); //сортировка, использующая опорное число
int findElem(int*, int, int, int); //выдает индекс элемента, если он есть в массиве, и -1, если такого элемента нет
int simpFindElem(int*, int, int, int); //делает тоже самое, но простым перебором, а не бинарным поиском
void findAllMed(int*, int, int); //находит все элементы, равные половине суммы максимального и минимального элементов
double findPlace(int*, int, int, int); //находит позицию элемента, если элемента нет, выдает позицию между которых он бы был
void userFindLess(int*); //пользователь вводит элемент, после чего выводится кол-во элементов меньше этого числа
void userFindMore(int*); //пользователь вводит элемент, после чего выводится кол-во элементов больше этого числа
void userSwap(int*); //пользователь вводит пару индексов, после чего в отсортированном массиве соответсвующие элементы меняются местами
void userFindNumber(int*); //пользователь вводит число, после чего находится соответствующий элемент бинарным поиском и простым перебором


int main()
{
	std::cout.setf(std::ios::fixed); //для кореектного вывода дробных чисел
	std::cout.precision(7); //только первые 7 знаков после запятой значащие для вывода временного интервала
	std::srand(time(0)); //для новых значений каждый раз
	setlocale(LC_ALL, "Russian"); //для корректного вывода текста
	int arrUnsort[N], arrSort[N]; 
	newArr(arrUnsort, arrSort); //создание и сортировка массива
	char answer;
	bool flag = true;
	while (flag) {//цикл для приема команд от пользователя
		std::cout << "Введите команду для работы с массивом\n";
		std::cin >> answer;
		switch (answer)
		{
		case 'h':
			std::cout << "h: список команд\n" \
				"s: заново создать массив\n" \
				"b: найти все элементы больше вашего числа\n" \
				"l: найти все элементы меньше вашего числа\n" \
				"m: найти индексы среднего элемента\n" \
				"w: поменять местам пару элементов в массиве\n" \
				"f: найти индекс элемента, равного вашему числу\n" \
				"e: завершить работу программы";
			break;
		case 's':
			newArr(arrUnsort, arrSort);
			break;
		case 'b':
			userFindMore(arrSort);
			break;
		case 'l':
			userFindLess(arrSort);
			break;
		case 'm':
			findAllMed(arrSort, 0, N - 1);
			break;
		case 'w':
			userSwap(arrSort);
			break;
		case 'f':
			userFindNumber(arrSort);
			break;
		case'e':
			flag = false;
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
для замера времени используются временные точки, и затем считается разница
функция берет два массива размером N, для заполнения случайными числами, затем второй сортируется
также вычисляются максимальный и минимальный элементы
*/
void newArr(int* arrUnsort, int* arrSort) {
	std::chrono::system_clock::time_point start, end;
	std::chrono::duration<double> sortTime, findTime;
	int min, max;
	std::cout << "Несортированный массив: ";
	for (int i = 0; i < N; i++)
	{
		arrUnsort[i] = (std::rand() % 199) - 99;
		arrSort[i] = arrUnsort[i];
		std::cout << arrUnsort[i] << " ";
	}
	wasArrSort = false;
	std::cout << "\n\n";
	start = std::chrono::system_clock::now();
	quicksort(arrSort, 0, N - 1);
	end = std::chrono::system_clock::now();
	sortTime = end - start;
	wasArrSort = true;
	std::cout << "Отсортированный массив: ";
	for (int i = 0; i < N; i++)
		std::cout << arrSort[i] << ' ';
	std::cout << "\n\n";
	std::cout << "Сортировка заняла " << sortTime.count() << " сек.\n\n";
	start = std::chrono::system_clock::now();
	min = max = arrUnsort[0];
	for (int i = 1;i < N;i++) {
		if (arrUnsort[i] > max)
			max = arrUnsort[i];
		else if (arrUnsort[i] < min)
			min = arrUnsort[i];
	}
	end = std::chrono::system_clock::now();
	std::cout << "Минимальный элемент = " << min << ", максимальный элемент = " << max << '\n';
	findTime = end - start;
	std::cout << "Поиск в неотсортированном массиве занял " << findTime.count() << " сек.\n";
	start = std::chrono::system_clock::now();
	min = arrSort[0];
	max = arrSort[N - 1];
	end = std::chrono::system_clock::now();
	findTime = end - start;
	std::cout << "Поиск в отсортированном массиве занял " << findTime.count() << " сек.\n";
	std::cout << "Сортировка и поиск в массиве заняли " << (findTime + sortTime).count() << " сек.\n\n";
}

/*
вся сортировка заключается в разделении массива на две части: больше и меньше определенного, опорного числа
для простосты и скородействия опорным числом выбирается число из середины массива
далее с двух сторон массив просматривается на наличие элементов, не в своей половине
(элементы больше опорного числа в левой части и элементы меньше опорного в правой части)
и попарно меняются местами, алгоритм заканчивается, когда оба индекса сойдутся на опорном числе,
если дошел только один, с несоответсвием начинает менятся опорное число
например {^9,1,2,4,3,3^,8}->{3,1,2,^4,3^,9,8}->{3,1,2,3,^4^,9,8}
после встречи на опорном числе/числах алгоритм повторяется отдельно для правой и левой частей
*/
void quicksort(int* arr, int  begin, int end)
{
	int f = begin, l = end, mid = arr[(f + l) / 2];
	while (f <= l)
	{
		while (arr[f] < mid) f++;
		while (arr[l] > mid) l--;
		if (f <= l)
		{
			std::swap(arr[f], arr[l]);
			f++;
			l--;
		}
	}
	if (begin < l) quicksort(arr, begin, l);
	if (f < end) quicksort(arr, f, end);
}

/*
функция ищет средний элемент, затем если их несколько находит индекс самого левого
и выводит на экран количество и индексы таких элементов
*/
void findAllMed(int* arr, int begin, int end) {
	if (!wasArrSort) {
		std::cout << "Для выполнения операции, нужно отсортировать массив\n";
		wasArrSort = true;
		std::cout << "Отсортированный массив: ";
		for (int i = 0; i < N; i++)
			std::cout << arr[i] << ' ';
		std::cout << "\n\n";
	}
	int med = (arr[begin] + arr[end]) / 2;
	std::cout << "Среднее значение = " << med << '\n';
	int sum = 0, count = findElem(arr, begin, end, med);
	if (count == -1) {
		std::cout << "Средний элемент = " << med << " в массиве не найден\n\n";
	}
	else {
		while (arr[count] == med)
			count--;
		count++;
		std::cout << "Средний элемент = " << med << " и находится по индексу ";
		while (arr[count] == med) {
			std::cout << count << ", ";
			count++;
			sum++;
		}
		std::cout << "и всего их " << sum << "\n\n";
	}
}

//находит элемент простым перебором, но сначала проверяет, входит ли оно в пределы массива
int simpFindElem(int* arr, int begin, int end, int elem) {
	if (!wasArrSort) {
		std::cout << "Для выполнения операции, нужно отсортировать массив\n";
		wasArrSort = true;
		std::cout << "Отсортированный массив: ";
		for (int i = 0; i < N; i++)
			std::cout << arr[i] << ' ';
		std::cout << "\n\n";
	}
	if ((elem < arr[begin]) || (elem > arr[end]))
		return -1;

	for (int i = begin;i <= end;i++)
		if (arr[i] == elem)
			return i;
	return -1;
}

/*
функция ищет элемент, выдает -1 если его нет или если он не входит в пределы массива
если входит, то индекс находится с помощью другой функции findPlace
*/
int findElem(int* arr, int begin, int end, int elem) {
	if (!wasArrSort) {
		std::cout << "Для выполнения операции, нужно отсортировать массив\n";
		wasArrSort = true;
		std::cout << "Отсортированный массив: ";
		for (int i = 0; i < N; i++)
			std::cout << arr[i] << ' ';
		std::cout << "\n\n";
	}
	if ((elem < arr[begin]) || (elem > arr[end]))
		return -1;
	double count = findPlace(arr, begin, end, elem);
	if (((int)count) == ((int)(count + 0.5)))
		return (int)count;
	return -1;
}

/*
функция использует бинарный поиск для нахождения индека числа, входящего в диапозон массива
дробная функция для того, чтобы при отсутствии числа в массиве выдать индекс между ближайшими к нему элементами
*/
double findPlace(int* arr, int begin, int end, int elem) {
	if ((end - begin) < 2) {
		if (elem == arr[end])
			return end;
		if (elem == arr[begin])
			return begin;
		return (double)(end + begin) / 2;
	}
	else{
		int count = (begin + end) / 2;
		if (elem > arr[count])
			return findPlace(arr, count, end, elem);
		return findPlace(arr, begin, count, elem);
	}
}

/*
функция ищет кол-во элементов, меньше заданного. для этого ищется индекс,
и если такое число есть, берем самое левое, если нет числа, берем большее ближайшее правое
все числа левее полученого индекса меньше нашего
*/
void userFindLess(int* arr) {
	if (!wasArrSort) {
		std::cout << "Для выполнения операции, нужно отсортировать массив\n";
		wasArrSort = true;
		std::cout << "Отсортированный массив: ";
		for (int i = 0; i < N; i++)
			std::cout << arr[i] << ' ';
		std::cout << "\n\n";
	}
	int ab;
	double placeAB;
	std::cout << "Введите число a, чтобы узнать, сколько чисел меньше него\n";
	while (true) {
		std::cin >> ab;
		if (std::cin)
			break;
		std::cout << "Вы неправильно ввели число. Повторите ввод\n";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	if (ab < arr[0])
		std::cout << "0 элементов меньше чем " << ab << "\n\n";
	else {
		int count;
		if (ab > arr[N - 1])
			std::cout << "100 элементов меньше чем " << ab << "\n\n";
		else {
			double countD = findPlace(arr, 0, N - 1, ab);
			if (((int)countD) == ((int)(countD + 0.5)))
				count = (int)countD;
			else
				count = (int)(countD - 0.5);
			while (arr[count] == ab)
				count--;
			std::cout << count + 1<< " элементов меньше чем " << ab << "\n\n";
		}
	}
}

/*
функция ищет кол-во элементов, больше заданного. для этого ищется индекс,
и если такое число есть, берем самое правое, если нет числа, берем большее ближайшее левое
все числа правее полученого индекса больше нашего
*/
void userFindMore(int* arr) {
	if (!wasArrSort) {
		std::cout << "Для выполнения операции, нужно отсортировать массив\n";
		wasArrSort = true;
		std::cout << "Отсортированный массив: ";
		for (int i = 0; i < N; i++)
			std::cout << arr[i] << ' ';
		std::cout << "\n\n";
	}
	int ab;
	double placeAB;
	std::cout << "Введите число b, чтобы узнать, сколько чисел больше него\n";
	while (true) {
		std::cin >> ab;
		if (std::cin)
			break;
		std::cout << "Вы неправильно ввели число. Повторите ввод\n";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	if (ab > arr[N - 1])
		std::cout << "0 элементов больше чем " << ab << "\n\n";
	else {
		int count;
		if (ab < arr[0])
			std::cout << "100 элементов больше чем " << ab << "\n\n";
		else {
			double countD = findPlace(arr, 0, N - 1, ab);
			if (((int)countD) == ((int)(countD + 0.5)))
				count = (int)countD;
			else
				count = (int)(countD + 0.5);
			while (arr[count] == ab)
				count++;
			std::cout << N - count << " элементов больше чем " << ab << "\n\n";
		}
	}
}

//функция ищет нужное число бинарным поиском и простым перебором
void userFindNumber(int* arr) {
	if (!wasArrSort) {
		std::cout << "Для выполнения операции, нужно отсортировать массив\n";
		wasArrSort = true;
		std::cout << "Отсортированный массив: ";
		for (int i = 0; i < N; i++)
			std::cout << arr[i] << ' ';
		std::cout << "\n\n";
	}
	int a;
	std::chrono::system_clock::time_point start, end;
	std::chrono::duration<double> binFindTime, simpFindTime;
	std::cout << "Введите число, которое нужно найти в массиве\n";
	while (true) {
		std::cin >> a;
		if (std::cin)
			break;
		std::cout << "Вы неправильно ввели число. Повторите ввод\n";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	int countBin, countSimp;
	start = std::chrono::system_clock::now();
	countBin = findElem(arr, 0, N - 1, a);
	end = std::chrono::system_clock::now();
	binFindTime = end - start;
	start = std::chrono::system_clock::now();
	countSimp = simpFindElem(arr, 0, N - 1, a);
	end = std::chrono::system_clock::now();
	simpFindTime = end - start;
	if (countBin == -1)
		std::cout << "Вашего числа нет в массиве,\n";
	else
		std::cout << "Ваше число соответствует элементу массива с индексом " << countBin << " и " << countSimp << '\n';
	std::cout << "На поиск ответа ушло " << binFindTime.count() << " сек. бинарным поиском и " << simpFindTime.count() << " сек. простым перебором\n\n";

}

//функция меняет местами два числа, индексы вводит пользователь
void userSwap(int* arr) {
	int a, b;
	std::chrono::system_clock::time_point start, end;
	std::chrono::duration<double> swapTime;
	std::cout << "Перестановка элементов массива. Введите индексы через пробел\n";
	while (true) {
		std::cin >> a >> b;
		if (std::cin)
			break;
		std::cout << "Вы неправильно ввели пару чисел. Повторите ввод\n";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	if (a == b)
		std::cout << "Вы ввели одинаковые числа\n";
	else
		wasArrSort = false;
	start = std::chrono::system_clock::now();
	std::swap(arr[a], arr[b]);
	end = std::chrono::system_clock::now();
	swapTime = end - start;
	std::cout << "Перестановка элементов заняла " << swapTime.count() << " сек.\n";
	std::cout << "Измененый массив: ";
	for (int i = 0; i < N; i++)
		std::cout << arr[i] << ' ';
	std::cout << "\n\n";
}