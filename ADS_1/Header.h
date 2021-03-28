#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <time.h>

const int inf = 1000000;        //�������� ������������ �� 1,000,000

using namespace std;
void outp_matrix(int, int**), input_matrix(int, int**), randomize(int, int**), get_start_finish(int&, int&, int);

class vertice {                 //�������� ���� ������� � ������ ����������������:
public:
    bool passed;                    //�� �������� �������
    int min_dist;                   //������� ������������ �����
    vector<pair<int, int>> adjacent; //������ ������� ������ �� ���� ����������� �� �����
    vector<int> path;               //����������� ����
    vertice(int dist = inf) { min_dist = dist;  passed = false; } //����������� �����
    void n_adj(int v, int val) { adjacent.push_back({ v, val }); } //�-� ��� ��������� ������ �������
};

int min(vertice* v, int n) {        //����� ������ �������� ���������� �������. ���� ���� - ������� ��������
    int min_index;
    for (int i = 0; i < n; i++) {
        min_index = i;
        if (!v[i].passed) break;
    }
    for (int i = 0; i < n; i++) {
        if (!v[i].passed && v[i].min_dist < v[min_index].min_dist) min_index = i;
    }
    return min_index;
}

void input_matrix(int n, int** matr) {      //�������� �������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matr[i][j] = 0;
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
        else {
            matr[v1 - 1][v2 - 1] = w;
            n_of_edges += 1;
        }
        system("CLS");
        outp_matrix(n, matr);
    }
    system("CLS");
    outp_matrix(n, matr);
}

void outp_matrix(int n, int** matr) { //��������� �������
    cout << "     |";
    for (int i = 0; i < n; i++) { printf("v%-3d", i + 1); if (i < n - 1) cout << "|"; }
    cout << endl;
    for (int i = 0; i < n; i++) {
        printf("v%-4d", i + 1); cout << "|";
        for (int j = 0; j < n; j++) {
            if (matr[i][j]) printf("%-4d", matr[i][j]);
            else cout << "    ";
            if (j < n - 1) cout << '|';

        }
        cout << endl;
    }
}

void randomize(int n, int** matr) {     //��������� ��������� �������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matr[i][j] = 0;
                continue;
            }
            int r = rand() % 4;
            if (r) matr[i][j] = 0;
            else matr[i][j] = rand() % 10 + 1;
        }
    }
    system("CLS");
    outp_matrix(n, matr);
}

vertice* get_vertices(int n, int** matrix) {    //����� �������, ���������� ������ ������ �� ��'���� �� ����
    vertice* vertices = new vertice[n];
    for (int i = 0; i < n; i++) {
        vertice a(inf);
        vertices[i] = a;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j]) vertices[i].n_adj(j, matrix[i][j]);
        }
    }
    return vertices;
}

void get_start_finish(int& s, int& f, int n) {  //�������� � �������� ������� � ���� �����
    cout << "Enter the numbers of start and finish vertices: " << endl;
    while (1) {
        cout << "\tStart: "; cin >> s;
        cout << "\n\tFinish: "; cin >> f; cout << endl;
        if (s > 0 && s <= n && f > 0 && f <= n && s!=f) break;
        cout << "Incorrect input!" << endl;
    }
    s -= 1;                                     //���������� �� ������� �������� � �������� �� 0
    f -= 1;
}

int Deikstra(int finish, vertice* vertices, int n) {
    while (1) {
        int a = min(vertices, n);       //������� "�����������" ����
        if (vertices[a].passed) break;  //���� �� ������� ���� ��������, ������������ ����� �� ����������, ��������
        for (pair<int, int> p : vertices[a].adjacent) {     //��� ����� � ������� ������...
            if (vertices[a].min_dist + p.second < vertices[p.first].min_dist) { //...���������� ������� ����� ����� �� �������
                vertices[p.first].min_dist = vertices[a].min_dist + p.second;   //���� ����� - ������
                vertices[p.first].path.erase(vertices[p.first].path.begin(), vertices[p.first].path.end());
                for (int w : vertices[a].path) vertices[p.first].path.push_back(w); //� ������������ ����
                vertices[p.first].path.push_back(a+1);
            }
        }
        vertices[a].passed = true;          //���� � ������� ��������� ���������
        if (a==finish) return vertices[finish].min_dist;
    }
}