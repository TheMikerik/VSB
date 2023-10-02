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
            cout << matrixA[i][j] << "   ";
        }
        cout << "|   " << matrixB[i] << endl;
    }
    cout << endl;
}
vector<vector<double>> SwapMatrix(vector<vector<double>> matrix){
    double max;
    double max_row;
    vector<vector<double>> result;

    for(int column=0; column<matrix.size(); column++){
        max = 0;
        max_row = 0;
        for(int row=0; row<matrix.size(); row++){
            if (abs(matrix[row][column]) > abs(max)){
                max = matrix[row][column];
                max_row = row;
            }
        }

        result.push_back(matrix[max_row]);
    }

    return result;
}
int main(){
    vector<vector<double>> gauss_matrix;
    PrintMatrix(A_1, B_1);
    gauss_matrix = SwapMatrix(A_1);
    PrintMatrix(gauss_matrix, B_1);
}

// radovan.recka.st@vsb.cz
// ALGC06_3