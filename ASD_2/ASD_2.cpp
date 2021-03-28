#include "Header.h"

int main() {
    int n, b;        //кількість вершин, ввідна/рандом
    cout << "Enter the number of vertices of the graph: "; cin >> n;
    cout << endl << "Would you like to randomize the matrix? Enter '1' or '0': "; cin >> b; cout << endl;
    int** matr = new int* [n];      //тут буде матриця вагів
    int** path = new int* [n];
    for (int i = 0; i < n; i++) {
        matr[i] = new int[n];
        path[i] = new int[n];
    }
    if (b) {                        //якщо користувач обрав рандом, генеруємо матрицю, інакше - вводимо
        srand(time(NULL));
        randomize(n, matr, path);
    }
    else input_matrix(n, matr, path);
    time_t t0 = clock();
    Floyd(matr, path, n);
    time_t t1 = clock();
    cout << "Result:" << endl;
    outp_matrix(n, matr);
    cout << "Path matrix:" << endl;
    outp_p_matrix(n, path);
    cout << "Search time: " << float (t1 - t0) / CLOCKS_PER_SEC << " seconds." << endl;
    del(matr, n);               //видаляємо сміття
    del(path, n);
}


// 9 0 1 2 1 1 3 3 2 4 2 2 6 9 3 4 4 3 5 1 4 6 3 4 7 5 5 6 7 6 7 4 6 8 2 7 8 2 8 9 3 0