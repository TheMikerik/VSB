#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<double>> A_1 = {
    {1,2,-3,4,5},
    {2,1,0,3,0},
    {0,2,1,2,-1},
    {3,-1,0,5,2},
    {2,1,2,3,-4}
    };
vector<double> B_1 = {4,9,5,3,2};

void PrintMatrix(vector<vector<double>> matrixA, vector<double> matrixB){
    for(int i=0; i<matrixA.size(); i++){
        for(int j=0; j<matrixA[i].size(); j++){
            cout << matrixA[i][j] << "\t";
        }
        cout << "|   " << matrixB[i] << endl;
    }
    cout << endl;
}
void SwapMatrix(vector<vector<double>> &matrix, vector<double> &result){
    int n = matrix.size();

    for (int column = 0; column < n; column++) {
        for (int row = column + 1; row < n; row++) {
            double subtractor = matrix[row][column] / matrix[column][column];

            for (int digits = column; digits < n; digits++) {
                matrix[row][digits] -= subtractor * matrix[column][digits];
            }
            result[row] -= subtractor * result[column];
        }
    }
}
void EvaluateMatrix(vector<vector<double>> &matrix, vector<double> &result){
    vector<double> xs;
    int n = matrix.size();

    for(int x = n; x > 0; x--){
        double seeked_x;
        double tmp_x;
        if(x == n){
            seeked_x = result[n-1] / matrix[n-1][n-1];
            xs.push_back(seeked_x);
        }
        else{
            for(int column = n; column > x; column--){
                tmp_x = xs.at(n - column);
                matrix[x-1][column-1] *= tmp_x;
            }
            for(int digits = n; digits > x; digits--){
                if(matrix[x-1][digits-1] > 0){
                    result[x-1] -= matrix[x-1][digits-1];
                }
                else if(matrix[x-1][digits-1] < 0){
                    result[x-1] -= matrix[x-1][digits-1];
                }
            }

            seeked_x = result[x-1] / matrix[x-1][x-1];
            xs.push_back(seeked_x);

        }
            cout << "x" << x << ": " << seeked_x << endl;
    }
}
int main(){
    PrintMatrix(A_1, B_1);
    SwapMatrix(A_1, B_1);
    PrintMatrix(A_1, B_1);
    EvaluateMatrix(A_1, B_1);
}

// radovan.recka.st@vsb.cz
// ALGC06_3