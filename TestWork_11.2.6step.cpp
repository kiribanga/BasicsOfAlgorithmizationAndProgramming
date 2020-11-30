#include <iostream>
#include <ctime>

#define N_i 5
#define N_f 7

void FillInAndShowArray(int*, int);
void FillInAndShowArray(float*, int);

int main()
{
	srand(time(NULL));
	int arr_i[N_i];
	float arr_f[N_f];
	FillInAndShowArray(arr_i, N_i);
	FillInAndShowArray(arr_f, N_f);
}

void FillInAndShowArray(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = rand() % 198 - 99;
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}

void FillInAndShowArray(float* arr, int len)
{	
	for (int i = 0; i < len; i++)
	{
		arr[i] = (float)((rand() % 19800 - 9900))/100;
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}