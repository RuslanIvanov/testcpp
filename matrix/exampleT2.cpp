#include <iostream>
using namespace std;
int main(){
    int A[3][3],B[3][3], j, i;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            cin >> A[i][j];
    }
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            B[i][j] = A[j][i];
    }
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            cout << B[i][j];
        cout << endl;
    }
    system("pause");
    return 0;
}