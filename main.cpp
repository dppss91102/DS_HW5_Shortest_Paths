#include <iostream>
using namespace std;
#define int_max numeric_limits<int>::max()

int** makeMatrix(int n);
int** copyMatrix(int n, int **copy);
void showPath(int** cost, int** pts, int i, int j);

int main() {
    int n;
    cin >> n;

    int **cost, **sho;
    cost = makeMatrix(n);
    sho = copyMatrix(n, cost);

    auto **midPts =  (int **) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        midPts[i] = (int *) malloc(sizeof(int) * n);

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int m = (sho[i][k] == int_max || sho[k][j] == int_max)?int_max:(sho[i][k] + sho[k][j]);
                if (m < sho[i][j]) {
                    sho[i][j] = m;
                    midPts[i][j] = k;
                }
            }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (sho[i][j] != 0 && sho[i][j] != int_max) {
                cout << "Path(" << i << "," << j << "):" << i << "->";
                showPath(cost, midPts, i, j);
                cout << j << endl << "Cost:" << sho[i][j] << endl;
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
int** copyMatrix(int n, int **copy){
    auto **temp = (int **) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++){
        temp[i] = (int *) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
            temp[i][j] = copy[i][j];
    }

    return temp;
}
void showPath(int** cost, int** pts, int i, int j){
    if (cost[i][j] == int_max){
        showPath(cost, pts, i, pts[i][j]);
        cout << pts[i][j] << "->";
    }
}