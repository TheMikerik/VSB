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
vector<vector<double>> SwapMatrix(vector<vector<double>> matrix, vector<double> result){
    double max;
    double max_row_index;
    double subtractor;
    vector<vector<double>> result_matrix;

    for(int column=0; column<matrix.size(); column++){
        max = 0;              //--Max number in each column
        max_row_index = 0;    //--Index of the row with max number

        for(int row=0; row<matrix.size(); row++){
            if (abs(matrix[row][column]) > abs(max)){
                max = matrix[row][column];
                max_row_index = row;
            }
        }

        for(int i=0; i<matrix.size(); i++){

            subtractor = matrix[i][column] / max;

            for(int j=0; j<matrix[i].size(); j++){
                if(i == max_row_index || j<column){
                }
                else{
                    matrix[i][j] -= ( matrix[max_row_index][column]*subtractor);
                }

                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }

        result_matrix.push_back(matrix[max_row_index]);
        result_matrix[column].push_back(result[max_row_index]);

        cout << "Final matrix: \n";
        for(int i=0; i<result_matrix.size(); i++){
            for(int j=0; j<result_matrix[i].size(); j++){
                if( j==result_matrix[i].size() - 1 ){
                    cout << "|   " << result_matrix[i][j] << endl;
                    break;
                }
                cout << result_matrix[i][j] << "\t";
            }
        }
        cout << endl;
        cout << endl;
    }

    return result_matrix;
}
int main(){
    vector<vector<double>> gauss_matrix;
    PrintMatrix(A_1, B_1);
    gauss_matrix = SwapMatrix(A_1, B_1);
    PrintMatrix(gauss_matrix, B_1);
}

// radovan.recka.st@vsb.cz
// ALGC06_3