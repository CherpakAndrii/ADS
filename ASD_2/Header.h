#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <time.h>

const int inf = 1000000;

using namespace std;
void outp_matrix(int, int**), outp_p_matrix(int, int**), input_matrix(int, int**, int**);
void randomize(int, int**, int**), Floyd(int**, int**, int);

void input_matrix(int n, int** matr, int**path) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            path[i][j] = inf;
            if (i == j) matr[i][j] = 0;
            else matr[i][j] = inf;
        }
    }
    int n_of_edges = 0;
    outp_matrix(n, matr);
    cout << "Now enter edges of the graph.\nFor example, to input the edge v1 -> v3 with weight 8, enter '1 3 8'" << endl;
    while (n_of_edges < n * (n - 1)) {
        int v1, v2, w;
        cout << "Enter 0 to finish the input." << endl;
        cout << "Enter the edge: "; cin >> v1;
        if (v1 == 0) break;
        cin >> v2; cin >> w;
        if (v1 == v2) {
            cout << "Weight of the edge between the same vertices should equal 0" << endl;
            clock_t t1 = clock();
            while (clock() / CLOCKS_PER_SEC - t1 / CLOCKS_PER_SEC < 4);
        }
        else if (v1 > v2) {
            cout << "Incorect input." << endl;
            clock_t t1 = clock();
            while (clock() / CLOCKS_PER_SEC - t1 / CLOCKS_PER_SEC < 4);
        }
        else {
            matr[v1 - 1][v2 - 1] = w;
            path[v1 - 1][v2 - 1] = v1 - 1;
            n_of_edges += 1;
        }
        system("CLS");
        cout << "Entered matrix:" << endl;
        outp_matrix(n, matr);
    }
    system("CLS");
    cout << "Entered matrix:" << endl;
    outp_matrix(n, matr);
}

void randomize(int n, int** matr, int** path) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matr[i][j] = 0;
                path[i][j] = inf;
                continue;
            }
            if (i > j) {
                matr[i][j] = inf;
                path[i][j] = inf;
                continue;
            }
            int r = rand() % 3;
            if (!r) {
                matr[i][j] = inf;
                path[i][j] = inf;
            }
            else {
                matr[i][j] = rand() % 10 + 1;
                path[i][j] = i;
            }
        }
    }
    system("CLS");
    cout << "Entered matrix:" << endl;
    outp_matrix(n, matr);
}

void Floyd(int** D, int** path, int n) {
    for (int m = 1; m < n-1; m++) {
        for (int i = 0; i < n; i++) {
            if (i == m) continue;
            for (int j = i+1; j < n; j++) {
                if (j == m or j == i) continue;
                int d = D[i][m] + D[m][j];
                if (d < D[i][j]) {
                    D[i][j] = d;
                    path[i][j] = m;
                }
            }
        }
    }
}

template <typename T>
void del(T** m, int n) {
    for (int i = 0; i < n; i++) {
        delete[] m[i];
    }
    delete[] m;
}

void outp_matrix(int n, int** matr) {
    cout << "     |";
    for (int i = 0; i < n; i++) printf("v%-3d|", i + 1);
    cout << endl;
    for (int i = 0; i < n; i++) {
        printf("v%-4d|", i + 1);
        for (int j = 0; j < n; j++) {
            if (matr[i][j] == inf) cout <<"inf |";
            else printf("%-4d|", matr[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void outp_p_matrix(int n, int** matr) {
    cout << "    |";
    for (int i = 0; i < n; i++) printf("v%-2d|", i + 1);
    cout<< endl;
    for (int i = 0; i < n; i++) {
        printf("v%-3d|", i + 1);
        for (int j = 0; j < n; j++) {
            if (matr[i][j] == inf) cout << "-  |";
            else printf("%-3d|", matr[i][j]+1);
        }
        cout << endl;
    }
    cout << endl;
}