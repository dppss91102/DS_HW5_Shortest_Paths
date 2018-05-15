#include <iostream>
using namespace std;
#define int_max 2147483647

int** makeMatrix(int n);
void showPath(int** next, int i, int j);

int main() {
    int n;
    cin >> n;

    int **sho;
    sho = makeMatrix(n);

    auto **next =  (int **) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        next[i] = (int *) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
            next[i][j] = j;
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int m = (sho[i][k] == int_max || sho[k][j] == int_max)?int_max:(sho[i][k] + sho[k][j]);
                if (m < sho[i][j]) {
                    sho[i][j] = m;
                    next[i][j] = next[i][k];
                } else if (m == sho[i][j]) {
                    if (next[i][j] > next[i][k] && k != i)
                        next[i][j] = next[i][k];
                }
            }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (sho[i][j] != 0 && sho[i][j] != int_max) {
                cout << "Path(" << i << "," << j << "):" << i;
                showPath(next, i, j);
                cout << endl << "Cost:" << sho[i][j] << endl;
            }

    return 0;
}

int** makeMatrix(int n){
    auto **temp = (int **) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++){
        temp[i] = (int *) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++){
            cin >> temp[i][j];
            if (temp[i][j] == 0 && i != j)
                temp[i][j] = int_max;
        }
    }

    return temp;
}
void showPath(int** next, int i, int j){
    if (i != j){
        cout << "->" << next[i][j];
        showPath(next, next[i][j], j);
    }
}