#include <iostream>
#include <ctime>

#define N 3

void randMatr(int [N][N]);
void printMatr(int[N][N]);
void whatTheHELL(int[N][N], int[N][N]);

int main()
{
	srand(time(NULL));
	int matOrg[N][N], matSec[N][N];
	randMatr(matOrg);
	randMatr(matSec);
	whatTheHELL(matOrg, matSec);
}

void randMatr(int arr[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0;j < N;j++)
			arr[i][j] = rand() % 10;
	printMatr(arr);
}


void printMatr(int arr[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0;j < N;j++)
			std::cout << arr[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << "\n\n";
}

void whatTheHELL(int arrOrg[N][N], int arrSec[N][N])
{
	int sum;
	for (int i = 0;i < N;i++) {
		sum = 1;
		for (int z = 0;z < N;z++)
			sum *= arrSec[i][z];
		for (int j = 0;j < N;j++)
			arrOrg[j][i] += sum;
	}
	printMatr(arrOrg);
}