#include "Header.h"

int main(){
    int n, b, start, finish;        //кількість вершин, ввідна/рандом, початок шляху, кінець шляху
    cout << "Enter the number of vertices of the graph: "; cin >> n;
    cout << endl << "Would you like to randomize the matrix? Enter '1' or '0': "; cin >> b; cout << endl;
    int** matr = new int* [n];      //тут буде матриця вагів
    for (int i = 0; i < n; i++) {
        matr[i] = new int[n];
    }
    
    if (b) {                        //якщо користувач обрав рандом, генеруємо матрицю, інакше - вводимо
        srand(time(NULL));
        randomize(n, matr);
    }
    else input_matrix(n, matr);

    get_start_finish(start, finish, n);     //вводимо і перевіряємо початок і кінець шляху
    vertice* vertices = get_vertices(n, matr);  //отримуємо масив вершин
    vertices[start].min_dist = 0;               //початковій вершині встановлюємо відстань 0, іншим - 1000000
    int len = Deikstra(finish, vertices, n);    //основний алгоритм, докладніше в іншому файлі.
    if (len < 0 || len == 1000000) cout << endl << "The path doesn't exist" << endl;    //при таких значеннях розв'язку не існує
    else {                                      //гарненько виводимо
        cout << endl << "The length of the shortest path = " << len << endl;
        cout << "Path: ";
        for (int w : vertices[finish].path){
            cout << w << " - ";
        }
        cout << finish + 1 << endl;
    }
    for (int i = 0; i < n; i++) {               //видаляємо сміття
        delete[] matr[i];
    }
    delete[] matr;
}
