#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int main() {
    setlocale(0, "");
    int mat_1[50][50], mat_2[50][50], size;
    cout << "Порядок матриц? ";
    cin >> size;//задаём порядок матриц
    long seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rand(seed);
    uniform_int_distribution<int> d(0, 9);
    for (int i = 0; i != size; i++) {//забиваем рандомными числами
        for (int j = 0; j != size; j++) {
            mat_1[i][j] = d(rand);
            mat_2[i][j] = d(rand);
        }
    }
    for (int i = 0; i != size; i++) {//смотрим что в первой матрице 
        for (int j = 0; j != size; j++) {
            cout << mat_1[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
    for (int i = 0; i != size; i++) {//смотрии что во второй матрице
        for (int j = 0; j != size; j++) {
            cout << mat_2[i][j] << " ";
        }
        cout << '\n';
    }
    int mnoj;
    for (int i = 0; i != size; i++) {
        mnoj = 1;
        for (int j = 0; j != size; j++) {//считаем произведение i-й строки
            mnoj *= mat_2[i][j];
        }
        for (int j = 0; j != size; j++) {//увеличиваем на полученное произведение i-й столбец
            mat_1[j][i] += mnoj;
        }
    }
    for (int i = 0; i != size; i++) {//выводим результат
        for (int j = 0; j != size; j++) {
            cout << mat_1[i][j] << " ";
        }
        cout << '\n';
    }
    return 0;
}
